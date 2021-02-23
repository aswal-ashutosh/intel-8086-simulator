#pragma once
#include"8086.h"

bool ProgramExecutor::XCHG_CASE_1(std::string& REG8_D, std::string& REG8_S)
{
	//Case-1 REG8, REG8
	Byte D = Register::REG8(REG8_D);
	Byte S = Register::REG8(REG8_S);
	D = D ^ S;
	S = D ^ S;
	D = D ^ S;
	Register::REG8(REG8_D, D);
	Register::REG8(REG8_S, S);
	return true;
}

bool ProgramExecutor::XCHG_CASE_2(std::string& MEM8, std::string& REG8)
{
	//Case-2 [], REG8
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte D = Memory::Get8Bit(Padd);
	Byte S = Register::REG8(REG8);
	D = D ^ S;
	S = D ^ S;
	D = D ^ S;
	Memory::Set8Bit(Padd, D);
	Register::REG8(REG8, S);
	return true;
}

bool ProgramExecutor::XCHG_CASE_3(std::string& REG8, std::string& MEM8)
{
	//Case-3 REG8, []
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte D = Register::REG8(REG8); 
	Byte S = Memory::Get8Bit(Padd);
	D = D ^ S;
	S = D ^ S;
	D = D ^ S;
	Register::REG8(REG8, D);
	Memory::Set8Bit(Padd, S);
	return true;
}

bool ProgramExecutor::XCHG_CASE_4(std::string& REG16_D, std::string& REG16_S)
{
	//Case-4 REG16, REG16
	Word D = Register::REG16(REG16_D);
	Word S = Register::REG16(REG16_S);
	D = D ^ S;
	S = D ^ S;
	D = D ^ S;
	Register::REG16(REG16_D, D);
	Register::REG16(REG16_S, S);
	return true;
}

bool ProgramExecutor::XCHG_CASE_5(std::string& REG16, std::string& MEM)
{
	///Case-5 REG16, []/W[]
	int Padd = Memory::PhysicalAddress(MEM);
	Word D = Register::REG16(REG16);
	Word S = Memory::Get16Bit(Padd);
	D = D ^ S;
	S = D ^ S;
	D = D ^ S;
	Register::REG16(REG16, D);
	Memory::Set16Bit(Padd, S);
	return true;
}

bool ProgramExecutor::XCHG_CASE_6(std::string& MEM, std::string& REG16)
{
	//Case-6 []/W[], REG16
	int Padd = Memory::PhysicalAddress(MEM);
	Word D = Memory::Get16Bit(Padd);
	Word S = Register::REG16(REG16);
	D = D ^ S;
	S = D ^ S;
	D = D ^ S;
	Memory::Set16Bit(Padd, D);
	Register::REG16(REG16, S);
	return true;
}

bool ProgramExecutor::XCHG(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 2))
	{
		return Error::LOG("Expected No Operand @XCHG\n");
	}
	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1 REG8, REG8
		return XCHG_CASE_1(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-2 [], REG8
		if (Utility::IsByteMemory(OP1))
		{
			return XCHG_CASE_2(OP1, OP2);
		}
		else
		{
			return Error::LOG("Both operand must be of same size\n");
		}
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-3 REG8, []
		if (Utility::IsByteMemory(OP2))
		{
			return XCHG_CASE_3(OP1, OP2);
		}
		else
		{
			return Error::LOG("Both operand must be of same size\n");
		}
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4 REG16, REG16
		//SPECIAL CASE AX, REG16 OR REG16, AX
		return XCHG_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5 REG16, []/W[]
		return XCHG_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6 []/W[], REG16
		return XCHG_CASE_6(OP1, OP2);
	}

	return Error::LOG("Invalid Syntax @XCHG\n");
}
