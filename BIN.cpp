#include "BinaryParser.h"
#include <iostream>
#include <string>


/* This file reads in a 32 bit MIPS binary encoded file specified at the command line.
 * If the file is correct syntactically, each line in the file
 * will be translated into MIPS assembly code instructions and printed
 * to stdout, one per line.
 *
 */

int main(int argc, char *argv[])
{
  BinaryParser *parser;

  if(argc < 2){
    cerr << "Need to specify a binary file to translate."<<endl;
    exit(1);
  }

  parser = new BinaryParser(argv[1]);

  if(parser->isFormatCorrect() == false){
    cerr << "Format of input file is incorrect " << endl;
    exit(1);
  }

  Instruction i;
  stringstream ss;

  //Iterate through instructions, printing each encoding.
  i = parser->getNextInstruction();
  while( i.getOpcode() != UNDEFINED){
    // cout << i.getString() << endl;
		string endcoding = i.getEncoding();
		string decoding = i.getDecoding();
		
		if(decoding == "error")
		{
			cerr << "Format of input file is incorrect, invalid instruction" << endl;
			exit(1);
		}

    ss << "mach: " << i.getEncoding() << "   asm: " <<  i.getDecoding() << endl;
    i = parser->getNextInstruction();
  }

	cout << ss.str();
  
  delete parser;
}
