#include "InstructionMem.h"

/*
* Default
*/
InstructionMem::InstructionMem() : PC(0), endIndex(0), myInstructions(MAXINSTRUCTIONS)
{
//	cout << "constructing InstructionMem with max: " << MAXINSTRUCTIONS << "instructions" << endl;
}	

/*
* Accepts a vector of instructions and initializes the PC
*/
InstructionMem::InstructionMem(vector<Instruction> instrs) : PC(0), myInstructions(MAXINSTRUCTIONS)
{
//	cout << "constructing InstructionMem with Instruction vector" << endl;
	
	for(int i = 0; i < instrs.size(); i++)
	{
		myInstructions[i] = instrs[i];
		endIndex = i; //Keep track of the last instruction
	}
}

/*
* Destructor 
*/
InstructionMem::~InstructionMem(){}

/*
* Set an instruction at a certain address
*/
void InstructionMem::setInstruction(Instruction instruction)
{
//	cout << "setting Instruction: " << instruction.getString() << "  with address  " << address << endl;

	int index = endIndex + 1; //DO THIS get index from the address;
	
	if(index > (MAXINSTRUCTIONS-1)|| index < 0)
	{
		cerr << "Cannot set Instruction greater than max Instruction nor below 0x4000" << endl;
		return;
	}

	//set the instruction 
	myInstructions[index] = instruction;

	//keep track of the last instruction added	
	if(index > endIndex)
	{
		endIndex = index; 
	}
}

/*
* Gets an instruction given a memory address
*/
Instruction InstructionMem::getInstruction(string address)
{
	//cout << "getting instruction at address: " << address << endl;
	
	int index = (address_index(address) - STARTADDRESS); //get index from address
	index = index / 4;
   
    cout << "index: " << index << endl;
	if(index > (MAXINSTRUCTIONS-1) || index < 0 || index > endIndex)
	{
		cerr << "address out of bounds in get Instruction" << endl;
	}

	return myInstructions[index];
}

/*
* 1) Gets Instruction the PC is pointing to
* 2) Advances the PC
* if the PC is pointing to the last instruction it will not advance
* the PC
*/
Instruction InstructionMem::getNextInstruction()
{
	//cout << "getting next Instruction: " << endl;	

    //increment PC
	int temp = PC;
	PC = PC + 1;

	//return the last instruction if called whilst PC is pointing to the last instruction
	if(PC >= endIndex)
	{
		PC = endIndex;
	}
    
	cout << "PC: " << temp << endl;
	return myInstructions[temp];
}

/*
* Returns the HEX address of the Program Counter
*/
string InstructionMem::getPCAddress()
{
	return index_address(PC);
}

/*
* Converts an address to an index of the instruction memory
*/
int InstructionMem::address_index(string address)
{
	stringstream stream;
	
	address = address.substr(2); //cut of the 0x

	stream << address;

	int index;
	stream >> hex >> index;

	cout << "converting address: " << address << "  to index: " << index << endl;
	return index;
}

/*
* Converts an index of the Instruction memory to a HEX address,
* by multiplying the index by 4, and adding the start addresss.
*/
string InstructionMem::index_address(int index)
{

	int num = ((index * 4) + STARTADDRESS);
	string address = int_hex(num);
	
	cout << "converting index: " << index << "  to address: " << address << endl;
	return address;
}

/*
* Converts an integer to hex string
*/
string InstructionMem::int_hex(int integer)
{

	stringstream stream;
	stream << hex << "0x" << integer;

	cout << "converting int: " << integer << "  to hex: " << stream.str() << endl;
	return stream.str();
}

void InstructionMem::print()
{
	for(int i = 0; i < myInstructions.size(); i++)
	{  
			cout << i << "\t" << myInstructions[i].getString() << endl;
	}
}


