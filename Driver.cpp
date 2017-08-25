#include<bits/stdc++.h>
#include "Opcode_map.h"
#include "Pass1.h"
#include "Pass2.h"

using namespace std;

int main()
{
	cin >> program_name >> str >> starting_address;
	cin.ignore();
	input();
	addressing();
	generate_object_code();
	generate_machine_code();	
}