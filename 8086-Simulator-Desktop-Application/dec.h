#pragma once
#include"8086.h"
//The CF flag is not affected.The OF, SF, ZF, AF, and PF flags are set according to the result.

void ProgramExecutor::UpdateFlags_DEC_8Bit(const Byte Data)
{
	Register::SetFlag(Register::FLAG::AF, (Data & 0x0f) < 0x01);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (Byte)0x80);//Overflow Flag
	Byte Result = Data - 1;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 7)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x00); //Zero Flag
}

void ProgramExecutor::UpdateFlags_DEC_16Bit(const Word Data)
{
	Register::SetFlag(Register::FLAG::AF, (Data & 0x000f) < 0x0001);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (Word)0x8000);//Overflow Flag
	Word Result = Data - 1;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 15)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x0000); //Zero Flag
}

bool ProgramExecutor::DEC_CASE_1(const std::string& MEM8)
{
	//Case-1: DEC []
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	Memory::Set8Bit(Padd, Data - 1);
	UpdateFlags_DEC_8Bit(Data);
	return true;

}

bool ProgramExecutor::DEC_CASE_2(const std::string& MEM16)
{
	//Case-2: DEC W[]
	int Padd = Memory::PhysicalAddress(MEM16);
	Word Data = Memory::Get16Bit(Padd);
	Memory::Set16Bit(Padd, Data - 1);
	UpdateFlags_DEC_16Bit(Data);
	return true;
}

bool ProgramExecutor::DEC_CASE_3(const std::string& REG8)
{
	//Case-3: DEC REG8
	Byte Data = Register::REG8(REG8);
	Register::REG8(REG8, Data - 1);
	UpdateFlags_DEC_8Bit(Data);
	return true;
}

bool ProgramExecutor::DEC_CASE_4(const std::string& REG16)
{
	//Case-4: DEC REG16
	Word Data = Register::REG16(REG16);
	Register::REG16(REG16, Data - 1);
	UpdateFlags_DEC_16Bit(Data);
	return true;
}

bool ProgramExecutor::DEC(const Operand& operand)
{
	std::string OP = operand.first;

	bool OK = false;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: DEC []
		OK = DEC_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: DEC W[]
		OK = DEC_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: DEC REG8
		OK = DEC_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: DEC REG16
		OK = DEC_CASE_4(OP);
	}
	else
	{
		return Error::LOG("Unhandled Case @ DEC");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}
