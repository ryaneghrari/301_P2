#Makefile for Project 1 301

CC = g++	#compiler to use
LD = $(CC)	#command used to link objects

INCDIR = -I../	#additional directories to look for include files

CCFLAGS = -Wall -Wno-deprecated $(INCDIR) -g -c	#compiler options
LDFLAGS = -Wall -Wno-deprecated -g		#linker options

OBJS = ASMParser.o BinaryParser.o Instruction.o Opcode.o RegisterTable.o
EXECS = BIN ASM

all:    $(EXECS)

BIN: BIN.o Instruction.o Opcode.o RegisterTable.o BinaryParser.o 
	$(CC) -Wall -o BIN BIN.o Opcode.o BinaryParser.o RegisterTable.o Instruction.o

ASM: ASM.o Instruction.o Opcode.o RegisterTable.o ASMParser.o 
	$(CC) -Wall -o ASM ASM.o Opcode.o ASMParser.o RegisterTable.o Instruction.o

ASMParser.o: ASMParser.h Opcode.h RegisterTable.h Instruction.h

BinaryParser.o: BinaryParser.h Opcode.h RegisterTable.h Instruction.h

Instruction.o: Opcode.h RegisterTable.h Instruction.h

Opcode.o: Opcode.h

RegisterTable.o: RegisterTable.h

clean:
	/bin/rm -f $(OBJS) $(EXECS)
