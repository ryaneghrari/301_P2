#include <iostream>
#include <string>
#include "alu.h"

using namespace std;

int main()
{
	Alu alu;

	cout << alu.add("10000000000000000000000000000010","10000000000000000000000000000010") << endl;
	cout << alu.sll("1100001") << endl;
}


