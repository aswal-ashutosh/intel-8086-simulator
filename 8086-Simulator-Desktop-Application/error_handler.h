#pragma once
#include<string>

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
};