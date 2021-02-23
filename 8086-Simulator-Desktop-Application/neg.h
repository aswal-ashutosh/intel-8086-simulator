#pragma once
#include"8086.h"

//The CF flag set to 0 if the source operand is 0; otherwise it is set to 1. The OF, SF, ZF, AF, and PF flags are set according to the result.
//Neg can be considered as 0 - DATA. Usefull statement for updating flags.
//Negating the smallest signed integer in a register results in a positive integer, which cannot fit into the same register.


void ProgramExecutor::UpdateFlags_NEG_8Bit(const Byte Data)
{
	Register::SetFlag(Register::FLAG::CF, Data != 0);//Carry Flag
	Register::SetFlag(Register::FLAG::AF, (Data & 0x0f) != 0);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (Byte)0x80);//Overflow Flag
	Byte Result = -Data;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 7)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x00); //Zero Flag
}

void ProgramExecutor::UpdateFlags_NEG_16Bit(const Word Data)
{
	Register::SetFlag(Register::FLAG::CF, Data != 0);//Carry Flag
	Register::SetFlag(Register::FLAG::AF, (Data & 0x000f) != 0);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (Word)0x8000);//Overflow Flag
	Word Result = -Data;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 15)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x0000); //Zero Flag
}



bool ProgramExecutor::NEG_CASE_1(const std::string& MEM8)
{
	//Case-1: NEG []
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	Memory::Set8Bit(Padd, -Data);
	UpdateFlags_NEG_8Bit(Data);
	return true;
}

bool ProgramExecutor::NEG_CASE_2(const std::string& MEM16)
{
	//Case-2: NEG W[]
	int Padd = Memory::PhysicalAddress(MEM16);
	Word Data = Memory::Get16Bit(Padd);
	Memory::Set16Bit(Padd, -Data);
	UpdateFlags_NEG_16Bit(Data);
	return true;
}

bool ProgramExecutor::NEG_CASE_3(const std::string& REG8)
{
	//Case-3: NEG REG8
	Byte Data = Register::REG8(REG8);
	Register::REG8(REG8, -Data);
	UpdateFlags_NEG_8Bit(Data);
	return true;
}

bool ProgramExecutor::NEG_CASE_4(const std::string& REG16)
{
	//Case-4: NEG REG16
	Word Data = Register::REG16(REG16);
	Register::REG16(REG16, -Data);
	UpdateFlags_NEG_16Bit(Data);
	return true;
}

bool ProgramExecutor::NEG(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: NEG []
		return NEG_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: NEG W[]
		return NEG_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: NEG REG8
		return NEG_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: NEG REG16
		return NEG_CASE_4(OP);
	}

	return Error::LOG("Execution Failed @NEG\n");
}
