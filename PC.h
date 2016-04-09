#include "Instruction.h"

using namespace std;
 
/**
   Header file for the PC class.
*/

class PC
{
     private:
         //Instruction myInstructions[];
		 int          numInstructions;

     public:
         PC();
         //PC(Instruction instructions[]);
         ~PC();

		 //Instruction getInstruction(int index);
		 int         getNumInstructions(){return numInstructions;}

};
