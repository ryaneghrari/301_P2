#ifndef _REGISTERFILE_H
#define _REGISTERFILE_H

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
	Register File is repsonsible for simulating the register file in the MIPS datapath.
	Essentially functions as unit which returns values from registers and writes data
	to certain registers when calculations are performed in the ALU.
*/

class RegisterFile
{
	public:

		// Default constructor - fills up registers with NULL
		RegisterFile();

		// Constructor for register file takes in the Register Input File
		RegisterFile(string filename);

		// Deconstructor
		~RegisterFile();

		// Method for register file that uses one read register
		// Returns the contents of what is inside readReg1
		string regExecute(int readReg1);

		// Method for register file that uses only teo read registers
		// Return the contents of what is inside both register 1 and register 2 in array form
		vector<string> regExecute(int readReg1, int readReg2);

		// General get method that gets contents of any register given its number
		string getRegContents(int regNum);

		// Set method that sets conents of register.  This is used when a register is written to
		// as a result of add, sub, lw etc...
		// Takes in a string representing the data
		void setRegData(int regNum, string regData);

		// Useful debugging tool that prints register numbers with their content
		void printRegContents();

	private:

		// Array containing contents of registers 0 - 32
		string myRegisters[32];
};

#endif
