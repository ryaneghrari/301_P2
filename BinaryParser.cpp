#include "BinaryParser.h"
#include <iostream>
#include <string>

using namespace std;


BinaryParser::BinaryParser(string filename)
  // Specify a text file containing binary.
  // checks syntactic correctness of file.
{
  Instruction i;
  myFormatCorrect = true;

  myLabelAddress = 0x400000;

  ifstream in;
  in.open(filename.c_str());
  if(in.bad()){
    myFormatCorrect = false;
  }
  else{
    string line;
    while( getline(in, line)){

      /*
			* Check to make sure the file is good format
			*/
			if(goodFormat(line) == false)
			{
				myFormatCorrect = false;
				break;
			}
        	
      /*
			* Get an instruction with the decode field set
			*/
	    i = decode(line);         
    
      line.resize(32);           //cut off the '/n'
			i.setEncoding(line);       //set the encoding string


      //cout << "encod: " << i.getEncoding() << "  decod: " << i.getDecoding() << endl;
	   	//  cout << i.getString() << endl;	
		  myInstructions.push_back(i);

    }
  }

  myIndex = 0;
}


Instruction BinaryParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }
  
  Instruction i;
  return i;

}


bool BinaryParser::goodFormat(string line)
{
	if(line.empty())
	{
		return false;
	}

	int length = line.size() - 1;

	if(length > 32)
	{
			return false;
	}

	for(int i = 0; i < 32; i++)
	{
		if(line.at(i) != '0' && line.at(i) != '1')
		{
			return false;
		}
	}

	return true;
}



void BinaryParser::getTokens(string line,
			       string &opcode,
			       string *operand,
			       int &numOperands)
  // Decomposes a line of assembly code into strings for the opcode field and operands, 
  // checking for syntax errors and counting the number of operands.
{
    // locate the start of a comment
    string::size_type idx = line.find('#');
    if (idx != string::npos) // found a ';'
	line = line.substr(0,idx);
    int len = line.length();
    opcode = "";
    numOperands = 0;

    if (len == 0) return;
    int p = 0; // position in line

    // line.at(p) is whitespace or p >= len
    while (p < len && isWhitespace(line.at(p)))
	p++;
    // opcode starts
    while (p < len && !isWhitespace(line.at(p)))
    {
	opcode = opcode + line.at(p);
	p++;
    }
    //    for(int i = 0; i < 3; i++){
    int i = 0;
    while(p < len){
      while ( p < len && isWhitespace(line.at(p)))
	p++;

      // operand may start
      bool flag = false;
      while (p < len && !isWhitespace(line.at(p)))
	{
	  if(line.at(p) != ','){
	    operand[i] = operand[i] + line.at(p);
	    flag = true;
	    p++;
	  }
	  else{
	    p++;
	    break;
	  }
	}
      if(flag == true){
	numOperands++;
			}
		}
}

bool BinaryParser::isNumberString(string s)
  // Returns true if s represents a valid decimal integer
{
    int len = s.length();
    if (len == 0) return false;
    if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0)))
    {
	// check remaining characters
	for (int i=1; i < len; i++)
	{
	    if (!isdigit(s.at(i))) return false;
	}
	return true;
    }
    return false;
}


int BinaryParser::cvtNumString2Number(string s)
  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
{
    if (!isNumberString(s))
    {
	cerr << "Non-numberic string passed to cvtNumString2Number"
		  << endl;
	return 0;
    }
    int k = 1;
    int val = 0;
    for (int i = s.length()-1; i>0; i--)
    {
	char c = s.at(i);
	val = val + k*((int)(c - '0'));
	k = k*10;
    }
    if (isSign(s.at(0)))
    {
	if (s.at(0) == '-') val = -1*val;
    }
    else
    {
	val = val + k*((int)(s.at(0) - '0'));
    }
    return val;
}
	

