#include <fstream>
#include <iostream>

#include "ASMParser.h"
#include "InstructionMem.h"
#include "RegisterFile.h"
#include "Instruction.h"
#include "RegisterTable.h"
#include "Opcode.h"
//#include "PC.h"

using namespace std;

// Ryan Eghrari - re9rk
// Put ur names here guys?

// This program accepts one command line arguements, being the name
// of the config file that will contain:
// program_input         : <filename>
// memory_contents_input : <filename>
// register_file_input   : <filename>
// output_mode           : <string>
// debug_mode            : <bool>
// print_memory_contents : <bool>

int main(int argc, char* argv[]){
    
/*********************Config**********************/
    
	if(argc != 2){
        cout << "Usage: " << argv[0] << " <config file name>" << endl;
        exit(0);
    }
    
    const int  MAX_ENTRIES = 15;
	string delim = "=";

	string     inputFileName;
	string     memFileName;
	string     regFileName;
	bool       outputMode; //true if single_step
	bool       debugMode;
	bool       printContents;
     
    string configFileName = argv[1];
    
    ifstream in;
    in.open(configFileName);
    
    if(!in.is_open()){
        cout << "Failed to open config file" << endl;
        exit(0);
    }
	
    int entries = 0;
    while(in.good()){
        if(entries >= MAX_ENTRIES){
            cerr << "Config file to large, " << MAX_ENTRIES <<  " entries max." << endl;
            break;
        }	
		
		string str;
		in >> str;

        //cout << "s: |" << str << "|" << endl;
		string token = str.substr(0,str.find(delim));
        //cout << "t: |" << token <<"|" << endl;
		if(token == "program_input")
		{
			inputFileName = str.substr((str.find(delim)+1),str.length());
		}
		else if(token == "memory_contents_input")
		{
			memFileName = str.substr((str.find(delim)+1),str.length());
		}
		else if(token == "register_file_input")
		{
			regFileName = str.substr((str.find(delim)+1),str.length());
		}
		else if(token == "output_mode")
		{
			if("single_step" == str.substr((str.find(delim)+1),str.length()))
			{
				outputMode = true;
			}
			else if("batch" == str.substr((str.find(delim)+1),str.length()))
			{
				outputMode = false;
			}
			else
			{
				cerr << "invalid output mode" << endl;
				cerr << "invalid config file" << endl;
			    exit(0);
			}
		}
		else if(token == "debug_mode")
		{
			if("true" == str.substr((str.find(delim)+1),str.length()))
			{
				debugMode = true;
			}
			else if("false" == str.substr((str.find(delim)+1),str.length()))
			{
				debugMode = false;
			}
			else
			{
				cerr << "invalid config file, mispelled boolean" << endl;
				exit(0);
			}
		}
		else if(token == "print_memory_contents")
		{
			if("true" == str.substr((str.find(delim)+1),str.length()))
			{
				printContents = true;
			}
			else if("false" == str.substr((str.find(delim)+1),str.length()))
			{
				printContents = false;
			}
			else
			{
				cerr << "invalid config file, mispelled boolean" << endl;
				exit(0);
			}
		}
		else if(token == "")
		{
			//nothing there 
			//cout << "empty at: " << entries << endl;
		}
		else if(str.at(0) == '#')
		{
			getline(in,str);
			//cout << "# at: " << entries << endl;
		}
		else if(str.find_first_not_of(' ') == std::string::npos)
		{
			//all white space
		}
		else
		{
			cerr << "invalid config file" << endl;
            exit(0);
		}
        
		if(in.fail())break;
        
		entries++;
    }

	cout << inputFileName << endl;
	cout << memFileName   << endl;
	cout << regFileName   << endl;
	cout << outputMode    << endl;
	cout << debugMode     << endl;
	cout << printContents << endl;
	
	in.close();
/*************************************************************/


/*********************Instruction Memory**********************/

	vector<string> instructionMemory;

/*
	InstructionMem instructionMemory;
*/

	ASMParser *parser;

	parser = new ASMParser(inputFileName);

	if(parser->isFormatCorrect() == false){
		cerr << "Format of ASM input file is incorrect" << endl;
		exit(1);
	}

	Instruction i;

	//Iterate through instructions, printing each encoding.
	i = parser->getNextInstruction();
	
	while( i.getOpcode() != UNDEFINED)
	{
		// cout << i.getString() << endl;
		cout << i.getEncoding() << endl;

		instructionMemory.push_back(i.getEncoding());

		//instructionMemory.setInstruction(i);

		i = parser->getNextInstruction();
	}

	delete parser;

	//instructionMemory.print();


/*************************************************************/

/*********************PC **************************/

//	PC pc(instructionMemory.size());
	
    //print instruction mem.
/*************************************************************/

/*********************Register file **************************/

	RegisterFile registerFile(regFileName);

    registerFile.printRegContents();	

/*************************************************************/

/*********************Register file **************************/

	MeUnit registerFile(regFileName);

    registerFile.printRegContents();	

/*************************************************************/


    
    return(0);
}
