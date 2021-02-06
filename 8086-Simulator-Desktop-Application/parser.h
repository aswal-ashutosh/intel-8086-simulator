#pragma once
#include<fstream>
#include<string>
#include<vector>
#include"utility.h"
#include"operands.h"
#include"program_manager.h"


/*
	1)Both operands can't be memory => mov [],[] =>wrong.
	2)If first operand is reg then d = 1 else if second operand is reg then d = 0.When both are reg then also d=1.
	3)If Data is word(16-bits) then w = 1 else if data is byte(8-bits) then w = 0.
	4)[50h] =>No displacement but data will be considered as (16-bit)
*/






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
			Error::LOG("Unexpected symbols\\Characters\n");
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
		Operand op = {tokens[1], tokens[3] };
		ProgramManager::MOV(op);
	}
}