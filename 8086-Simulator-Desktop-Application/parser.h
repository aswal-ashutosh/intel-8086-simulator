#pragma once
#include<fstream>
#include<string>
#include<iostream>
#include<vector>
#include"utility.h"


/*
	1)Both operands can't be memory => mov [],[] =>wrong.
	2)If first operand is reg then d = 1 else if second operand is reg then d = 0.When both are reg then also d=1.
	3)If Data is word(16-bits) then w = 1 else if data is byte(8-bits) then w = 0.
	4)[50h] =>No displacement but data will be considered as (16-bit)
*/




std::vector<std::string> SplitBy(const std::string& s, const char& del = ' ')
{
	std::vector<std::string> res;
	std::string word;
	for (const char& x : s)
	{
		if (x == del)
		{
			if (!word.empty())
			{
				res.push_back(word);
				word.clear();
			}
		}
		else
		{
			word.push_back(x);
		}
	}

	if (!word.empty())
	{
		res.push_back(word);
		word.clear();
	}

	for (std::string& s : res)
	{
		Utility::Capitalize(s);
	}
	return res;
}

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
	std::vector<std::string> afterSplit = SplitBy(s, '+');
	
	if (afterSplit.size() > 3)
	{
		std::cout << "More than 3 strings separated by +\n";
		return false;
	}

	//Primary => BX, BP
	//Secondary=> SI, DI
	//Data=>8/16Bit data
	std::vector<std::string> PSD(3); //0=>Primary, 1=>Secondary, 3=>Data
	std::vector<bool> PSD_Found(3);//0=>Primary, 1=>Secondary, 3=>Data
	for (const std::string& x : afterSplit)
	{
		//Maximum size token will be of 5 eg: 0fa1h and minimum size will be of two eg: 1h 
		if (x.length() > 5 || x.length() < 2)
		{
			//error
			std::cout << "Unexected length of aftersplit content\n";
			return false;
		}

		if (x == "BX" || x == "BP")
		{
			if (PSD_Found[0])
			{
				//error
				std::cout << "Primary is already found!\n";
				return false;
			}
			else
			{
				PSD[0] = x;
				PSD_Found[0] = true;
			}
		}
		else if (x == "SI" || x == "DI")
		{
			if (PSD_Found[1])
			{
				//error
				std::cout << "Secondary is already found!\n";
				return false;
			}
			else
			{
				PSD[1] = x;
				PSD_Found[1] = true;
			}
		}
		else if (Utility::IsValidHex(x))
		{
			if (PSD_Found[2])
			{
				//Error
				std::cout << "Data is already found!\n";
				return false;
			}
			else
			{
				PSD[2] = x;
				PSD_Found[2] = true;
			}
		}
		else
		{
			//error
			std::cout << "Unexpected symbols\\Characters\n";
			return false;
		}
	}

	exp.clear();

	for (int i = 0; i < PSD.size(); ++i)
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
	for (int i = 0; i < line.length(); ++i)
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
			for (int j = i + 1; j < line.length(); ++j)
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
	}
}