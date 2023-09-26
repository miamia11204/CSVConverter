#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "functions.h"
using namespace std; 

int main(int argc, char* argv[])
{
	//if --help is called, disregard any other switch
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "--help") == 0)
		{
			display_help();
			return 1;
		}
		//if more than 1 arg contain the switch (ie: -rq -h/ -r simple.csv -bg) 
		//=> report too many arg
		if (i >= 2)
		{
			string anoSwitchTrack = argv[i];
			if (anoSwitchTrack[0] == '-' && anoSwitchTrack[1] != '-') 
			{
				cout << "Error: too many command line arguments \"" << argv[i] << "\"" << endl;
				return 1;
			}
		}
	}
	
	string csvfile;
	//Checking switches
	bool switchH = false;
	bool switchR = false;
	bool switchN = false;
	bool switchQ = false;
	bool switchBG = false;
	bool switchFG = false;
	bool switchExist = false;
	string inputSwitch = argv[1];
	//If the switch is not start with '-', then it might be the csv file
	//1: If switch specified => argv[2] = csv file
	//2: If switch IS NOT specified => argv[1] = csv file
	if (inputSwitch[0] != '-')
	{
		csvfile = argv[1];
	}
	else
	{
		csvfile = argv[2];
		//Checking each character in the inputSwitch
		for (int j = 1; j < inputSwitch.length(); j++)
		{
			char switchChar = inputSwitch[j];
			switch (switchChar)
			{
			case 'h':
				switchH = true;
				switchExist = true;
				break;
			case 'r':
				switchR = true;
				switchExist = true;
				break;
			case 'n':
				switchN = true;
				switchExist = true;
				break;
			case 'q':
				switchQ = true;
				switchExist = true;
				break;
				//Report if switch is not correct
			default:
				cout << "Error: unknown switch \" " << argv[1] << "\"" << endl;
				return 1;
			}
		}
	}

	//If more than 2 arg are entered and there is only switch, no file specified --> Error
	if (argc >= 2)
	{
		if ((switchExist && argv[2] == NULL) || (!switchExist && argv[1] == NULL))
		{
			cout << "Error: text file not specified." << endl;
			return 1;
		}
	}
	

	//Declare input file - output file
	ifstream inputFile;
	ofstream outputFile;
	string htmlfile = "";
	string title = "";

	//Open csvfile
	inputFile.open(csvfile);
	//Checking and report if file cannot be opened
	if (!inputFile.is_open())
	{
		cout << "Error: .csv filename \"" << csvfile << "\" --> No such file or directory" << endl;
		return 1;
	}
	title = csvfile.substr(0, csvfile.find_first_of('.'));

	//Checking if html file is specified by: If there are 2 dots '.' => The html file is specified
	int dotCounter = 0;
	for (int i = 1; i < argc; i++)
	{
		string arg = argv[i];
		for (char ch : arg)
		{
			if (ch == '.')
			{
				dotCounter++;
			}
		}
	}

	//If html file is NOT specified
	if (dotCounter == 1)
	{
		htmlfile = title + ".html";
		outputFile.open(htmlfile);
		if (!outputFile.is_open())
		{
			cout << "Error: Failed to open \"" << htmlfile << "\"" << endl;
			return 1;
		}
	}
	else if (dotCounter == 2)
	{
		if (switchExist)
		{
			htmlfile = argv[3];
		}
		else
		{
			htmlfile = argv[2];
		}
		outputFile.open(htmlfile);
		//Checking and report if file cannot be opened
		if (!outputFile.is_open())
		{
			cout << "Error: Failed to open \"" << htmlfile << "\"" << endl;
			return 1;
		}
	}

	///Report if output and input files have the same name (same .extension)
	if (htmlfile == csvfile)
	{
		cout << "Error: input and output files are the same." << endl;
		return 1;
	}

	//Edit the HTML file
	outputFile << "<!DOCTYPE html>" << endl;
	outputFile << "<html>" << endl;
	outputFile << "<head>" << endl;
	outputFile << "<title> " << title << "</title>" << endl;
	//Style tag!
	outputFile << "<style>" << endl;
	//Checking --bg/ --background && --fg/--foreground
	//Check the switch after argv[2] (csvfile) 
	//Create 2 variables type int to keep track where the --bg and/or --fg is found
	int BGIndex = 0;
	int FGIndex = 0;
	for (int i = 2; i < argc; i++)
	{
		//The arg after --bg/ --fg will be applied for the header
		if ((strcmp(argv[i],"--background") == 0) || (strcmp(argv[i],"--bg") == 0))
		{
			BGIndex = i;
			switchBG = true;
		}
		else if ((strcmp(argv[i],"--foreground") == 0) || (strcmp(argv[i],"--fg") == 0))
		{
			FGIndex = i;
			switchFG = true;
		}
	}
	if (switchBG && switchFG && switchH)
	{
		outputFile << "th { background-color: " << argv[BGIndex + 1];
		outputFile << "; color: " << argv[FGIndex + 1] << "; }";
	}
	else if (switchBG && !switchFG && switchH)
	{
		outputFile << "th { background-color: " << argv[BGIndex + 1] << "; }"; //worked
	}
	else if (!switchBG && switchFG && switchH)
	{
		outputFile << "th { color: " << argv[FGIndex + 1] << "; }"; //worked
	}
	outputFile << "</style>" << endl;

	outputFile << "</head>" << endl;
	outputFile << "<body>" << endl;
	//Border table
	if (switchN)
	{
		outputFile << "<table cellspacing = \"0\" cellpadding = \"0\">" << endl;
	}
	else
	{
		outputFile << "<table>" << endl;
	}

	//Read values from input file
	string line = "";
	int rowCounter = 0;
	bool isFirstRow = true;
	while (getline(inputFile, line))
	{
		string value;
		stringstream extractedLine(line);
		outputFile << "<tr>";

		//Edit the HTML file
		//Header row and standard rows
		//If there is no switch -q
		if (switchH && isFirstRow)
		{
			while (getline(extractedLine, value, ','))
			{
				outputFile << "<th>" << value << "</th>";
			}
		}
		else
		{
			//if it is first row, extract it like normal
			if (switchQ && !isFirstRow)
			{
				int quoteCounter = 0;
				for (char ch : line)
				{
					if (ch == '\"')
					{
						quoteCounter++;
					}
				}

				// If there are two quotes, handle the special case
				if (quoteCounter == 2)
				{
					stringstream streamExtractedLine(line);
					string firstLetter, secondLetter;
					getline(streamExtractedLine, firstLetter, '\"');
					getline(streamExtractedLine, secondLetter, '\"');
					value = firstLetter + secondLetter;
					outputFile << "<td>" << value << "</td>";

					string nextValue;
					streamExtractedLine.ignore(); // Ignore the ',' before the grade value
					getline(streamExtractedLine, nextValue);
					outputFile << "<td>" << nextValue << "</td>";
				}
				else
				{
					// No quotes, handle regular comma-separated values
					while (getline(extractedLine, value, ','))
					{
						outputFile << "<td>" << value << "</td>";
					}
				}
			}
			else
			{
				// If there is no -q switch, handle regular comma-separated values
				while (getline(extractedLine, value, ','))
				{
					outputFile << "<td>" << value << "</td>";
				}
			}
		}

		outputFile << "</tr>" << endl;
		rowCounter++;
		isFirstRow = false;
	}

	//Edit the HTML file
	outputFile << "</table>" << endl;
	outputFile << "</body>" << endl;
	outputFile << "</html>" << endl;

	//Switch -r - Display # of lines
	if (switchR)
	{
		cout << "# lines input = " << rowCounter << endl;
	}
	
	inputFile.close();
	outputFile.close();

	return 0;
}