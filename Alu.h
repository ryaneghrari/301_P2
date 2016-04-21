#ifndef __ALU_H__
#define __ALU_H__

#include <sstream>
#include <iostream>

using namespace std;

class ALU{
	public:
		ALU();
		~ALU() {};
		string add(string a, string b);
		string sll(string a);
		string sub(string a, string b);
		string slt(string a, string b);
		string beq(string a, string b);
		bool   isZero(){return zero;};
		string calculate(string input1, string input2, string opcodeName);
		string convertDecimalToBinary(int value);
	
	private:
		int convertBinaryToDecimal(string binary);
		string decimal_binary(int n);
		bool zero;
		string id;
};

#endif
