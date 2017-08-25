#include <bits/stdc++.h>
using namespace std;

vector < pair < string, pair < string, pair < string, string > > > > arr;
string program_name, str, starting_address;
map <string, string> labels;
vector <string> object_code;

void input()
{
	char ch;
	string str, temp;
	int index = 0;
	while(!cin.eof())
	{
	    str.clear();
		arr.push_back(make_pair("\t", make_pair("\t", make_pair("\t", "\t") ) ) );
		getline(cin, str);
		int k = 0, flag = 0, found_opcode = 0;
		for(int i = 0; i < str.size(); i++)
		{
			while(i < str.size() && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			{
				temp.push_back(str[i++]);
				flag = 1;
			}
			
			if(flag)
			{
			    if(get_opcode(temp) == "-1" && ( temp != "BYTE" && temp != "WORD" && temp != "RESW" && temp != "RESB"
				&& temp != "END"))
			    {
			    	if(!found_opcode)
			    		arr[index].second.first = temp;
			    	else
			    		arr[index].second.second.second = temp;
			    }
			    else
			    {
			    	arr[index].second.second.first = temp;
			    	found_opcode = 1;
			    }
			    temp.clear();
			    flag = 0;
			}
	    }
	    index++;
	}
}

int hexToDec(string str)
{
    int y;
    stringstream stream;
    stream << str;
    stream >> hex >> y;
    return y;
}

string decToHex(int num)
{
    stringstream stream;
    stream << hex << num;
    return stream.str();
}

string add(string str, string adder, int flag)
{
	//Adding hex and hex
	if(flag)
	{
		int num1 = hexToDec(str);
		int num2 = hexToDec(adder);
		int sum = num1 + num2;
		return decToHex(sum);
	}
	//Adding decimal and hex
	else
	{
		int num1 = hexToDec(str);
		int num2 = atoi(adder.c_str());
		int sum = num1 + num2;

		return decToHex(sum);
	}
}

void addressing()
{
	arr[0].first = starting_address;
	if(arr[0].second.first.size() > 0)
		labels[arr[0].second.first] = arr[0].first;

	for(int i = 1; i < arr.size()-1; i++)
	{
		string mnemonic = arr[i-1].second.second.first;
		string lastAddress = arr[i-1].first;
		if(mnemonic != "BYTE" && mnemonic != "RESW" && mnemonic != "RESB")
		{
			arr[i].first = add(lastAddress, "3", 0);
		}
		else
		{
			if(mnemonic == "BYTE")
			{
				int bytes;
				string label2 = arr[i-1].second.second.second;
				char ch = label2[0];
				if(ch == 'C')
				{
					bytes = (label2.size() - 3);
				}
				else
				{
					if((label2.size() - 3) % 2 == 0)
					{
						bytes = (label2.size() -3) / 2;
					}
					else
					{
						bytes = ((label2.size() - 3) / 2) + 1;
					}
				}
				arr[i].first = add(lastAddress, to_string(bytes), 1);
			}
			else if(mnemonic == "RESB")
			{
				int reserve = atoi(arr[i-1].second.second.second.c_str());
    			string hexaReserve = decToHex(reserve);
    			arr[i].first = add(lastAddress, hexaReserve, 1);
			}
			else
			{
				int reserve = 3 * atoi(arr[i-1].second.second.second.c_str());
				string hexaReserve = decToHex(reserve);
				arr[i].first = add(lastAddress, hexaReserve, 1);
			}
		}
		if(arr[i].second.first.size() > 0)
			labels[arr[i].second.first] = arr[i].first;
	}
}

void generate_object_code()
{
	string objectCode = "", mnemonic, operand, label_address;
	for(int i = 0; i < arr.size() - 1; i++)
	{
		int flag = 0;
		objectCode.clear();
		mnemonic = arr[i].second.second.first;
		if(mnemonic == "RESW" || mnemonic == "RESB" || mnemonic == "END")
		{
			object_code.push_back("\t");
			continue;
		}
		operand.clear();
		for(int l = 0; l < arr[i].second.second.second.size(); l++)
		{
			if(arr[i].second.second.second[l] == ',')
			{
				flag = 1;
				break;
			}
			operand += arr[i].second.second.second[l];
		}
		if(mnemonic == "BYTE")
		{
			if(operand[0] == 'C')
			{
				for(int i = 2; i < operand.size()-1; i++)
				{
					int ascii = operand[i];
					objectCode += (decToHex(ascii));
				}
			}
			else
			{
				for(int i = 2; i < operand.size()-1; i++)
				{
					objectCode += (operand[i]);
				}
			}
			if(objectCode.size() < 6)
			{
				string zero;
				for(int i = 0; i < 6 - objectCode.size(); i++)
				{
					zero += "0";
				}
				objectCode.insert(0, zero);
			}
			object_code.push_back(objectCode);
			continue;
		}
		if(mnemonic == "WORD")
		{
			objectCode += decToHex(atoi(operand.c_str()));
			if(objectCode.size() < 6)
			{
				string zero;
				for(int i = 0; i < 6 - objectCode.size(); i++)
				{
					zero += "0";
				}
				objectCode.insert(0, zero);
			}
			object_code.push_back(objectCode);
			continue;
		}
		objectCode += get_opcode(mnemonic);
		if(operand == "\t")
		{
			objectCode += "0000";
			object_code.push_back(objectCode);
			continue;
		}
		label_address = labels[operand];
		if(label_address[0] > '7')
		{
			if(label_address[0] >= 'A')
				label_address[0] -= 15;
			else
				label_address[0] -= 8;
		}
		objectCode += label_address;
		if(flag)
			objectCode = add(objectCode, "8000", 1);

		if(objectCode.size() < 6)
		{
			string zero;
			for(int i = 0; i < 6 - objectCode.size(); i++)
			{
				zero += "0";
			}
			objectCode.insert(0, zero);
		}
		object_code.push_back(objectCode);
	}
}