bool BinaryParser::getOperands(Instruction &i, Opcode o, 
			    string *operand, int operand_count)
  // Given an Opcode, a string representing the operands, and the number of operands, 
  // breaks operands apart and stores fields into Instruction.
{

  if(operand_count != opcodes.numOperands(o))
    return false;

  int rs, rt, rd, imm;
  imm = 0;
  rs = rt = rd = NumRegisters;

  int rs_p = opcodes.RSposition(o);
  int rt_p = opcodes.RTposition(o);
  int rd_p = opcodes.RDposition(o);
  int imm_p = opcodes.IMMposition(o);

  if(rs_p != -1){
    rs = registers.getNum(operand[rs_p]);
    if(rs == NumRegisters)
      return false;
  }

  if(rt_p != -1){
    rt = registers.getNum(operand[rt_p]);
    if(rt == NumRegisters)
      return false;

  }
  
  if(rd_p != -1){
    rd = registers.getNum(operand[rd_p]);
    if(rd == NumRegisters)
      return false;

  }

  if(imm_p != -1){
    if(isNumberString(operand[imm_p])){  // does it have a numeric immediate field?
      imm = cvtNumString2Number(operand[imm_p]);
      if(((abs(imm) & 0xFFFF0000)<<1))  // too big a number to fit
				return false;
    }
    else{ 
      if(opcodes.isIMMLabel(o)){  // Can the operand be a label?
					// Assign the immediate field an address
					imm = myLabelAddress;
					myLabelAddress += 4;  // increment the label generator
      }
      else  // There is an error
			return false;
    }

  }

  i.setValues(o, rs, rt, rd, imm);

  return true;
}

//Decodes binary string to mips instruction
Instruction BinaryParser::decode(string line)
{   
		OpcodeTable table = OpcodeTable();

		string sub   = line.substr(0,6);
		
    //cout << "substring: " << sub << endl;
	
		Opcode o     = table.findOpcode(sub);

		if(o == UNDEFINED)
		{
			cout << "UNDEFINED" << endl;
			return Instruction();
		}

		//cout << "Opcode: " << (Opcode)o << endl;

		InstType t   = table.getInstType(o);

		//cout << (InstType)t << endl;

		if(t == RTYPE){return decodeR(line);};	
		if(t == ITYPE){return decodeI(line);};
		if(t == JTYPE){return decodeJ(line);};
		
		cerr << "Error: Incorrect Opcode" << endl;
	  return Instruction();	
}


//returns mips R-type instruction of binary string s
Instruction BinaryParser::decodeR(string line)
{   
		//cout << "R type" << endl;


		OpcodeTable t = OpcodeTable();


    string s_rs     = line.substr(6,5);
		//cout << "rs: " << s_rs << "	[00100]" << endl;
		int    i_rs = binaryToDecimal(s_rs);
		//cout << "rs: " << i_rs << "	[4]" << endl;


		string s_rt     = line.substr(11,5);
		//cout << "rt: " << s_rt << "	[01000]" << endl;	
		int    i_rt = binaryToDecimal(s_rt);
		//cout << "rt: " << i_rt << "	[8]" << endl;


		string s_rd    = line.substr(16,5);
    //cout << "rd: " << s_rd << " [00011]" << endl;	
		int    i_rd = binaryToDecimal(s_rd);
		//cout << "rd: " << i_rd << "	[3]" << endl;


		string s_shift    = line.substr(21,5);
    //cout << "shift: " << s_shift << "	[00000]" << endl;	
		int    i_shift = binaryToDecimal(s_shift);
		//cout << "shift: " << i_shift << "	[0]" << endl;

		
		string s_funct = line.substr(26,6);
		Opcode opcode = t.findRtypeOpcode(s_funct);
    //cout << "s_funct: " << s_funct << "     Op: " << opcode << endl;


		Instruction i = Instruction(opcode,i_rs,i_rt,i_rd,i_shift);

		RegisterTable REG = RegisterTable();

    string decoding = ""; 	
		decoding += t.getOp(opcode);	
    decoding += " ";

	  /*
		* First positon
		*/
		if(t.RTposition(opcode) == 0)
		{
			decoding += REG.getReg(i.getRT());
			decoding += " "; 
		}
		else if(t.RSposition(opcode) == 0)
		{
			decoding += REG.getReg(i.getRS());
			decoding += " "; 
		}
		else if(t.RDposition(opcode) == 0)
		{
			decoding += REG.getReg(i.getRD());
			decoding += " "; 	
		}

	  /*
		* Second position 
		*/
		if(t.RTposition(opcode) == 1)
		{
			decoding += REG.getReg(i.getRT());
			decoding += " "; 
		}
		else if(t.RSposition(opcode) == 1)
		{
			decoding += REG.getReg(i.getRS());
			decoding += " "; 
		}
		else if(t.RDposition(opcode) == 1)
		{
			decoding += REG.getReg(i.getRD());
			decoding += " "; 	
		}
		else if(t.IMMposition(opcode) == 1)
		{
			decoding += to_string(i.getImmediate());
			decoding += "("; 
		}

		/*
		* Third position 
		*/	
		if(t.RTposition(opcode) == 2)
		{
			decoding += REG.getReg(i.getRT());
		}
		else if(t.RSposition(opcode) == 2)
		{
			decoding += REG.getReg(i.getRS());
		}
		else if(t.RDposition(opcode) == 2)
		{
			decoding += REG.getReg(i.getRD());
		}
		else if(t.IMMposition(opcode) == 2)
		{	
			decoding += to_string(i.getImmediate());
		}

		/*
		* Close Paren if need be
		*/
		if(t.IMMposition(opcode) == 1)
		{	
			decoding += ")"; 
		}

		

		i.setDecoding(decoding);

   

		return Instruction(i);
}

