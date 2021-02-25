#pragma once
#include<fstream>
#include<string>
#include<vector>
#include"utility.h"
#include"operands.h"
#include"program_loader.h"
#include"8086.h"
#include"memory.h"
#include"instruction.h"
#include"error_handler.h"
#include"labels.h"


class Parser
{
	
public:
	//Will format the memroy expression and also check for possible error.
	static bool ValidateAndFormatMemoryExp(std::string&);

	//Will convert the give line into tokens
	static bool Tokenize(const std::string&, std::vector<std::string>&, const int);

	//Will Read, check & load the source code for further execution
	static bool Read(const std::string&);
};

bool Parser::ValidateAndFormatMemoryExp(std::string& exp)
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
		return false;
	}

	//split by '+'
	const std::vector<std::string> &afterSplit = Utility::SplitBy(s, '+');
	
	if (afterSplit.size() > 3)
	{
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
			return false;
		}

		if (x == REGISTER::BX || x == REGISTER::BP)
		{
			if (!PSD[0].empty())
			{
				//error
				return false;
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
				return false;
			}
			else
			{
				PSD[1] = x;
			}
		}
		else if (Utility::IsValidHex(x))
		{
			if (!PSD[2].empty())
			{
				//Error
				return false;
			}
			else
			{
				PSD[2] = x;
			}
		}
		else
		{
			//error
			return false;
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

bool Parser::Tokenize(const std::string &line, std::vector<std::string>& TOKENS, const int lineNumber)
{
	std::string token;
	for (int i = 0; i < (int)line.length(); ++i)
	{
		const char& x = line[i];
		if (x == ' ' || x == '\t')
		{
			if (!token.empty())
			{
				TOKENS.push_back(token);
				token.clear();
			}
		}
		else if (x == ',')
		{

			if (!token.empty())
			{
				TOKENS.push_back(token);
				token.clear();
			}

			TOKENS.push_back(",");
		}
		else if (x == ':')
		{
			if (token.empty())
			{
				return Error::LOG(ERROR_TYPE::SYNTAX, lineNumber);
			}
			token.push_back(x);
			TOKENS.push_back(token);
			token.clear();
		}
		else if (x == '[')
		{
			bool end = false;
			for (int k = i; k < (int)line.length(); ++k)
			{
				token.push_back(line[k]);
				if (line[k] == ']')
				{
					end = true;
					i = k;
					break;
				}
			}
			if (!end) { return Error::LOG(ERROR_TYPE::SYNTAX, lineNumber); }
		}
		else if (x == ';')
		{
			if (!token.empty())
			{
				TOKENS.push_back(token);
				token.clear();
			}
			break;
		}
		else
		{
			token.push_back(x);
		}
	}

	if (!token.empty())
	{
		TOKENS.push_back(token);
	}

	//Formatting Memory
	for (std::string& s : TOKENS)
	{
		if (Utility::IsValidMemory(s))
		{
			if (Utility::IsWordMemory(s))
			{
				std::string exp = s.substr(2, s.length() - 3);
				if (ValidateAndFormatMemoryExp(exp))
				{
					s = "W[" + exp + "]";
				}
				else
				{
					return Error::LOG(ERROR_TYPE::INVALID_MEM_EXP, lineNumber);
				}
			}
			else
			{
				std::string exp = s.substr(1, s.length() - 2);
				if (ValidateAndFormatMemoryExp(exp))
				{
					s = "[" + exp + "]";
				}
				else
				{
					return Error::LOG("Invalid Memory Expression", lineNumber);
				}
			}
		}
	}
	return true;
}

bool Parser::Read(const std::string& FILE_PATH)
{
	/*ProgramManager::Clear();
	Register::Clear();*/
	std::fstream file;
	file.open(FILE_PATH, std::ios::in);
	int LineNumber = 0;
	while (!file.eof())
	{
		++LineNumber;
		std::string line;
		std::getline(file, line);
		if (line.empty()) { continue; }

		std::vector<std::string> TOKENS;
		 if(!Tokenize(line, TOKENS, LineNumber))
		 {
			 return false;
		 }

		if (TOKENS.empty())//Lines with comment or white spaces or may be both
		{
			continue;
		}
		else
		{
			for (const std::string& s : TOKENS)
			{
				std::cout << s << ' ';
			}
			std::cout << '\n';
		}

		const int TotalTokens = TOKENS.size();
		int CurrToken = 0;

		if (TotalTokens > 5)//we can have at max 5 token in a line
		{
			return Error::LOG("Syntax Error", LineNumber);
		}

		if (TOKENS[CurrToken].back() == ':')
		{
			const std::string& s = TOKENS[CurrToken];
			if (Utility::IsLabel(s))
			{
				const std::string label = s.substr(0, s.size() - 1);
				if (!Label::Add(label, ProgramLoader::ProgramSize()))
				{
					return false;
				}
				if (TotalTokens == 1)//Just Label
				{
					continue;
				}
				++CurrToken;
			}
			else
			{
				return Error::LOG("'" + TOKENS[CurrToken] + "' is not a valid label name", LineNumber);
			}
		}

		Instruction instruction;
		instruction.LineNumber = LineNumber;

		//Checking for mnemonic
		if (CurrToken < TotalTokens)
		{
			std::string& s = TOKENS[CurrToken];
			Utility::Capitalize(s);
			if (ProgramLoader::IsValidMnemonic(s))
			{
				instruction.Mnemonic = s;
				++CurrToken;
			}
			else
			{
				return Error::LOG("Expected a Mnemonic", LineNumber);
			}
		}

		//First operand
		if (CurrToken < TotalTokens)
		{
			std::string& s = TOKENS[CurrToken];
			/*First operand can be a label name.
			So we don't have to change it into upper case form as labels are case sensitive.*/
			if (!ProgramLoader::IsJumpCallInstruction(instruction.Mnemonic))
			{
				Utility::Capitalize(s);
			}
			instruction.operand.first = s;
			++CurrToken;
		}

		/*If there are two operands then there should be a ',' in between.*/
		bool bComma = false;
		if (CurrToken < TotalTokens)
		{
			std::string& s = TOKENS[CurrToken];
			if (s == ",")
			{
				bComma = true;
				++CurrToken;
			}
			else
			{
				return Error::LOG("Syntax Error", LineNumber);
			}
		}

		//Second Operand
		if (CurrToken < TotalTokens)
		{
			std::string& s = TOKENS[CurrToken];
			Utility::Capitalize(s);
			instruction.operand.second = s;
			++CurrToken;
		}
		else if (bComma)
		{
			//There must be an opeands after comma
			return Error::LOG("Syntax Error", LineNumber);
		}
		//if (CurrToken < TotalTokens) //If there are still token left (after second operands), it must be a syntax error
		//{
		//	return Error::Throw(ERROR_TYPE::SYNTAX);
		//}
		ProgramLoader::AddInstruction(instruction);
	}
	return ProgramLoader::ProgramSize() == 0 ? Error::LOG("Empty File\n") : true;
}
