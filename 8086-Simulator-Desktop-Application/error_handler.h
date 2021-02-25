#pragma once
#include<string>
#include<iostream>
#include<bitset>

class Error
{
public:
	static bool LOG(const std::string& e, const int lineNumber = -1)
	{
		std::string error;
		if (lineNumber != -1)
		{
			error = "Error: " + e + " [Line Number: " + std::to_string(lineNumber) + "]";
		}
		else
		{
			error = "Error: " + e;
		}
		wxMessageBox(error, DIALOG::EXECUTION_STOPPED);
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