#pragma once
#include<string>
#include"typedef.h"
#include<sstream>
#include"error_handler.h"
#include"utility.h"

enum class Type
{
	_8,
	_16,
};

class Converter
{
public:

	//To convert Dec to Hex
	static std::string DecToHex(const _16Bit&, const Type&);
	
	//To convert Hex to Dec
	static _16Bit HexToDec(const std::string&);

	//To convert memory Location to Hex
	static std::string MemLocHex(const int);

	//Helper function to fetch the MOD_RM_INFO from MOD_RM map
	//It will convert the expersion given in memory([exp]) in the form of key requried for MOD_RM map
	static std::string ExpressionForModRM(const std::string&);
};

std::string Converter::DecToHex(const _16Bit& data, const Type& type = Type::_8)
{
	std::stringstream ss;
	ss << std::hex << data;
	std::string res = ss.str() + 'H';
	Utility::Capitalize(res);

	if (type == Type::_8)
	{
		Utility::Format8Bit(res);
	}
	else
	{
		Utility::Format16Bit(res);
	}
	return res;
}

_16Bit Converter::HexToDec(const std::string& data)
{
	std::stringstream ss(data.substr(0, data.length() - 1));
	_16Bit res = 0;
	ss >> std::hex >> res;
	return res;
}

std::string Converter::MemLocHex(const int location)
{
	std::stringstream ss;
	ss << std::hex << location;
	std::string res = ss.str() + 'H';
	Utility::Capitalize(res);
	return std::string(5 - (res.length() - 1), '0') + res;
}

std::string Converter::ExpressionForModRM(const std::string& mem)
{
	
	const std::string& exp = mem.substr(1, mem.length() - 2);//Removing []
	//split by '+'
	const std::vector<std::string> &afterSplit = Utility::SplitBy(exp, '+');

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
			res += res.empty() ? 'd' + Utility::HexSize(s) : "+d" + Utility::HexSize(s);
		}
		else
		{
			res += res.empty() ? s : "+" + s;
		}
	}

	return '[' + res + ']';
}

