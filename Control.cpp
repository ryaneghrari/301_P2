#include "Control.h"

ControlTable::ControlTable() {
	myArray[ADD].name = "add"; myArray[ADD].op_field = "000000"; myArray[ADD].funct_field = "100000";
	myArray[ADD].RegDst = true; myArray[ADD].ALUSrc = false; myArray[ADD].MemtoReg = false; myArray[ADD].RegWrite = true;
	myArray[ADD].MemRead = false; myArray[ADD].MemWrite = false; myArray[ADD].Branch = false; 
	myArray[ADD].ALUOp1 = true; myArray[ADD].ALUOp2 = false; myArray[ADD].Jump = false;

	//still need to add ADDI  


	myArray[SUB].name = "sub"; myArray[SUB].op_field = "000000"; myArray[SUB].funct_field = "100010";
	myArray[SUB].RegDst = true; myArray[SUB].ALUSrc = false; myArray[SUB].MemtoReg = false; myArray[SUB].RegWrite = true;
	myArray[SUB].MemRead = false; myArray[SUB].MemWrite = false; myArray[SUB].Branch = false; 
	myArray[SUB].ALUOp1 = true; myArray[SUB].ALUOp2 = false; myArray[SUB].Jump = false;

	myArray[SLT].name = "slt"; myArray[SLT].op_field = "000000"; myArray[SLT].funct_field = "101010";
	myArray[SLT].RegDst = true; myArray[SLT].ALUSrc = false; myArray[SLT].MemtoReg = false; myArray[SLT].RegWrite = true;
	myArray[SLT].MemRead = false; myArray[SLT].MemWrite = false; myArray[SLT].Branch = false; 
	myArray[SLT].ALUOp1 = true; myArray[SLT].ALUOp2 = false; myArray[SLT].Jump = false;

	myArray[LW].name = "lw"; myArray[LW].op_field = "100011"; myArray[LW].funct_field = "000000";
	myArray[LW].RegDst = false; myArray[LW].ALUSrc = true; myArray[LW].MemtoReg = true; myArray[LW].RegWrite = true;
	myArray[LW].MemRead = true; myArray[LW].MemWrite = false; myArray[LW].Branch = false; 
	myArray[LW].ALUOp1 = false; myArray[LW].ALUOp2 = false; myArray[LW].Jump = false;

	myArray[SW].name = "sw"; myArray[SW].op_field = "101011"; myArray[SW].funct_field = "000000";
	myArray[SW].RegDst = false; myArray[SW].ALUSrc = true; myArray[SW].MemtoReg = false; myArray[SW].RegWrite = false;
	myArray[SW].MemRead = false; myArray[SW].MemWrite = true; myArray[SW].Branch = false; 
	myArray[SW].ALUOp1 = false; myArray[SW].ALUOp2 = false; myArray[SW].Jump = false;

	myArray[BEQ].name = "beq"; myArray[BEQ].op_field = "000100"; myArray[BEQ].funct_field = "000000";
	myArray[BEQ].RegDst = false; myArray[BEQ].ALUSrc = false; myArray[BEQ].MemtoReg = false; myArray[BEQ].RegWrite = false;
	myArray[BEQ].MemRead = false; myArray[BEQ].MemWrite = false; myArray[BEQ].Branch = true; 
	myArray[BEQ].ALUOp1 = false; myArray[BEQ].ALUOp2 = true; myArray[BEQ].Jump = false;

	myArray[J].name = "jump"; myArray[J].op_field = "000010"; myArray[J].funct_field = "000000";
	myArray[J].RegDst = false; myArray[J].ALUSrc = false; myArray[J].MemtoReg = false; myArray[J].RegWrite = false;
	myArray[J].MemRead = false; myArray[J].MemWrite = false; myArray[J].Branch = false; 
	myArray[J].ALUOp1 = false; myArray[J].ALUOp2 = false; myArray[ADD].Jump = true;
}

//takes in machine instruction and returns the corresponfing opcode 
//if the instruction is not the opcodetable returns UNDEFINED
Opcode ControlTable::findOpcode(string binaryOpcode, string binaryFunct) {
	//if the opcode is 000000 then it is a r-type and you must look at the funct value
	if (binaryOpcode == "000000") {
		//iterates through the elements all opcodes
		for (int i=0; i<(int)UNDEFINED; i++) {
			//if the funct field of the binary matches one in the table we know that the instruction must be that opcode
			if (myArray[i].funct_field == binaryFunct && myArray[i].op_field == binaryOpcode)
				return (Opcode)i;
		}
	}
	//if not 000000 then we only have to check op-field
	else {
		//iterates through the opcodes
		for (int j=0; j < (int)UNDEFINED; j++) {
			//if the opcodes match then the instruction is that opcode
			if (myArray[j].op_field == binaryOpcode)
				return (Opcode)j;
		}
	}

	//if instruction cannot be found return UNDEFINED
	return UNDEFINED;
}

//given an Opcode, returns the name of the opcode 
//returns -1 if this area is not used
string ControlTable::getName(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return "-1";
	return myArray[o].name;
}

//given an Opcode, returns the value of RegDst control value 
//returns -1 if this area is not used
bool ControlTable::getRegDst(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].RegDst;
}

//given an Opcode, returns the value of ALUSrc control value 
//returns -1 if this area is not used
bool ControlTable::getALUSrc(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].ALUSrc;
}

//given an Opcode, returns the value of MemToReg control value 
//returns -1 if this area is not used
bool ControlTable::getMemtoReg(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].MemtoReg;
}

//given an Opcode, returns the value of regWrite control value 
//returns -1 if this area is not used
bool ControlTable::getRegWrite(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].RegWrite;
}

//given an Opcode, returns the value of MemRead control value 
//returns -1 if this area is not used
bool ControlTable::getMemRead(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].MemRead;
}

//given an Opcode, returns the value of MemWrite control value 
//returns -1 if this area is not used
bool ControlTable::getMemWrite(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].MemWrite;
}

//given an Opcode, returns the value of Branch control value 
//returns -1 if this area is not used
bool ControlTable::getBranch(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].Branch;
}

//given an Opcode, returns the value of ALUOp1 control value 
//returns -1 if this area is not used
bool ControlTable::getALUOp1(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].ALUOp1;
}

//given an Opcode, returns the value of ALUOp2 control value 
//returns -1 if this area is not used
bool ControlTable::getALUOp2(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].ALUOp2;
}

//given an Opcode, returns the value of Jump control value 
//returns -1 if this area is not used
bool ControlTable::getJump(Opcode o) {
	if (o < 0 || o >= UNDEFINED)
		return -1;
	return myArray[o].Jump;
}


