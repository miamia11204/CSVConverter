#include "functions.h"
//Include libraries here
#include <iostream>
#include <fstream>
using namespace std;

//Define functions here
//Display help function
void display_help() {
	cout << "CSVConverter Application, (c) 2023, Mia Nguyen\n" << endl;
	cout << "usage: csv2html [--help] [-hrnq] csvFilename [htmlFilename] [--(bg|background) Args...] [--(fg|foreground) Args...]" << endl;
	cout << "\n    --help          display the help text for the program." << endl;
	cout << "    -h              first line is the table header" << endl;
	cout << "    -r              report conversion metrics" << endl;
	cout << "    -n              no border" << endl;
	cout << "    -q              strip quotes, commas inside quotes are not delimiters" << endl;
	cout << "\n    csvFilename     the name of the ASCII csv file to process" << endl;
	cout << "    htmlFilename    the name of the HTML file receiving the output." << endl;
	cout << "                    If not provided the csv filename will be used" << endl;
	cout << "                    with its extension changed to \".html\"" << endl;
	cout << "    --bg,           background-colors for rows (first is header, then cycle)" << endl;
	cout << "    --background        where the colors are HTML/CSS compatible encoding" << endl;
	cout << "\n    --fg,           foreground-colors for row (first is header, then cycle)" << endl;
	cout << "    --foreground        where the colors are HTML/CSS compatible encoding\n" << endl;
}