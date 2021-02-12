#pragma once
#include<string>
#include<iostream>
#include<bitset>

class Error
{
public:
	static bool LOG(const std::string& e)
	{
		std::cout << "\x1B[31mERROR\x1B[0m::" + e;
		exit(0);//To be removed
		return false;
	}

	static void Debug(const std::string& e)
	{
		std::cout << e << '\n';
		std::cin.get();
	}

	static void DebugBit(std::bitset<8> b)
	{
		std::cout << b << '\n';
	}
};