//returns mips I-type instruction of binary string s
Instruction BinaryParser::decodeI(string line)
{		

	  OpcodeTable t = OpcodeTable();
	//	cout << "I type" << endl;
    
		string s_opcode = line.substr(0,6);
		Opcode opcode   = t.findOpcode(s_opcode);
		//cout << "opcode: " << s_opcode << "	[001000]" << endl;
		//int    i_opcode = binaryToDecimal(s_opcode);
		//cout << "opcode: " << i_opcode << "	[?]" << endl;


		string s_rs     = line.substr(6,5);
		//cout << "rs: " << s_rs << "	[00010]" << endl;
		int    i_rs = binaryToDecimal(s_rs);
		//cout << "rs: " << i_rs << "	[?]" << endl;


		string s_rt     = line.substr(11,5);
	//	cout << "rt: " << s_rt << "	[00001]" << endl;	
		int    i_rt = binaryToDecimal(s_rt);
		//cout << "rt: " << i_rt << "	[?]" << endl;


		string s_imm    = line.substr(16,16);
   // cout << "Immediate: " << s_imm << "	[0000000001100100]" << endl;	
		int    i_imm = binaryToDecimal(s_imm);
		//cout << "immediate: " << i_imm << "	[100]" << endl;



    
		//cout << " " << line << endl;
		//cout << "[" << s_opcode << "|" << s_rs << "|" << s_rt << "|" << s_imm << "]" << endl;

		Instruction i = Instruction(opcode,i_rs,i_rt,-1,i_imm);

		RegisterTable REG = RegisterTable();

    string decoding = "";
   

	  /*
		* Instruction
		*/
		decoding += t.getOp(opcode);	
    decoding += " "; 

	  /*
		* First positon
		*/
		if(t.RTposition(opcode) == 0)
		{
			decoding += REG.getReg(i.getRT());
			decoding += " "; 
		}
		else if(t.RSposition(opcode) == 0)
		{
			decoding += REG.getReg(i.getRS());
			decoding += " "; 
		}
		else if(t.RDposition(opcode) == 0)
		{
			decoding += REG.getReg(i.getRD());
			decoding += " "; 	
		}

	  /*
		* Second position 
		*/
		if(t.RTposition(opcode) == 1)
		{
			decoding += REG.getReg(i.getRT());
			decoding += " "; 
		}
		else if(t.RSposition(opcode) == 1)
		{
			decoding += REG.getReg(i.getRS());
			decoding += " "; 
		}
		else if(t.RDposition(opcode) == 1)
		{
			decoding += REG.getReg(i.getRD());
			decoding += " "; 	
		}
		else if(t.IMMposition(opcode) == 1)
		{
			decoding += to_string(i.getImmediate());
			decoding += "("; 
		}

		/*
		* Third position 
		*/	
		if(t.RTposition(opcode) == 2)
		{
			decoding += REG.getReg(i.getRT());
		}
		else if(t.RSposition(opcode) == 2)
		{
			decoding += REG.getReg(i.getRS());
		}
		else if(t.RDposition(opcode) == 2)
		{
			decoding += REG.getReg(i.getRD());
		}
		else if(t.IMMposition(opcode) == 2)
		{	
			decoding += to_string(i.getImmediate());
		}
		else if(t.isIMMLabel(opcode))
		{	
			decoding += decimalToHex(i.getImmediate());//address
		}

		/*
		* Close Paren if need be
		*/
		if(t.IMMposition(opcode) == 1)
		{	
			decoding += ")"; 
		}

 
		/*
		*	Set decode string 
		*/
		i.setDecoding(decoding); 

		return i;
}

