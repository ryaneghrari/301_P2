#ifndef __BINPARSER_H__
#define __BINPARSER_H__



#include <iostream>
#include <fstream>
#include "Instruction.h"
#include "Opcode.h"
#include <vector>
#include <sstream>
#include <stdlib.h>

/* This class reads in a MIPS assembly file and checks its syntax.  If
 * the file is syntactically correct, this class will retain a list 
 * of Instructions (one for each instruction from the file).  This
 * list of Instructions can be iterated through.
 */
   

class BinaryParser{
 public:
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
  BinaryParser(string filename);

  // Returns true if the file specified was syntactically correct.  Otherwise,
  // returns false.
  bool isFormatCorrect() { return myFormatCorrect; };
  
	//for a binary string makes sure it is 32 bits long with all 0 and 1s
	bool goodFormat(string s);

	//InstType getType(string line);

  // Iterator that returns the next Instruction in the list of Instructions.
  Instruction getNextInstruction();

 private:
  vector<Instruction> myInstructions;      // list of Instructions
  int myIndex;                             // iterator index
  bool myFormatCorrect;

  RegisterTable registers;                 // encodings for registers
  OpcodeTable opcodes;                     // encodings of opcodes
  int myLabelAddress;                      // Used to assign labels addresses
  



  // Decomposes a line of assembly code into strings for the opcode field and operands, 
  // checking for syntax errors and counting the number of operands.
  void getTokens(string line, string &opcode, string *operand, int &num_operands);

  // Given an Opcode, a string representing the operands, and the number of operands, 
  // breaks operands apart and stores fields into Instruction.
  bool getOperands(Instruction &i, Opcode o, string *operand, int operand_count);
	
	bool isNumberString(string s); 

  int cvtNumString2Number(string s);
  
	// Helper functions
  bool isWhitespace(char c)    { return (c == ' '|| c == '\t'); };
  bool isDigit(char c)         { return (c >= '0' && c <= '9'); };
  bool isAlphaUpper(char c)    { return (c >= 'A' && c <= 'Z'); };
  bool isAlphaLower(char c)    { return (c >= 'a' && c <= 'z'); };
  bool isSign(char c)          { return (c == '-' || c == '+'); };
  bool isAlpha(char c)         {return (isAlphaUpper(c) || isAlphaLower(c)); };
  


  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
  Instruction  decode(string s);

  Instruction  decodeR(string s);

  Instruction  decodeI(string s);

  Instruction  decodeJ(string s);

  int    binaryToDecimal(string s);

  string decimalToHex(int num);
};

#endif
