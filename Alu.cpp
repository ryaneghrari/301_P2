#include "ALU.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

ALU::ALU(){}

ALU::ALU(string id)
{
	this->id = id;
}

string ALU::calculate(string input1, string input2, string opcodeName) {
	if (opcodeName == "add" || opcodeName == "addi" || opcodeName == "sw" || opcodeName == "lw" )
		return add(input1,input2);
	else if (opcodeName == "sub") 
		return sub(input1,input2);
	else if (opcodeName == "slt") 
		return slt(input1,input2);
	else if (opcodeName == "beq")
		return beq(input1,input2);
	else 
		return "";

}

string ALU::beq(string a, string b) {
	int aa = convertBinaryToDecimal(a);
	int bb = convertBinaryToDecimal(b);
	int sub = aa-bb;
	if (sub == 0)
		return "true";
	else 
		return "false";

}


string ALU::add(string a, string b) {
	int aa = convertBinaryToDecimal(a);
	int bb = convertBinaryToDecimal(b);
	cout << "first in decimal " << aa << "\n";
	cout << "second in decimal " << bb << "\n";

	int sum = aa+bb;

	string sumBinary = convertDecimalToBinary(sum);

	return sumBinary;
}

string ALU::convertDecimalToBinary(int value) {
	bool neg = false;
	if (value < 0 ) {
		value = -value;
		neg = true;
	}

	string result = "";
	int powerOf2 = 0;
	if (value >= 0) {
		for (int i=31; i >= 0; i--) {
			powerOf2 = pow(2,i);
			if (value - powerOf2 >= 0) {
				value = value - powerOf2;
				result = result + "1";
			}
			else {
				result = result + "0";
			}
		}
	}
	//must find twos complement
	if (neg == true) {
		//inverse the bits in result
		for (int len=0; len<32; len++) {
			if (result.at(len) == '1')  
				result[len] = '0';
			else
				result[len] = '1';
		}


		//now must add one to result 
		//adding 1 to inverse of the string 
		if (result[31] == '0') 
			result[31] = '1';
		//last index is 1 so need to keep switching 1's to 0 from the back till you reach a 0
		else {
			int index = 31;
			while (result[index] == '1') {
				result[index] = '0';
				index--;
			}
			result[index] = '1';

		}


	}

	return result;

}

string ALU::sub(string a, string b)
{
	int aa = convertBinaryToDecimal(a);
	int bb = convertBinaryToDecimal(b);

	int sum = aa-bb;

	string sumBinary = convertDecimalToBinary(sum);

	return sumBinary;
}

string ALU::sll(string a)
{
	a = a.substr(2);
	a = a + "00";
	return a;
}

//note that a represents value from rs and b represents value from rt
string ALU::slt(string a, string b) {
	int aa = convertBinaryToDecimal(a);
	int bb = convertBinaryToDecimal(b);
	if (aa < bb ) 
		return "00000000000000000000000000000001";
	else 
		return "00000000000000000000000000000000";

}



	//false if string is positive and true if string is negative
int ALU::convertBinaryToDecimal(string binary) {
	//false is positive and true if number is negative
	bool neg = false;
	//stores the decimal
	 int decimal = 0;
  	int len = binary.size()-1;

  	//if first element in binary string is 1 then it is a negative number
  	//must find twos complement
	if (binary[0] == '1') {
		//we know it is neg
		neg = true;
		//iterate through the binary string and inverse it 
		for (int i = 0; i <= len; i++) {
			if (binary.at(i) == '1')
				binary[i] = '0';
			else
				binary[i] = '1';
		}
		//adding 1 to inverse of the string 
		if (binary[len] == '0') 
			binary[len] = '1';
		//last index is 1 so need to keep switching 1's to 0 from the back till you reach a 0
		else {
			int index = len;
			while (binary[index] == '1') {
				binary[index] = '0';
				index--;
			}
			binary[index] = '1';

		}

	}

	//at this point we know binary is a positive number 
  for (int i = 0; i <= len; i++) {
  	//if it is 1 add 2^(len-i) to the decimal counter
    if (binary[i] == '1') {
      decimal += pow(2,len-i);
    }
  }

  if (neg)
  	return -decimal;
  else
  	return decimal;
 }
