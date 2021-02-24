#pragma once
#include"8086.h"


void ProgramExecutor::UpdateFlags_MUL_8Bit()
{
	//MUL only affects OF and CF based upon the upper half of the result all other flags are undefined
	Byte AH = Register::REG8(REGISTER::AH);
	Register::SetFlag(Register::FLAG::CF, AH != 0x00);
	Register::SetFlag(Register::FLAG::OF, AH != 0x00);
}

void ProgramExecutor::UpdateFlags_MUL_16Bit()
{
	//MUL only affects OF and CF based upon the upper half of the result all other flags are undefined
	Word DX = Register::REG16(REGISTER::DX);
	Register::SetFlag(Register::FLAG::CF, DX != 0x0000);
	Register::SetFlag(Register::FLAG::OF, DX != 0x0000);
}



bool ProgramExecutor::MUL_CASE_1(const std::string& MEM8)
{
	//Case-1: MUL []
	Word multiplicand = Register::REG8(REGISTER::AL);
	Word mulitplier = Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	Word Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::MUL_CASE_2(const std::string& MEM16)
{
	//Case-2: MUL W[]
	uint32_t multiplicand = Register::REG16(REGISTER::AX);
	uint32_t mulitplier = Memory::Get16Bit(Memory::PhysicalAddress(MEM16));
	uint32_t Result = multiplicand * mulitplier;
	Word UpperHalf = (Result & 0xffff0000) >> 16;
	Word LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::MUL_CASE_3(const std::string& REG8)
{
	//Case-3: MUL REG8
	Word multiplicand = Register::REG8(REGISTER::AL);
	Word mulitplier = Register::REG8(REG8);
	Word Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::MUL_CASE_4(const std::string& REG16)
{
	//Case-4: MUL REG16
	uint32_t multiplicand = Register::REG16(REGISTER::AX);
	uint32_t mulitplier = Register::REG16(REG16);
	uint32_t Result = multiplicand * mulitplier;
	Word UpperHalf = (Result & 0xffff0000) >> 16;
	Word LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_1(const std::string& MEM8)
{
	//Case-1: IMUL []
	short multiplicand = (char)Register::REG8(REGISTER::AL);
	short mulitplier = (char)Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	short Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_2(const std::string& MEM16)
{
	//Case-2: IMUL W[]
	int multiplicand = (short)Register::REG16(REGISTER::AX);
	int mulitplier = (short)Memory::Get16Bit(Memory::PhysicalAddress(MEM16));
	int Result = multiplicand * mulitplier;
	Word UpperHalf = (Result & 0xffff0000) >> 16;
	Word LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_3(const std::string& REG8)
{
	//Case-3: IMUL REG8
	short multiplicand = (char)Register::REG8(REGISTER::AL);
	short mulitplier = (char)Register::REG8(REG8);
	short Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_4(const std::string& REG16)
{
	//Case-4: IMUL REG16
	int multiplicand = (short)Register::REG16(REGISTER::AX);
	int mulitplier = (short)Register::REG16(REG16);
	int Result = multiplicand * mulitplier;
	Word UpperHalf = (Result & 0xffff0000) >> 16;
	Word LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::MUL(const Operand& operand)
{
	std::string OP = operand.first;
	
	bool OK = false;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: MUL []
		OK = MUL_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: MUL W[]
		OK = MUL_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: MUL REG8
		OK = MUL_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: MUL REG16
		OK = MUL_CASE_4(OP);
	}
	else
	{
		return Error::LOG("Unhandled Case @MUL");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}

bool ProgramExecutor::IMUL(const Operand& operand)
{
	std::string OP = operand.first;

	bool OK = false;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: IMUL []
		OK = IMUL_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: IMUL W[]
		OK = IMUL_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: IMUL REG8
		OK = IMUL_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: IMUL REG16
		OK = IMUL_CASE_4(OP);
	}
	else
	{
		return Error::LOG("Unhandled Case @IMUL");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}
