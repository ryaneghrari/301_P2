#include "ASMParser.h"

ASMParser::ASMParser(string filename)
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness /f file and creates a list of Instructions.
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
      string opcode("");
      string operand[80];
      int operand_count = 0;

      getTokens(line, opcode, operand, operand_count);

      if(opcode.length() == 0 && operand_count != 0){
		// No opcode but operands

		myFormatCorrect = false;
		break;
      }

      Opcode o = opcodes.getOpcode(opcode);      
      if(o == UNDEFINED){
		// invalid opcode specified
		myFormatCorrect = false;
		break;
      }

      bool success = getOperands(i, o, operand, operand_count);
      if(!success){
		myFormatCorrect = false;
		break;
      }

      string encoding = encode(i);
      i.setEncoding(encoding);

      myInstructions.push_back(i);

    }
  }

  myIndex = 0;
}


Instruction ASMParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }
  
  Instruction i;
  return i;

}

void ASMParser::getTokens(string line,
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
      i++;
    }

    
    idx = operand[numOperands-1].find('(');
    string::size_type idx2 = operand[numOperands-1].find(')');
    
    if (idx == string::npos || idx2 == string::npos ||
	((idx2 - idx) < 2 )){ // no () found
    }
    else{ // split string
      string offset = operand[numOperands-1].substr(0,idx);
      string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);
      
      operand[numOperands-1] = offset;
      operand[numOperands] = regStr;
      numOperands++;
    }
    
    

    // ignore anything after the whitespace after the operand
    // We could do a further look and generate an error message
    // but we'll save that for later.
    return;
}

bool ASMParser::isNumberString(string s)
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


int ASMParser::cvtNumString2Number(string s)
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
		

bool ASMParser::getOperands(Instruction &i, Opcode o, 
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


string ASMParser::encode(Instruction i)
  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
{
  string returner;

  // Sorts the instruction by type, and uses helper methods to encode the different types separately
  if (opcodes.getInstType(i.getOpcode()) == 0)
  {
     returner = encodeR(i);
  }
  else if (opcodes.getInstType(i.getOpcode()) == 1)
  {
    returner = encodeI(i);
  }
  else if (opcodes.getInstType(i.getOpcode()) == 2)
  {
     returner = encodeJ(i);
  }
  return returner;
}
//Encodes R type instructions with an instruction input, and a 32 bit binary string output
string ASMParser::encodeR(Instruction i)
{
  Opcode o = i.getOpcode();  
  string encoder = opcodes.getOpcodeField( i.getOpcode()); //The String encoder that will represent the encoded string
  if(opcodes.RSposition(i.getOpcode()) != -1 )              // Checks position register positions, and inputs 0's or 
    encoder = encoder + cvtDectoBin(i.getRS(),5);           // binary representation of register numbers in appropriate positions
  else
    encoder = encoder + "00000";
  if(opcodes.RTposition(i.getOpcode()) != -1)
    encoder = encoder + cvtDectoBin(i.getRT(),5);
  else
    encoder = encoder + "00000";
  if(opcodes.RDposition(i.getOpcode()) != -1)
    encoder = encoder + cvtDectoBin(i.getRD(),5);
  else
    encoder = encoder + "00000";
  if(opcodes.IMMposition(i.getOpcode()) != -1)
    encoder = encoder + cvtDectoBin(i.getImmediate(),5);
  else
    encoder = encoder + "00000";


  encoder = encoder + opcodes.getFunctField(i.getOpcode());

  return encoder;
}
//Encodes I type instructions with an instruction input, and a 32 bit binary string output
string ASMParser::encodeI(Instruction i)
{
  Opcode o = i.getOpcode();  
  string encoder = opcodes.getOpcodeField( i.getOpcode());//The String encoder that will represent the encoded string
                                                          // Checks position register positions, and inputs 0's or 
  if(opcodes.RSposition(i.getOpcode()) != -1 )            // binary representation of register numbers in appropriate positions
    encoder = encoder + cvtDectoBin(i.getRS(),5);
  else
    encoder = encoder + "00000";
  if(opcodes.RTposition(i.getOpcode()) != -1)
    encoder = encoder + cvtDectoBin(i.getRT(),5);
  else
    encoder = encoder + "00000";
  if(opcodes.IMMposition(i.getOpcode()) != -1)
    encoder = encoder + cvtDectoBin(i.getImmediate(),16);
  else
    encoder = encoder + "0000000000000000";

  


  return encoder;
}
//Encodes I type instructions with an instruction input, and a 32 bit binary string output
string ASMParser::encodeJ(Instruction i)
{
  Opcode o = i.getOpcode();                                   //The String encoder that will represent the encoded string
  string encoder = opcodes.getOpcodeField( i.getOpcode());    // Checks position register positions, and inputs 0's or 
  if(opcodes.IMMposition(i.getOpcode()) != -1)                // binary representation of register numbers in appropriate positions
    encoder = encoder + cvtDectoBin(i.getImmediate()/4,26);   // divides the immediate by 4, in order to shift the binary representation by 2 bits
  else
    encoder = encoder + "00000000000000000000000000";
  return encoder;
}

//accepts the number you want to convert to binary, and the total number of bits you want(pad)
string ASMParser::cvtDectoBin(int num, int pad)
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


