#Makefile for Project 1 301

CC = g++	#compiler to use
LD = $(CC)	#command used to link objects

INCDIR = -I../	#additional directories to look for include files

CCFLAGS = -Wall -Wno-deprecated $(INCDIR) -g -c	#compiler options
LDFLAGS = -Wall -Wno-deprecated -g		#linker options

OBJS = ASM.o BIN.o Run.o ASMParser.o BinaryParser.o Instruction.o Opcode.o RegisterTable.o InstructionMem.o
EXECS = BIN ASM RUN

all:    $(EXECS)

RUN: Run.o Instruction.o ASMParser.o Opcode.o RegisterTable.o RegisterFile.o DataMemory.o Control.o ALU.o PC.o
	$(CC) -Wall -o RUN Run.o Instruction.o ASMParser.o Opcode.o RegisterTable.o RegisterFile.o DataMemory.o Control.o ALU.o PC.o

BIN: BIN.o Instruction.o Opcode.o RegisterTable.o BinaryParser.o 
	$(CC) -Wall -o BIN BIN.o Opcode.o BinaryParser.o RegisterTable.o Instruction.o

ASM: ASM.o Instruction.o Opcode.o RegisterTable.o ASMParser.o 
	$(CC) -Wall -o ASM ASM.o Opcode.o ASMParser.o RegisterTable.o Instruction.o

ALU.o: ALU.h

Control.o: Control.h

PC.o: PC.h

DataMemory.o: DataMemory.h

RegisterFile.o: RegisterFile.h

ASMParser.o: ASMParser.h Opcode.h RegisterTable.h Instruction.h

BinaryParser.o: BinaryParser.h Opcode.h RegisterTable.h Instruction.h

#InstructionMem.o: Opcode.h RegisterTable.h Instruction.h InstructionMem.h

Instruction.o: Opcode.h RegisterTable.h Instruction.h

Opcode.o: Opcode.h

RegisterTable.o: RegisterTable.h

clean:
	/bin/rm -f $(OBJS) $(EXECS)
