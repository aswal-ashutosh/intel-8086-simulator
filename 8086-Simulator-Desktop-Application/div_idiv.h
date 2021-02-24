#pragma once
#include"8086.h"
bool ProgramExecutor::DIV_CASE_1(const std::string& MEM8)
{
	//Case-1: DIV []
	Word divisor = Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	Word dividend = Register::REG16(REGISTER::AX);
	Word quotient = dividend / divisor;
	Word remainder = dividend % divisor;
	if (quotient > 0xff) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, (Byte)quotient);
	Register::REG8(REGISTER::AH, (Byte)remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV_CASE_2(const std::string& MEM16)
{
	//Case-2: DIV W[]
	uint32_t divisor = Memory::Get16Bit(Memory::PhysicalAddress(MEM16));
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	uint32_t dividendLowerHalf = Register::REG16(REGISTER::AX);
	uint32_t dividendUpperHalf = Register::REG16(REGISTER::DX);
	uint32_t dividend = (dividendUpperHalf << 16) | dividendLowerHalf;
	uint32_t quotient = dividend / divisor;
	uint32_t remainder = dividend % divisor;
	if (quotient > 0xffff) { return Error::LOG("Division Error. Result can't be fit in AX\n"); }
	Register::REG16(REGISTER::AX, quotient);
	Register::REG16(REGISTER::DX, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV_CASE_3(const std::string& REG8)
{
	//Case-3: DIV REG8
	Word divisor = Register::REG8(REG8);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	Word dividend = Register::REG16(REGISTER::AX);
	Word quotient = dividend / divisor;
	Word remainder = dividend % divisor;
	if (quotient > 0xff) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, (Byte)quotient);
	Register::REG8(REGISTER::AH, (Byte)remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV_CASE_4(const std::string& REG16)
{
	//Case-4: DIV REG16
	uint32_t divisor = Register::REG16(REG16);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	uint32_t dividendLowerHalf = Register::REG16(REGISTER::AX);
	uint32_t dividendUpperHalf = Register::REG16(REGISTER::DX);
	uint32_t dividend = (dividendUpperHalf << 16) | dividendLowerHalf;
	uint32_t quotient = dividend / divisor;
	uint32_t remainder = dividend % divisor;
	if (quotient > 0xffff) { return Error::LOG("Division Error. Result can't be fit in AX\n"); }
	Register::REG16(REGISTER::AX, quotient);
	Register::REG16(REGISTER::DX, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_1(const std::string& MEM8)
{
	//Case-1: IDIV []
	short divisor = (char)Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	short dividend = Register::REG16(REGISTER::AX);
	short quotient = dividend / divisor;
	short remainder = dividend % divisor;
	if (quotient > 0x7f || quotient < (char)0x80) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, (Byte)quotient);
	Register::REG8(REGISTER::AH, (Byte)remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_2(const std::string& MEM16)
{
	//Case-2: IDIV W[]
	int divisor = (short)Memory::Get16Bit(Memory::PhysicalAddress(MEM16));
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	uint32_t dividendLowerHalf = Register::REG16(REGISTER::AX);
	uint32_t dividendUpperHalf = Register::REG16(REGISTER::DX);
	int dividend = (dividendUpperHalf << 16) | dividendLowerHalf;
	int quotient = dividend / divisor;
	int remainder = dividend % divisor;
	if (quotient > 0x7fff || quotient < (short)0x8000) { return Error::LOG("Division Error. Result can't be fit in AX\n"); }
	Register::REG16(REGISTER::AX, quotient);
	Register::REG16(REGISTER::DX, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_3(const std::string& REG8)
{
	//Case-3: IDIV REG8
	short divisor = (char)Register::REG8(REG8);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	short dividend = Register::REG16(REGISTER::AX);
	short quotient = dividend / divisor;
	short remainder = dividend % divisor;
	if (quotient > 0x7f || quotient < (char)0x80) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, (Byte)quotient);
	Register::REG8(REGISTER::AH, (Byte)remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_4(const std::string& REG16)
{
	//Case-4: IDIV REG16
	int divisor = (short)Register::REG16(REG16);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	uint32_t dividendLowerHalf = Register::REG16(REGISTER::AX);
	uint32_t dividendUpperHalf = Register::REG16(REGISTER::DX);
	int dividend = (dividendUpperHalf << 16) | dividendLowerHalf;
	int quotient = dividend / divisor;
	int remainder = dividend % divisor;
	if (quotient > 0x7fff || quotient < (short)0x8000) { return Error::LOG("Division Error. Result can't be fit in AX\n"); }
	Register::REG16(REGISTER::AX, quotient);
	Register::REG16(REGISTER::DX, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV(const Operand& operand)
{
	std::string OP = operand.first;

	bool OK = false;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: DIV []
		OK = DIV_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: DIV W[]
		OK = DIV_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: DIV REG8
		OK = DIV_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: DIV REG16
		OK = DIV_CASE_4(OP);
	}
	else
	{
		return Error::LOG("Unhandled Case @DIV");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}

bool ProgramExecutor::IDIV(const Operand& operand)
{
	std::string OP = operand.first;

	bool OK = false;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: IDIV []
		OK = IDIV_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: IDIV W[]
		OK = IDIV_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: IDIV REG8
		OK = IDIV_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: IDIV REG16
		OK = IDIV_CASE_4(OP);
	}
	else
	{
		Error::LOG("Unhandled Case @IDIV");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}
