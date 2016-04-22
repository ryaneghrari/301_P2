#include "DataMemory.h"
#include <math.h>
#include <array>
#include <sstream>

using namespace std;

// Default constructor
DataMemory::DataMemory()
{

	for (int i = 1; i < 100; i++)
	{
		myDataBinary[i] = "NULL"; // initialize values to null
	}
}

//this constructor is for testing only!
DataMemory::DataMemory(string binaryArray[]) {
	int i;
	for ( i=0; i < binaryArray->size(); i++) {
		myDataBinary[i] = binaryArray[i];
	}
	while (i < 100) {
		myDataBinary[i] = "00000000000000000000000000000000";
		i++;
	}
}

DataMemory::DataMemory(string filename)
{
	for (int i = 0; i < 100; i++)
	{
		myDataHex[i] = "NULL"; // initialize values to null
	}

	ifstream infile(filename.c_str());

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
		string memNumString = "";
		for (int i = 0; i < parsedLine.size(); i++)
		{
			if (parsedLine[i] == ':')
			{
				break;
			}
			memNumString += parsedLine[i]; //basically, this should contain the register number now
		}


		int memNum;

		std::stringstream ss;

		ss << std::hex << memNumString;

		ss >> memNum;

		size_t pos = parsedLine.find(":"); //finds index position of this in the string
		string data = parsedLine.substr(pos + 1); //this is the string of data

	    // Based on memory number, put data into the array
		myDataHex[memNum] = data;
		
	}

}


// Deconstructor
DataMemory::~DataMemory(){}


string DataMemory::readData(string binaryAddress) {
	int index = convertBinaryToDecimal(binaryAddress);
	index = (index-268435456)/4;
	cout << "The index is: " << index << "\n";
	return myDataBinary[index];
}

void DataMemory::writeData(string data, string binaryAddress) {
	int index = convertBinaryToDecimal(binaryAddress);
	index = (index-268435456)/4;
	cout << "The index is: " << index << "\n";
	myDataBinary[index] = data;
}

//takes in a binary string and converts it decimal
int DataMemory::convertBinaryToDecimal(string binary) {
  int decimal = 0;            //counter
  int len = binary.size()-1;  // last index of binary string

  for (int i = 0; i <= len; i++) {
    if (binary[i] == '1') {
      decimal += pow(2,len-i);
    }
  }

  return decimal;

}
