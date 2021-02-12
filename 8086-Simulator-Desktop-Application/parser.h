#pragma once
#include<fstream>
#include<string>
#include<vector>
#include"utility.h"
#include"operands.h"
#include"program_manager.h"
#include"8086.h"
#include"memory.h"

bool ValidateAndFormatExp(std::string& exp)
{
	//Remove spaces
	std::string s;
	for (const char& x : exp)
	{
		if (x != ' ' && x != '\t')
		{
			s.push_back(x);
		}
	}

	//ax+bx+ffffh

	if (s.length() > 11 || s.length() < 2)
	{
		std::cout << "Unexpected number of characters\n";
		return false;
	}

	//split by '+'
	const std::vector<std::string> &afterSplit = Utility::SplitBy(s, '+');
	
	if (afterSplit.size() > 3)
	{
		std::cout << "More than 3 strings separated by +\n";
		return false;
	}

	//Primary => BX, BP
	//Secondary=> SI, DI
	//Data=>8/16Bit data
	std::vector<std::string> PSD(3); //0=>Primary, 1=>Secondary, 3=>Data
	for (const std::string& x : afterSplit)
	{
		//Maximum size token will be of 5 eg: 0fa1h and minimum size will be of two eg: 1h 
		if (x.length() > 5 || x.length() < 2)
		{
			//error
			Error::LOG("Unexected length of aftersplit content\n");
		}

		if (x == REGISTER::BX || x == REGISTER::BP)
		{
			if (!PSD[0].empty())
			{
				//error
				Error::LOG("Primary is already found!\n");
			}
			else
			{
				PSD[0] = x;
			}
		}
		else if (x == REGISTER::SI || x == REGISTER::DI)
		{
			if (!PSD[1].empty())
			{
				//error
				Error::LOG("Secondary is already found!\n");
			}
			else
			{
				PSD[1] = x;
			}
		}
		else if (Utility::IsValidHex(x))
		{
			if ((int)x.length() > 5)
			{
				Error::LOG("Unexpected length of hex data. @ValidateFromExp\n");
			}

			if (!PSD[2].empty())
			{
				//Error
				Error::LOG("Data is already found!\n");
			}
			else
			{
				PSD[2] = x;
			}
		}
		else
		{
			//error
			Error::LOG("Unexpected symbols\\Characters\n In [] @ValidateAndFormatExp");
		}
	}

	exp.clear();

	for (int i = 0; i < (int)PSD.size(); ++i)
	{
		if (i)
		{
			if (!PSD[i].empty())
			{
				exp += exp.empty() ? PSD[i] : '+' + PSD[i];
			}
		}
		else
		{
			exp += PSD[i];
		}
	}
	return true;
}

std::vector<std::string> Tokenize(const std::string &line)
{
	std::vector<std::string> Tokens;
	std::string token;
	for (int i = 0; i < (int)line.length(); ++i)
	{
		const char& x = line[i];
		if (x == ' ' || x == '\t')
		{
			if (!token.empty())
			{
				Tokens.push_back(token);
				token.clear();
			}
		}
		else if (x == ',')
		{

			if (!token.empty())
			{
				Tokens.push_back(token);
				token.clear();
			}

			Tokens.push_back(",");
		}
		else if (x == '[')
		{
			if (!token.empty())
			{
				//error
				std::cout << "Error: Unexpcted character before [\n";
			}
			bool OK = false;
			std::string exp;
			for (int j = i + 1; j < (int)line.length(); ++j)
			{
				if (line[j] == ']')
				{			
					if (ValidateAndFormatExp(exp))
					{
						token = '[' + exp + ']';
						OK = true;
						i = j;
						break;
					}
					else
					{
						//error
						std::cout << "Invalid Exp\n";
						exit(0);
					}
				}
				exp.push_back(line[j]);
			}

			if (!OK)
			{
				//error
				std::cout << "ERROR\n";
				exit(0);
			}
		}
		else
		{
			token.push_back(x);
		}
	}

	if (!token.empty())
	{
		Tokens.push_back(token);
	}

	//Dont forget to remove capitalization for label
	for (std::string& s : Tokens)
	{
		Utility::Capitalize(s);
	}

	return Tokens;
}


void Read()
{
	std::fstream file;
	file.open("test.txt", std::ios::in);
	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		std::vector<std::string> tokens = Tokenize(line);
		
		for (const std::string& s : tokens)
		{
			std::cout << s << ' ';
		}
		std::cout << '\n';
		if (tokens.empty())
		{
			Error::LOG("Empty Token Error\n");
		}

		Operand op = { tokens[1], tokens[3] };


		//Compile
		ProgramManager::ADD(op);

		//Data Initialize
		/*Register::REG16(REGISTER::DS, 0x1000);
		Register::REG16(REGISTER::DI, 0x0100);
		Register::REG16(REGISTER::AX, 0xABCD);*/


		//Run
		//Mnemonic::MOV(op.first, op.second);

		

		/*Memory::SetData(MemData(0x3333, 0x33), MemData(0x3335, 0xff));
		
		/*Register::REG16(op.second, 0x1f33);
		Mnemonic::MOV(op.first, op.second);
		std::cout << "AL:" << Converter::DecToHex(Register::REG16(op.second), Type::_16) << '\n';*/
	}

	//View
	/*Memory::DebugMem(0x1000, 0x01ff, 2);
	Register::PrintAll();*/
}