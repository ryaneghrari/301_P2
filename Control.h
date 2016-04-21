#ifndef __Control_H__
#define __Control_H__

#include <string>

using namespace std;

//List of all supported MIPS instructions
enum Opcode {
  ADD,
  ADDI,
  SUB,
  SLT,
  LW,
  SW,
  BEQ,
  J,
  UNDEFINED
};


/*
* This class simulates the control and the ALU control in the Mips Datapath.
*/
class ControlTable {
public:
	ControlTable();

	//given an funct and opcode in binary; method finds the opcode
	Opcode findOpcode(string binaryOpcode, string binaryFunct);

	/**
	* For all the below instructions: give an opcode and recieve the corresponding control boolean value!
	*/
	bool getRegDst(Opcode o);
	bool getALUSrc(Opcode o);
	bool getMemtoReg(Opcode o);
	bool getRegWrite(Opcode o);
	bool getMemRead(Opcode o);
	bool getMemWrite(Opcode o);
	bool getBranch(Opcode o);
	bool getALUOp1(Opcode o);
	bool getALUOp2(Opcode o);
	bool getJump(Opcode o);
	string getName(Opcode o);

private:
	//used to store the control values for each opcode we use
	struct ControlTableEntry {
		string name;
		string op_field;
		string funct_field;
		bool RegDst;
		bool ALUSrc;
		bool MemtoReg;
		bool RegWrite;
		bool MemRead;
		bool MemWrite;
		bool Branch;
		bool ALUOp1;
		bool ALUOp2;
		bool Jump;

		ControlTableEntry() {

		};
	};

ControlTableEntry myArray[UNDEFINED];

};

#endif 