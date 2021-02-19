#pragma once
#include<string>
#include<vector>
#include"constants.h"
#include"error_handler.h"
#include<sstream>
#include"operands.h"
#include"hex_size.h"

class Utility
{
	static _16Bit HexToDec(const std::string&);
public:
	//To check whether a string is representing a valid hex number or not
	static bool IsValidHex(const std::string &);

	//To capitalize a string
	static void Capitalize(std::string&);

	//To check whether the operand is Memory or not
	static bool IsValidMemory(const std::string&);

	//To check if the memory is word memory
	static bool IsWordMemory(const std::string&);

	//To check if the memory is byte memory
	static bool IsByteMemory(const std::string&);

	//To check whether the oeprand is an 8-Bit register
	static bool Is8BitRegister(const std::string&);

	//To check whether the oeprand is an 16-Bit register but it will not include segment registers
	static bool Is16BitRegister(const std::string&);

	//To check whether the oeprand is an Segment register
	static bool IsSegmentRegister(const std::string&);

	//Function to format data in 16bit hex
	static void Format16Bit(std::string&);

	//Function to format data in 8bit hex
	static void Format8Bit(std::string&);

	//Function to split a string
	static std::vector<std::string> SplitBy(const std::string&, const char&);

	//Function to check whether the data is 8bit-hex or 16-bitHex
	static const SIZE HexSize(const std::string&);

	//Function to extract hex data from memory expression, it will return true if exp only contain hex data
	static bool ExtractHexFromMemExp(const std::string&, std::string&);

	//Helper function to fetch the MOD_RM_INFO from MOD_RM map
	//It will convert the expersion given in memory([exp]) in the form of key requried for MOD_RM map
	static std::string ExpressionForModRM(const std::string&);

	//Function to check whether the operand count is equal to expected count or not
	static bool IsValidOperandCount(const Operand&, int);

	static int SetBitCount(uint32_t);
};

_16Bit Utility::HexToDec(const std::string& data)
{
	std::stringstream ss(data.substr(0, data.length() - 1));
	_16Bit res = 0;
	ss >> std::hex >> res;
	return res;
}

bool Utility::IsValidHex(const std::string& hex)
{
	if (hex.size() > 5)
	{
		return Error::LOG("Don't Represent Hex in more than 4 digits\n");
	}
	//If hex value matches registers
	if (hex == REGISTER::AH || hex == REGISTER::BH || hex == REGISTER::CH || hex == REGISTER::DH)
	{
		//Error::Debug(hex + "is not hex\n");
		return false;
	}

	if (hex.back() != 'H') { return false; }

	//Assuming hex is in uppercase
	for (int i = 0; i < (int)hex.length() - 1; ++i)
	{
		const char& x = hex[i];
		bool OK = false;
		OK |= x >= 'A' && x <= 'F';
		OK |= x >= '0' && x <= '9';
		if (!OK) { return false; }
	}
	return true;
}

void Utility::Capitalize(std::string& s)
{
	for (char& x : s)
	{
		x = std::toupper(x);
	}
}

bool Utility::IsValidMemory(const std::string& s)
{
	if (s.size() < 4) { return false; }

	return (s.front() == '[' && s.back() == ']') || (s.substr(0, 2) == "W[" && s.back() == ']');
}

bool Utility::IsWordMemory(const std::string& s)
{
	return (s.substr(0, 2) == "W[" && s.back() == ']');
}

bool Utility::IsByteMemory(const std::string& s)
{
	return (s.front() == '[' && s.back() == ']');
}

bool Utility::Is8BitRegister(const std::string& reg)
{
	bool OK = false;
	OK |= reg == REGISTER::AL;
	OK |= reg == REGISTER::AH;
	OK |= reg == REGISTER::BH;
	OK |= reg == REGISTER::BL;
	OK |= reg == REGISTER::CH;
	OK |= reg == REGISTER::CL;
	OK |= reg == REGISTER::DH;
	OK |= reg == REGISTER::DL;
	return OK;
}


