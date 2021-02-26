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

	//Will check whether there exist label with such name with atleast one instruction
	static bool IsValidLabel(const std::string&);

	//Will return the mapped value to the label
	static int IndexOf(const std::string& label);

	static const std::unordered_map<std::string, int>& GetLabels();

	static void Clear();
};

std::unordered_map<std::string, int> Label::_Label;

bool Label::Add(const std::string& Label_String, const int index)
{
	//If Label is already taken
	if (_Label.count(Label_String))
	{
		return Error::LOG("There is already lable with name '" + Label_String + "'");
	}
	_Label[Label_String] = index;
	return true;
}

bool Label::IsValidLabel(const std::string& label)
{
	return _Label.count(label);
}

int Label::IndexOf(const std::string& label)
{
	return _Label[label];
}

const std::unordered_map<std::string, int>& Label::GetLabels()
{
	return _Label;
}

void Label::Clear()
{
	_Label.clear();
}