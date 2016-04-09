#include "Instruction.h"

using namespace std;
 
/**
   Header file for the PC class.
*/

class PC
{
     private:
         Instructions myInstructions[];
		 int          numInstructions;

     public:
         PC();
         PC(Intructions[] instructions);
         ~PC();

		 Instruction getInstruction(int index);
		 int         getNumInstructions(){return numInstructions}

};
