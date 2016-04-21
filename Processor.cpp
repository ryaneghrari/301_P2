#include <iostream>
#include <string>
#include <array>
#include "PC.h"
#include "RegisterFile.h"
#include "Control.h"
#include "ALU.h"
#include "DataMemory.h"

using namespace std;


//if the control bool is 0 input1 is returned 
//if the bool is 1 then input2 is returned
string multiplexorAction(string input1, string input2, bool control) {
	if (control == false)
		return input1;
	else
		return input2;
}

//pads the front of the string with 0 if positive and 1s if negative
string signExtend(string data) {
	if (data.at(0) == '1') {
		while (data.size() < 32) {
			data = '1' + data;
		
		}
		return data;
	}
	else {
		while (data.size() < 32) {
			data = '0' + data;
		}
		return data;

	}
}

int main(int argc,char *argv[]) {

	//****************INITIALIZE EACH UNIT OF MIPS DATAPATH***************************
	//***********THIS WILL BE MOVED TO CLASS THAT HAS INSTANCE OF PROCESSOR***********

	//initalize the instruction memory based on input
	string instructionMem [4] = {"00000000010000110000100000101010", "00001000000000000100000000001100", "00000000100010000001100000100000", "10001100010000010000000000000100"};
	int instructionSize = 4;
	//create a PC counter
	PC myPC = PC(instructionSize);
	//Initalize the register file
	string binaryArry [32] = {"00000000000000000000000000000000","00000000000000000000000000000011",
							  "00010000000000000000000000000000","00000000100010000001100000100010",
							  "00001000000100000000000000000010","00000000100010000001100000100011",
							  "00001000000100000000000000000011","00000000100010000001100000100100",
							  "00001000000100000000000000000100","00000000100010000001100000100101",
							  "00001000000100000000000000000101","00000000100010000001100000100110",
							  "00001000000100000000000000000110","00000000100010000001100000100111",
							  "00001000000100000000000000000111","00000000100010000001100000101000",
							  "00001000000100000000000000001000","00000000100010000001100000101001",
							  "00001000000100000000000000001001","00000000100010000001100000101010",
							  "00001000000100000000000000001010","00000000100010000001100000101011",
							  "00001000000100000000000000001011","00000000100010000001100000101100",
							  "00001000000100000000000000001100","00000000100010000001100000101101",
							  "00001000000100000000000000001101","00000000100010000001100000101110",
							  "00001000000100000000000000001110","00000000100010000001100000101111",
							  "00001000000100000000000000001111","00000000100010000001100000100000",};

	RegisterFile myRegFiles = RegisterFile(binaryArry);
	ControlTable myControl = ControlTable();
	ALU MyALU = ALU();
	DataMemory myDataMemory = DataMemory(binaryArry);


	//***************************BEGIN THE PROCESSOR********************************
	while(myPC.IsPCValid()) {
		string currentInstruction  = instructionMem[myPC.getPCIndex()];

		string binaryOpcode = currentInstruction.substr(0,6);
		string binaryFunct = currentInstruction.substr(26,6);

		Opcode o = myControl.findOpcode(binaryOpcode,binaryFunct);

		cout << "The instruction is: " << currentInstruction << "\n";
		cout << "The opcode is: " << myControl.getName(o) << "\n";

		//corresponds to bits 25 to 21 from insruction
		string ReadReg1 = currentInstruction.substr(6,5);
		string ReadReg2 = currentInstruction.substr(11,5);
		//data from the register files
		string dataFromReg1 = myRegFiles.ReadData(ReadReg1);
		string dataFromReg2 = myRegFiles.ReadData(ReadReg2);

		cout << "data going into the Register file " << ReadReg1 << " " << ReadReg2 << "\n";

		//sign extend bits 15 through 0
		string imm = currentInstruction.substr(16,16);
		imm = signExtend(imm);
		cout << "the sign extended imm field " << imm << "\n";



		// determines the second input to ALU
		string ALUInput2 = multiplexorAction(dataFromReg2,imm,myControl.getALUSrc(o));

		cout << "second multiplexor that picks second ALU value input 1: " << dataFromReg2 << "\n";
		cout << "second multiplexor input 2: " << imm << "\n";
		cout << "second multiplexor output: " << ALUInput2 << "\n";

		//use ALU to calculate based on opcode
		string ALUResult = MyALU.calculate(dataFromReg1,ALUInput2,myControl.getName(o));

		cout << "input to ALU: " << dataFromReg1 << " " << ALUInput2 << " " << myControl.getName(o) << "\n";
		cout << "output of ALU: " << ALUResult << "\n";

		//send calculation to data memory to determine if we need to write or read to memory
		string DataFromMem = "00000000000000000000000000000000";
		if (myControl.getMemRead(o) == true) {
			DataFromMem = myDataMemory.readData(ALUResult);
		}
		if (myControl.getMemWrite(o) == true) {
			//first param stores the data you want to save into memory at the location of ALUResult in memory
			myDataMemory.writeData(dataFromReg2,ALUResult);
		}

		//memToReg stories the data that will be stored back in the registers. 
		string memToReg = multiplexorAction(ALUResult,DataFromMem,myControl.getMemtoReg(o));
		//corresponds to bits 20 through 16 from the instruction
		string input1 = currentInstruction.substr(11,5);
		//corresponds to bits 15 to 11 from the instruction
		string input2 = currentInstruction.substr(16,5);
		//output of the multiplexor that decides what to send to write register
		string writeReg = multiplexorAction(input1,input2,myControl.getRegDst(o));
		//stores memtoReg at the register given by the binary of writeReg
		string name = myControl.getName(o);
		if (myControl.getRegWrite(o) == true) {
			myRegFiles.writeRegister(memToReg,writeReg);
		}

		cout << "deciding what to send to reg \n";
		cout << "input 1: (from alu)" << ALUResult << "\n";
		cout << "input 2: (from mem)" << DataFromMem << "\n";
		cout << "the control for regDest (FOR data): " << myControl.getMemtoReg(o) << "\n";
		cout << " the output of multiplexor is " << memToReg << "\n";

		cout << "input 1: " << input1 << "\n";
		cout << "input 2: " << input2 << "\n";
		cout << "the control for regDest (FOR WRITING): " << myControl.getRegDst(o) << "\n";
		cout << " the output of multiplexor is " << writeReg << "\n";

		//figuring out the next instruction for PC if a branch
		string branchedInsruction = MyALU.add(currentPCInBinary,MyALU.sll(imm));
		//increase pc by 4 
		int p = myPC.getPCIndex()+1;
		myPC.setPCIndex(p);
		string currentPCInBinary = myPC.getPCAsBinary(); 

		cout << " current pc: " << myPC.getPC() << " binary " << currentPCInBinary << "\n";
		bool operandForBranch = false;
		if (myControl.getBranch(o) && ALUResult == "true") {
			operandForBranch = true;
		} 
		string potNextInstruction = multiplexorAction(currentPCInBinary,branchedInsruction,operandForBranch);

		cout << "deciding what is potential next instruction  \n";
		cout << "input 1: (curent instruction + 4)" << currentPCInBinary << "\n";
		cout << "input 2: (branch)" << branchedInsruction << "\n";
		cout << "the control for regDest (FOR data): " << myControl.getMemtoReg(o) << "\n";
		cout << " the output of multiplexor is " << memToReg << "\n";


		//calculate jump instruction 
		string jumpInstruction = "0000" + MyALU.sll(currentInstruction.substr(6));
		string nextInstruction = multiplexorAction(potNextInstruction,jumpInstruction,myControl.getJump(o));

		myPC.convertNextToPC(nextInstruction);

		cout << "next index is: " << myPC.getPCIndex() << "\n";








		
		cout << "\n \n \n";



	}
}