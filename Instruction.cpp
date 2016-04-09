#include "Instruction.h"
#include <string>



Instruction::Instruction()
{
  myOpcode = UNDEFINED;
  myRS = myRT = myRD = NumRegisters; 
}

Instruction::Instruction(Opcode op, Register rs, Register rt, Register rd, int imm)
// You can specify all the fields to initialize the Instruction
{
  setValues(op, rs, rt, rd, imm);
}

Instruction::Instruction(Opcode op, Register rs, Register rt, Register rd, int imm, string address)
// You can specify all the fields to initialize the Instruction
{
  setValues(op, rs, rt, rd, imm, address);
}

void Instruction::setValues(Opcode op, Register rs, Register rt, Register rd, int imm)
// You can specify all the fields to initialize the Instruction
{

  myOpcode = op;
  if(op < 0 || op >= UNDEFINED)
    myOpcode = UNDEFINED;

  myRS = rs;
  if(rs < 0 || rs >= NumRegisters)
    myRS = NumRegisters;

  myRT = rt;
  if(rt < 0 || rt >= NumRegisters)
    myRT = NumRegisters;

  myRD = rd;
  if(rd < 0 || rd >= NumRegisters)
    myRD = NumRegisters;

  myImmediate = imm;


}

void Instruction::setValues(Opcode op, Register rs, Register rt, Register rd, int imm, string address)
// You can specify all the fields to initialize the Instruction
{

  myOpcode = op;
  if(op < 0 || op >= UNDEFINED)
    myOpcode = UNDEFINED;

  myRS = rs;
  if(rs < 0 || rs >= NumRegisters)
    myRS = NumRegisters;

  myRT = rt;
  if(rt < 0 || rt >= NumRegisters)
    myRT = NumRegisters;

  myRD = rd;
  if(rd < 0 || rd >= NumRegisters)
    myRD = NumRegisters;

  myImmediate = imm;
  myAddress   = address;

}
/*
int  getRS()
{
		return myRS;
}

int  getRT()
{
		return myRS;
}

int  getRD()
{
		return myRS;
}

int  getImm()
{
		return myImmediate;
}
*/

void Instruction::setDecoding(string d)
{
		myDecoding = d;
}

string Instruction::getDecoding()
{
		return myDecoding;
}

string Instruction::getString()
// Returns a string which represents all of the fields 
{
  stringstream s ;
  s << "OP: \t" << myOpcode << "\t" << "RD: " << myRD << "\t" << 
    "RS: " << myRS << "\t" << "RT: " << "\t" << myRT << "\t" <<
    "Imm: " << myImmediate;
  
  return s.str();
  
}

