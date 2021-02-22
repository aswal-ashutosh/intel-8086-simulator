#pragma once
#include<unordered_map>
#include<string>
#include"error_handler.h"
class Label
{
	//Will map the label string to starting index of instruction under the label
	static std::unordered_map<std::string, int> _Label;

public:
	static bool Add(const std::string&, const int);
};

std::unordered_map<std::string, int> Label::_Label;

bool Label::Add(const std::string& Label_String, const int index)
{
	//If Label is already taken
	if (_Label.count(Label_String))
	{
		return Error::LOG("There is already lable with name '" + Label_String + "'\n");
	}
	_Label[Label_String] = index;
	return true;
}