bool Utility::Is16BitRegister(const std::string& reg)
{
	bool OK = false;
	OK |= reg == REGISTER::AX;
	OK |= reg == REGISTER::BX;
	OK |= reg == REGISTER::CX;
	OK |= reg == REGISTER::DX;

	/*OK |= reg == REGISTER::CS;
	OK |= reg == REGISTER::DS;
	OK |= reg == REGISTER::SS;
	OK |= reg == REGISTER::ES;*/

	OK |= reg == REGISTER::SP;
	OK |= reg == REGISTER::BP;
	OK |= reg == REGISTER::SI;
	OK |= reg == REGISTER::DI;
	return OK;
}


bool Utility::IsSegmentRegister(const std::string& reg)
{
	bool OK = false;
	OK |= reg == REGISTER::CS;
	OK |= reg == REGISTER::DS;
	OK |= reg == REGISTER::SS;
	OK |= reg == REGISTER::ES;
	return OK;
}

void Utility::Format8Bit(std::string& s)
{
	//ABh
	if (s.length() == 3) { return; }

	if (s.length() > 3)
		Error::LOG("Can't convert to Type 8\n");
	else
		s = std::string(2 - (s.length() - 1), '0') + s;
}

void Utility::Format16Bit(std::string& s)
{
	//ABCDh
	if (s.length() == 5) { return; }
	if (s.length() > 5)
		Error::LOG("Can't convert to Type 16\n");
	else
		s = std::string(4 - (s.length() - 1), '0') + s;
}


std::vector<std::string> Utility::SplitBy(const std::string& s, const char& del = ' ')
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

const SIZE Utility::HexSize(const std::string& hex)
{
	_16Bit data = HexToDec(hex);
	if (data >= 0x00 && data <= 0xff)
	{
		return SIZE::BYTE;
	}
	else
	{
		//data > 0xff && data <= 0xffff
		return SIZE::WORD;
	}
	//[ToDo:REMOVE]
	Error::LOG("Unexpected Case @HexSize\n");
}


bool Utility::ExtractHexFromMemExp(const std::string& mem, std::string& hex)
{
	const std::string & exp = IsByteMemory(mem) ? mem.substr(1, mem.length() - 2) : mem.substr(2, mem.length() - 3);//Removing []/W[]

	const std::vector<std::string>& afterSplit = Utility::SplitBy(exp, '+');

	for (const std::string& s : afterSplit)
	{
		if (Utility::IsValidHex(s))
		{
			hex = s;
			return afterSplit.size() == 1 ? true : false;
		}
	}
	
	hex = "";
	return false;
}

std::string Utility::ExpressionForModRM(const std::string& mem)
{
	const std::string& exp = IsByteMemory(mem) ? mem.substr(1, mem.length() - 2) : mem.substr(2, mem.length() - 3);//Removing []/W[]

	const std::vector<std::string>& afterSplit = Utility::SplitBy(exp, '+');

	//If there is only data then it will be considered as 16bit displacement even if it is containing 8bit only
	if (afterSplit.size() == 1 && Utility::IsValidHex(afterSplit.front()))
	{
		return "[d16]";
	}

	std::string res;

	for (const std::string& s : afterSplit)
	{
		if (Utility::IsValidHex(s))
		{
			if (res.empty())
			{
				if (Utility::HexSize(s) == SIZE::BYTE)
				{
					res += "d8";
				}
				else
				{
					res += "d16";
				}
			}
			else
			{
				if (Utility::HexSize(s) == SIZE::BYTE)
				{
					res += "+d8";
				}
				else
				{
					res += "+d16";
				}
			}
		}
		else
		{
			res += res.empty() ? s : "+" + s;
		}
	}

	return '[' + res + ']';
}



bool Utility::IsValidOperandCount(const Operand& op, int expected_count)
{
	int count = !op.first.empty();
	count += !op.second.empty();
	return count == expected_count;
}

int Utility::SetBitCount(uint32_t number)
{
	int c = 0;
	while (number)
	{
		c += number & 1;
		number >>= 1;
	}
	return c;
}