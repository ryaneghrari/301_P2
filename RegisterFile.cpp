#include "RegisterFile.h"

using namespace std;

// Default constructor
RegisterFile::RegisterFile()
{
	myRegisters[0] = '0'; //initialize zero reg

	for (int i = 1; i < 33; i++)
	{
		myRegisters[i] = "NULL"; // initialize values to null
	}
}

// Constructor that takes in Register Input File
RegisterFile::RegisterFile(ifstream& infile)
{
	// Check to make sure infile is good
	if (!infile)
	{
		cerr << "unable to open input file: " << infile << endl;
		return;
	}

	// Fill up registers with data
	while (infile)
	{
		string parsedLine;
		getline(infile, parsedLine); // put current line of file into parsedLine

		//get the register number from file
		string regNumString = "";
		for (int i = 0; i < parsedLine.size(); i++)
		{
			if (parsedLine[i] == ':')
			{
				break;
			}
			regNumString += parsedLine[i]; //basically, this should contain the register number now
		}
		int regNum = atoi(regNumString.c_str()); //now change it to integer for indexing

		size_t pos = parsedLine.find(":"); //finds index position of this in the string
		string data = parsedLine.substr(pos + 1); //this is the string of data

	    // Based on register number, put data into the array
		myRegisters[regNum] = data;
		
	}

}

// Deconstructor
RegisterFile::~RegisterFile(){}

// Method for register file that usesone read register
// Returns the contents of what is inside readReg1
string RegisterFile::regExecute(int readReg1)
{
	return myRegisters[readReg1];
}

// Method for register file that uses only teo read registers
// Return the contents of what is inside both register 1 and register 2 in array form
string* RegisterFile::regExecute(int readReg1, int readReg2)
{
	string contents[2];

	contents[0] = myRegisters[readReg1];
	contents[1] = myRegisters[readReg2];

	return *contents; 
}

// General get method that gets contents of any register given its number
string RegisterFile::getRegContents(int regNum)
{
	return myRegisters[regNum];
}

// Set method that sets conents of register.  This is used when a register is written to
// as a result of add, sub, lw etc...
// Takes in a string representing the data
void RegisterFile::setRegData(int regNum, string regData)
{
	myRegisters[regNum] = regData;
}

// Useful debugging tool that prints register numbers with their content
void RegisterFile::printRegContents()
{
	for (int i = 0; i < 33; i++)
	{
		cout << "Register #" << i << " : " << myRegisters[i] << endl; // initialize values to null
	}
}
