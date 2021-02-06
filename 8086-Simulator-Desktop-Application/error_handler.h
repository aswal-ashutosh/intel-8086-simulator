#pragma once
#include<string>
#include<iostream>

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
};