#include "Instruction.h"
#include <vector>

using namespace std;
 
/**
   Header file for the PC class.
*/

class PC
{
     private:
         vector<Instruction> myInstructions;
		 int          numInstructions;

     public:
         PC();
         PC(vector<Instruction> instrs);
         ~PC();

		 Instruction getInstruction(int index);
		 int         getNumInstructions(){return numInstructions;}
		 bool        isEmpty();

};
