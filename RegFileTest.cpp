#include <iostream>
#include "RegisterFile.h"

using namespace std;

// Test for RegisterFile.cpp
int main()
{
	cout << "filename: " << endl;
	string filename;
	cin >> filename;

	//default constructor test - array should all be NULL
	RegisterFile testReg;
	cout << "TESTING DEFAULT CONSTRUCTOR + PRINT:" << endl;
	testReg.printRegContents();

	//test constructor that takes in a file
	RegisterFile testRegFile(filename);
	cout << "TESTING FILE CONSTRUCTOR + PRINT:" << endl;
	testRegFile.printRegContents();

	cout << "TESTING regExecute:" << endl;
	string register15 = testRegFile.regExecute(15);
	cout << "Contents inside register 15: " << register15 << " [0xa7c3be21]" << endl;

	cout << "TESTING getRegContents:" << endl;
	string regContent = testRegFile.getRegContents(31);
	cout << "REGISTER 31: " << regContent << " [0xa7c3be21]" << endl;

	cout << "TESTING setRegData:" << endl;
	cout << "Register 18 contents before: " << testRegFile.getRegContents(18) << " [NULL]" << endl;
	testRegFile.setRegData(18, "0xasd87q1je"); //sets data in register 18 to this
	cout << "Register 18 contents after: " << testRegFile.getRegContents(18) << " [0xasd87q1je]" << endl;

	/* TAKE A LOOK AT THIS ONE HOMIE !!
	cout << "TESTING regExecute w/ 2 registers: " << endl;
	vector<string> testVec = testRegFile.regExecute(15, 21);
	cout << "Contents inside register 15 and 21: " << testVec.at(1) << " " << testVec.at(2) << " [0xa7c3be21 0xa7c3be21]" << endl;
	*/

	return 0;
}
