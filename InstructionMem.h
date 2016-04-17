#include "Instruction.h"
#include <vector>

using namespace std;
 
/**
   Header file for the PC class.
*/

class InstructionMem
{
     static const int MAXINSTRUCTIONS = 100;
     static const int STARTADDRESS    = 16384; //0x4000
	 private:
         vector<Instruction> myInstructions;
		 int                 PC; //0 corresponds to 0x4000
		 int				 endIndex; //position of the last instruction
		 int                 address_index(string address);
		 string              index_address(int index);
		 string              int_hex(int integer);

     public:
         InstructionMem();
         InstructionMem(vector<Instruction> instrs);
         ~InstructionMem();

		 Instruction getInstruction(string address);
		 Instruction getNextInstruction();

		 string      getPCAddress();
		
		 void        setInstruction(Instruction instruction);
		
		 void        print();
};
