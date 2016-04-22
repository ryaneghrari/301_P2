#ifndef __DATAMEMORY_H__
#define __DATAMEMORY_H__

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

/*
	The data memory file is used to similuate the data memory in the MIPS Pipeline 
	You are able to feed in an address and return a data or write to memory
*/

class DataMemory
{
	public:

		// Default constructor - fills up registers with NULL
		DataMemory();

		// Constructor for register file takes in the Data memory Input FileDataMemory(ifstream& infile);
		DataMemory(string filename);
		DataMemory(string binaryArray[]);

		// Deconstructor
		~DataMemory();

		//returns binary data from the registers 
		//when given a 32 bit binary string that represents an address to a data location
		string readData(string binaryAddress);

		void writeData(string data, string binaryAddress);

		//converts binary string to Decimal
		int convertBinaryToDecimal(string binary);

		
	private:

		// Array holding 100 memory spaces
		string myDataBinary[100];
		string myDataHex[100];
		
};

#endif 
