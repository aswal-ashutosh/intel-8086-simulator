#pragma once
#include<string>

class Utility
{
public:
	//To check whether a string is representing a valid hex number or not
	static bool IsValidHex(const std::string &);

	//To capitalize a string
	static void Capitalize(std::string&);
};

bool Utility::IsValidHex(const std::string& hex)
{
	if (hex.back() != 'H') { return false; }
	//Assuming hex is in uppercase
	for (int i = 0; i < hex.length() - 1; ++i)
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