//returns mips J-type instruction of binary string s
Instruction BinaryParser::decodeJ(string line)
{
		//cout << "J type" << endl;

		
	  OpcodeTable t = OpcodeTable();
    
		string s_opcode = line.substr(0,6);
		Opcode opcode   = t.findOpcode(s_opcode);
		//cout << "opcode: " << s_opcode << "	[001000]" << endl;
		//int    i_opcode = binaryToDecimal(s_opcode);
		//cout << "opcode: " << i_opcode << "	[?]" << endl;

		string s_imm    = line.substr(6,25);
   // cout << "Immediate: " << s_imm << "	[0000000001100100]" << endl;	
		int    i_imm = binaryToDecimal(s_imm);

///ADD TO THE PROGRAM COUNTER




	//	cout << "immediate: " << i_imm << "	[1098240982304980]" << endl;
  //  cout << "HEX: |" << decimalToHex(i_imm) << "|"<< endl;

		string h_imm = decimalToHex(i_imm);
		Instruction i = Instruction(opcode,-1,-1,-1,-1,h_imm);

		RegisterTable REG = RegisterTable();


		string decoding = "";

		decoding += t.getOp(opcode);	
    decoding += " "; 
		decoding += i.getAddress();	

		i.setDecoding(decoding);
		i.setEncoding(line);

		return i;
}


/*Helper methods*/

int BinaryParser::binaryToDecimal(string s)
{
     if(s.size() < 16) 
		 {
			 return stoi(s,NULL,2);
		 }
		 else if(s.size() == 16)
		 {	
			 int dec; 

			 if(s.at(0) == '1')
		   {
					dec = -1 * (65536 - stoi(s,NULL,2)); 
			 }
			 else
			 {
					dec = stoi(s,NULL,2);
			 }

			 return dec;
		 }
     else if(s.size() == 25)
		 {
					
			 int dec; 

			 if(s.at(0) == '1')
		   {
					dec = -1 * (33554432 - stoi(s,NULL,2)); 
			 }
			 else
			 {
					dec = stoi(s,NULL,2);
			 }

			 return dec;
			
		 } 
		 
		 return stoi(s,NULL,2);

}

string BinaryParser::decimalToHex(int num)
{
		stringstream stream;
		stream << hex << "0x" << num;
		//cout << stream.str();
		return stream.str();
}
/**Binary to Decimal Helper methods */


//InstType BinaryParser::getType(string line)
///{

	//parse the first 6 bits
	//get the type i think i can use getOpcode or something
//	return (InstType)1;
//}



/*
//accepts the number you want to convert to binary, and the total number of bits you want(pad)
string BinaryParser::cvtDectoBin(int num, int pad)
{
  string binary = "";
  bool neg = false;

  //Check to see if number is negative
  if(num < 0)
  {
    neg = true;
    num = num * -1;
  }


  int i = 0;
  //Convert to binary
  while(num> 0)
  {
    int bit = num % 2;
    int quote = num /2;
    stringstream ss;
    ss << bit;
    string b = ss.str();
    binary = b + binary;
    num = quote;
    i++;

  }
  while(i < pad)
  {
    binary = "0" + binary;
    i++;
    
  }

  //If the number is negative it negates it by flipping all of the digits and adding 1
  if(neg){
    for(int i = 0 ; i< binary.length(); i++)
    {

      if (binary.at(i) == '0')
        binary.at(i) = '1';
      else
        binary.at(i) = '0';

    }
    bool added = false;

    //adds the 1 
    for(int j = binary.length()-1 ; j > 0  && !added; j--)
    {
      if(binary.at(j) == '0')
      {
        binary.at(j) = '1';
        for(int k = j+1; k < binary.length(); k++)
        {
          binary.at(k) = '0';
        }
        added = true;
      }   



    }
  }

  
  return binary;
}
*/

