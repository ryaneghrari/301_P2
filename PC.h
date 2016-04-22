#ifndef __PC_H__
#define __PC_H__

#include <string>

using namespace std;

class PC {
public:
	string GetHexForPC();
	void determineNewPC();
	bool IsPCValid();
	PC(int max);
	int getPCIndex() {return PCIndex; };
	void setPCIndex(int i) {PCIndex = i; };
	string getPCAsBinary();
	void convertNextToPC(string binaryAddress);

private:
	int PCIndex;
	int maxPC;
	string convertDecimalToBinary(int value);
	int convertBinaryToDecimal(string binary);
	string DecToHex(int d);

};

#endif 