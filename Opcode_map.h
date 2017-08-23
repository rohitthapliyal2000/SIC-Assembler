#include <bits/stdc++.h>
using namespace std;

string get_opcode(string str)
{
    map <string, string> opcode;
	opcode.insert(pair <string , string> ("LDA", "00"));
	opcode.insert(pair <string , string> ("AND", "40"));
	opcode.insert(pair <string , string> ("DIV", "24"));
	opcode.insert(pair <string , string> ("SUB", "1C"));
	opcode.insert(pair <string , string> ("ADD", "18"));
	opcode.insert(pair <string , string> ("LDL", "08"));
	opcode.insert(pair <string , string> ("RD", "D8"));
	opcode.insert(pair <string , string> ("WD", "DC"));
	opcode.insert(pair <string , string> ("LDCH", "50"));
	opcode.insert(pair <string , string> ("STX", "10"));
	opcode.insert(pair <string , string> ("JLT", "38"));
	opcode.insert(pair <string , string> ("TIX", "2C"));
	opcode.insert(pair <string , string> ("TD", "E0"));
	opcode.insert(pair <string , string> ("STCH", "54"));
	opcode.insert(pair <string , string> ("STL", "14"));
	opcode.insert(pair <string , string> ("LDX", "04"));
	opcode.insert(pair <string , string> ("RSUB", "4C"));
	opcode.insert(pair <string , string> ("STA", "0C"));
	opcode.insert(pair <string , string> ("J", "3C"));
	opcode.insert(pair <string , string> ("JEQ", "30"));
	opcode.insert(pair <string , string> ("COMP", "26"));
	opcode.insert(pair <string , string> ("COMP", "14"));
	opcode.insert(pair <string , string> ("JSUB", "48"));
	opcode.insert(pair <string , string> ("JGT", "34"));
	opcode.insert(pair <string , string> ("MUL", "20"));
	opcode.insert(pair <string , string> ("OR", "44"));
	opcode.insert(pair <string , string> ("STSW", "E8"));

	if(opcode.find(str) == opcode.end())
		return "-1";
	
	return opcode[str];
}
