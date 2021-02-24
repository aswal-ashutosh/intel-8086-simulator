#pragma once
#include"8086.h"

//No flags are affected
bool ProgramExecutor::NOT_CASE_1(const std::string& MEM8)
{
	//Case-1: NOT []
	int Padd = Memory::PhysicalAddress(MEM8);
	Memory::Set8Bit(Padd, ~Memory::Get8Bit(Padd));
	return true;
}
bool ProgramExecutor::NOT_CASE_2(const std::string& MEM16)
{
	//Case-2: NOT W[]
	int Padd = Memory::PhysicalAddress(MEM16);
	Memory::Set16Bit(Padd, ~Memory::Get16Bit(Padd));
	return true;
}
bool ProgramExecutor::NOT_CASE_3(const std::string& REG8)
{
	//Case-3: NOT REG8
	Register::REG8(REG8, ~Register::REG8(REG8));
	return true;
}
bool ProgramExecutor::NOT_CASE_4(const std::string& REG16)
{
	//Case-4: NOT REG16
	Register::REG16(REG16, ~Register::REG16(REG16));
	return true;
}
bool ProgramExecutor::NOT(const Operand& operand)
{
	std::string OP = operand.first;

	bool OK = false;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: NOT []
		OK = NOT_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: NOT W[]
		OK = NOT_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: NOT REG8
		OK = NOT_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: NOT REG16
		OK = NOT_CASE_4(OP);
	}
	else
	{
		return Error::LOG("Unhandled Case @NOT");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}
