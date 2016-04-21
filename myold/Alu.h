#ifndef __ALU_H
#define __ALU_H

#include <sstream>
#include <iostream>

using namespace std;

class Alu{
	public:
		Alu();
		~Alu() {};
		string add(string a, string b);
		string sll(string a);
		string sub(string a, string b);
		bool   isZero(){return zero;};
	
	private:
		string decimal_binary(int n);
		bool zero;
};

#endif
