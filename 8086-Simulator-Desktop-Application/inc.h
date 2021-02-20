#pragma once
#include"8086.h"

//The CF flag is not affected. The OF, SF, ZF, AF, and PF flags are set according to the result.


void ProgramExecutor::UpdateFlags_INC_8Bit(const Byte Data)
{
	Register::SetFlag(Register::FLAG::AF, (Data & 0x0f) + 0x01 > 0x0f);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (Byte)0x7f);//Overflow Flag
	Byte Result = Data + 1;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 7)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x00); //Zero Flag
}

void ProgramExecutor::UpdateFlags_INC_16Bit(const _16Bit Data)
{
	Register::SetFlag(Register::FLAG::AF, (Data & 0x000f) + 0x0001 > 0x000f);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (_16Bit)0x7fff);//Overflow Flag
	_16Bit Result = Data + 1;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 15)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x0000); //Zero Flag
}

bool ProgramExecutor::INC_CASE_1(const std::string& MEM8)
{
	//Case-1: INC []
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	Memory::Set8Bit(Padd, Data + 1);
	UpdateFlags_INC_8Bit(Data);
	return true;
}

bool ProgramExecutor::INC_CASE_2(const std::string& MEM16)
{
	//Case-2: INC W[]
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit Data = Memory::Get16Bit(Padd);
	Memory::Set16Bit(Padd, Data + 1);
	UpdateFlags_INC_16Bit(Data);
	return true;
}

bool ProgramExecutor::INC_CASE_3(const std::string& REG8)
{
	//Case-3: INC REG8
	Byte Data = Register::REG8(REG8);
	Register::REG8(REG8, Data + 1);
	UpdateFlags_INC_8Bit(Data);
	return true;
}

bool ProgramExecutor::INC_CASE_4(const std::string& REG16)
{
	//Case-4: INC REG16
	_16Bit Data = Register::REG16(REG16);
	Register::REG16(REG16, Data + 1);
	UpdateFlags_INC_16Bit(Data);
	return true;
}

bool ProgramExecutor::INC(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: INC []
		return INC_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: INC W[]
		return INC_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: INC REG8
		return INC_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: INC REG16
		return INC_CASE_4(OP);
	}

	return Error::LOG("Wrong Syntax @INC\n");
}