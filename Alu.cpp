#include "Alu.h"
#include <string>
#include <iostream>

using namespace std;

Alu::Alu(){}

string Alu::add(string a, string b)
{
	if((a.size() != 32) || (b.size() != 32))
	{
		cerr << "cannot perform add on bit size less than 32 bits" << endl;
		return "ERROR";
	}
	

	int numA = strtol(a.c_str(),NULL,2);	
	int numB = strtol(b.c_str(),NULL,2);	

	int sum = numA + numB;
   
	cout << sum << endl;

	return decimal_binary(sum);
}

string Alu::sub(string a, string b)
{
	int numA = strtol(a.c_str(),NULL,2);	
	int numB = strtol(b.c_str(),NULL,2);	

	int ans = numA - numB;
    
	return decimal_binary(ans);
}

string Alu::sll(string a)
{
	a = a.substr(2);
	a = a + "00";
	return a;
}


/* Function to convert decimal to binary.*/
string Alu::decimal_binary(int n)  
{

	bool neg = false;

	if(n < 0)
	{
		neg = true;
	}

    cout << "converting n: " << n << endl;

	int rem, i=1, binary=0;
	
	while (n!=0)
	{
		rem = n % 2;
		n /= 2;
		binary += rem * i;
		i *= 10;
	}
	
	stringstream ss;
	ss << binary;
	string str = ss.str();

	while(str.size() != 32)
	{
		if(neg)
		{
			str = "1" + str;
		}
		else
		{
			str = "0" + str;
		}
	}
	
	return str;
}





