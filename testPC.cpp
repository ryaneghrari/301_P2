#include "InstructionMem.h"
#include "Instruction.h"

using namespace std;

int main()
{		
	InstructionMem m;
	Instruction i;


	cout << "PC:  " << m.getPCAddress() << endl;
	m.setInstruction(i);
 	cout << "I: " << m.getInstruction("0x4004").getString() << endl;;

    //cout << i.getString() << endl;
  	//m.print();

	for(int i = 0; i < 10; i++)
	{
		cout << m.getNextInstruction().getString() << endl;
	}
	
	m.setInstruction(i);
	m.setInstruction(i);
	m.setInstruction(i);
	m.setInstruction(i);

	for(int i = 0; i < 10; i++)
	{
		cout << m.getNextInstruction().getString() << endl;
	}
	
	
	vector<Instruction> vec1;
	vec1.push_back(i);
	vec1.push_back(i);
	vec1.push_back(i);
	vec1.push_back(i);
	vec1.push_back(i);
	vec1.push_back(i);
	vec1.push_back(i);
	vec1.push_back(i);
	vec1.push_back(i);
	vec1.push_back(i);
	
	InstructionMem m2(vec1);
	
	for(int i = 0; i < 15; i++)
	{
		cout << m2.getNextInstruction().getString() << endl;
	}


}
