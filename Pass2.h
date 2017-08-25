#include<bits/stdc++.h>
using namespace std;

void generate_machine_code()
{
	string size = decToHex(hexToDec(arr[arr.size()-2].first) - hexToDec(starting_address));
	cout << "H " << program_name << " " << starting_address << " " << size << endl;
	int i = 0, save = 0, eternal_flag = 0;
	string firstExecutable;
	while(1)
	{
		int flag = 0, length = 0, codes = 0;
		i = save;
		while(i < arr.size()-1 && object_code[i] != "\t" && codes < 30)
		{
			length++;
			if(!flag && get_opcode(arr[i].second.second.first) != "-1")
			{
				cout << "T ";
				flag = 1;
				cout << arr[i].first << " ";
				if(!eternal_flag)
				{
					firstExecutable = arr[i].first;
					eternal_flag = 1;
				}
			}
			if(object_code[i] != "\t")
			{
				codes += (object_code[i].size() / 2);
				if(codes > 30)
				{
					codes -= (object_code[i].size() / 2);
					break;
				}
			}
			i++;
		}
		if(!flag)
		{
			save++;
			continue;
		}
		cout << decToHex(codes) << " ";
		i = save;
		codes = 0;
		for(; codes < 30; i++)
		{
			if(i >= arr.size() - 1)
				break;
			if(object_code[i] != "\t")
			{
				codes += (object_code[i].size() / 2);
				if(codes > 30)
					break;
				cout << object_code[i] << " ";
			}
			else
			{
				i++;
				break;
			}
		}
		save = i;
		if(i >= arr.size()-1)
			break;
		cout << endl;
	}
	cout << endl << "E " << firstExecutable << endl;

}