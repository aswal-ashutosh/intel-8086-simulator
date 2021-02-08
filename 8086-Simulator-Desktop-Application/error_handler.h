#pragma once
#include<string>
#include<iostream>
#include<bitset>

class Error
{
public:
	static void LOG(const std::string& e)
	{
		std::cout << "ERROR: " + e;
		exit(0);
	}

	static void Debug(const std::string& e)
	{
		std::cout << e << '\n';
	}

	static void DebugBit(std::bitset<8> b)
	{
		std::cout << b << '\n';
	}
};