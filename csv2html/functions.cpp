#include "functions.h"
//Include libraries here
#include <iostream>
#include <fstream>
using namespace std;

//Define functions here
//Display help function
void display_help()
{
	cout << "CSVConverter, (c) 2023, Ngoc Minh Anh Nguyen\n" << endl;
	cout << "usage: CSVConverter [--help] [-hrnq] csvFilename [htmlFilename] [--(bg|background) Args...] [--(fg|foreground) Args...]" << endl;
	cout << "\n    --help          display the help section." << endl;
	cout << "    -h              first line is the table header" << endl;
	cout << "    -r              report conversion metrics" << endl;
	cout << "    -n              no border for the table" << endl;
	cout << "    -q              strip quotes, commas inside quotes are not delimiters" << endl;
	cout << "\n    csvFilename     the name of the converted csv file" << endl;
	cout << "    htmlFilename    the name of the output HTML file." << endl;
	cout << "    --bg,           background-colors for rows (first is header)" << endl;
	cout << "    --background        " << endl;
	cout << "\n    --fg,           foreground-colors for row (first is header)" << endl;
	cout << "    --foreground        \n" << endl;
}