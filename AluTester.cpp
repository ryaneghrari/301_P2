#include <iostream>
#include <string>
#include "alu.h"

using namespace std;

int main()
{
	Alu alu;

	cout << alu.add("11100000000000000","10000000000000") << endl;
	cout << alu.sll("1100001") << endl;
}


