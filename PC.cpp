#include "PC.h"
#include <math.h>

using namespace std;

PC::PC(int max) {
	PCIndex = 0;
	maxPC = max;
}

string PC::GetHexForPC() {
	return DecToHex(16384+(4*PCIndex));
}

void PC::determineNewPC() {

}

bool PC::IsPCValid() {
	if (PCIndex < 0)
		return false;
	else if (PCIndex >= maxPC)
		return false;
	else 
		return true;
}

string PC::DecToHex(int d) {
	return "0x";
}

string PC::getPCAsBinary() {
	int index = (PCIndex*4) + 16384;
	return convertDecimalToBinary(index);
}

void PC::convertNextToPC(string binaryAddress) {
	int index = convertBinaryToDecimal(binaryAddress);
	setPCIndex((index - 16384)/4); 

}

	//false if string is positive and true if string is negative
int PC::convertBinaryToDecimal(string binary) {
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

string PC::convertDecimalToBinary(int value) {
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
