#pragma once
#include<string>
#include"typedef.h"
#include<sstream>
#include"error_handler.h"
#include"utility.h"
#include"hex_size.h"

class Converter
{
public:

	//To convert Dec to Hex
	static std::string DecToHex(const Word&, const SIZE&);
	
	//To convert Hex to Dec
	static Word HexToDec(const std::string&);

	//To convert memory Location to Hex
	static std::string MemLocHex(const int);

	//To convert Hex to Dec
	static Byte Dec(const std::string&);
};

Byte Converter::Dec(const std::string& data)
{
	std::stringstream ss(data);
	Byte res = 0;
	ss >> std::hex >> res;
	return res;
}

std::string Converter::DecToHex(const Word& data, const SIZE& Size = SIZE::BYTE)
{
	std::stringstream ss;
	ss << std::hex << data;
	std::string res = ss.str() + 'H';
	Utility::Capitalize(res);

	if (Size == SIZE::BYTE)
	{
		Utility::Format8Bit(res);
	}
	else
	{
		Utility::Format16Bit(res);
	}
	return res;
}

Word Converter::HexToDec(const std::string& data)
{
	std::stringstream ss(data.substr(0, data.length() - 1));
	Word res = 0;
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