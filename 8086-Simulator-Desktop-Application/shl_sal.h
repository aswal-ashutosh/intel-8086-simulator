#pragma once
#include"8086.h"

//The CF flag contains the value of the last bit shifted out of the destination operand; 
//it is undefined for SHLand SHR instructions where the count is greater than or equal to the size(in bits)
//of the destination operand.The OF flag is affected only for 1 - bit shifts
//otherwise, it is undefined.The SF, ZF, and PF flags are set according to the result.If the count is 0, 
//the flags are not affected.For a non - zero count, the AF flag is undefined.

void ProgramExecutor::UpdateFlags_SHL_SAL_8Bit(const Byte Result, int count)
{
	if (count == 0) { return; }

	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(Result & 0x80) ^ Register::GetFlag(Register::FLAG::CF));
	}
	//else OF is undefined => (I am Keeping the old state)
	//AF is undefined=> (I am Keeping the old state)
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result & 0x80); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result == 0x00); //Zero Flag
}

void ProgramExecutor::UpdateFlags_SHL_SAL_16Bit(const Word Result, int count)
{
	if (count == 0) { return; }

	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(Result & 0x8000) ^ Register::GetFlag(Register::FLAG::CF));
	}
	//else OF is undefined => (I am Keeping the old state)
	//AF is undefined=> (I am Keeping the old state)
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result & 0x8000); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result == 0x0000); //Zero Flag

}

bool ProgramExecutor::SHL_SAL_CASE_1(const std::string& REG8, const std::string& IMMD8)
{
	//Case-1 REG8, IMMD8
	int count = Converter::HexToDec(IMMD8);
	int TCount = count;
	Byte Data = Register::REG8(REG8);
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x80));
		Data <<= 1;
	}
	Register::REG8(REG8, Data);
	UpdateFlags_SHL_SAL_8Bit(Data, count);
	return true;
}

bool ProgramExecutor::SHL_SAL_CASE_2(const std::string& REG8)
{
	//Case-2 REG8, CL
	int count = Register::REG8(REGISTER::CL);
	int TCount = count;
	Byte Data = Register::REG8(REG8);
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x80));
		Data <<= 1;
	}
	Register::REG8(REG8, Data);
	UpdateFlags_SHL_SAL_8Bit(Data, count);
	return true;
}

bool ProgramExecutor::SHL_SAL_CASE_3(const std::string& REG16, const std::string& IMMD8)
{
	//Case-3 REG16, IMMD8
	int count = Converter::HexToDec(IMMD8);
	int TCount = count;
	Word Data = Register::REG16(REG16);
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x8000));
		Data <<= 1;
	}
	Register::REG16(REG16, Data);
	UpdateFlags_SHL_SAL_16Bit(Data, count);
	return true;
}

bool ProgramExecutor::SHL_SAL_CASE_4(const std::string& REG16)
{
	//Case-4 REG16, CL
	int count = Register::REG8(REGISTER::CL);
	int TCount = count;
	Word Data = Register::REG16(REG16);
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x8000));
		Data <<= 1;
	}
	Register::REG16(REG16, Data);
	UpdateFlags_SHL_SAL_16Bit(Data, count);
	return true;
}

bool ProgramExecutor::SHL_SAL_CASE_5(const std::string& MEM8, const std::string& IMMD8)
{
	//Case-5 [], IMMD8
	int count = Converter::HexToDec(IMMD8);
	int TCount = count;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x80));
		Data <<= 1;
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_SHL_SAL_8Bit(Data, count);
	return true;
}

bool ProgramExecutor::SHL_SAL_CASE_6(const std::string& MEM8)
{
	//Case-6 [], CL
	int count = Register::REG8(REGISTER::CL);
	int TCount = count;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x80));
		Data <<= 1;
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_SHL_SAL_8Bit(Data, count);
	return true;
}

bool ProgramExecutor::SHL_SAL_CASE_7(const std::string& MEM16, const std::string& IMMD8)
{
	//Case-7 W[], IMMD8
	int count = Converter::HexToDec(IMMD8);
	int TCount = count;
	int Padd = Memory::PhysicalAddress(MEM16);
	Word Data = Memory::Get16Bit(Padd);
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x8000));
		Data <<= 1;
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_SHL_SAL_16Bit(Data, count);
	return true;
}

bool ProgramExecutor::SHL_SAL_CASE_8(const std::string& MEM16)
{
	//Case-8 W[], CL
	int count = Register::REG8(REGISTER::CL);
	int TCount = count;
	int Padd = Memory::PhysicalAddress(MEM16);
	Word Data = Memory::Get16Bit(Padd);
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x8000));
		Data <<= 1;
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_SHL_SAL_16Bit(Data, count);
	return true;
}

bool ProgramExecutor::SHL_SAL(const Operand& operand)
{
	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	bool OK = false;

	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-1 REG8, IMMD8
		OK = SHL_SAL_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-2 REG8, CL
		OK = SHL_SAL_CASE_2(OP1);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-3 REG16, IMMD8
		OK = SHL_SAL_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-4 REG16, CL
		OK = SHL_SAL_CASE_4(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-5 [], IMMD8
		OK = SHL_SAL_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-6 [], CL
		OK = SHL_SAL_CASE_6(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-7 W[], IMMD8
		OK = SHL_SAL_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-8 W[], CL
		OK = SHL_SAL_CASE_8(OP1);
	}
	else
	{
		return Error::LOG("Unhandled Case @SHL/SAL");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}
