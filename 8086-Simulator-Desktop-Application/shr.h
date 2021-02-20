#pragma once
#include"8086.h"

//The CF flag contains the value of the last bit shifted out of the destination operand; 
//it is undefined for SHLand SHR instructions where the count is greater than or equal to the size(in bits)
//of the destination operand.The OF flag is affected only for 1 - bit shifts
//otherwise, it is undefined.The SF, ZF, and PF flags are set according to the result.If the count is 0, 
//the flags are not affected.For a non - zero count, the AF flag is undefined.

void ProgramExecutor::UpdateFlags_SHR_8Bit(const Byte OldData, const Byte NewData, int count)
{
	if (count == 0) { return; }

	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(OldData & 0x80));
	}
	//else OF is undefined => (I am Keeping the old state)
	//AF is undefined=> (I am Keeping the old state)
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(NewData) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, NewData & 0x80); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, NewData == 0x00); //Zero Flag
}

void ProgramExecutor::UpdateFlags_SHR_16Bit(const _16Bit OldData, const _16Bit NewData, int count)
{
	if (count == 0) { return; }

	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(OldData & 0x8000));
	}
	//else OF is undefined => (I am Keeping the old state)
	//AF is undefined=> (I am Keeping the old state)
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(NewData) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, NewData & 0x8000); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, NewData == 0x0000); //Zero Flag
}

bool ProgramExecutor::SHR_CASE_1(const std::string& REG8, const std::string& IMMD8)
{
	//Case-1 REG8, IMMD8
	int count = Converter::HexToDec(IMMD8);
	int TCount = count;
	Byte OldData = Register::REG8(REG8);
	Byte Data = OldData;
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x01));
		Data >>= 1;
	}
	Register::REG8(REG8, Data);
	UpdateFlags_SHR_8Bit(OldData, Data, count);
	return true;
}

bool ProgramExecutor::SHR_CASE_2(const std::string& REG8)
{
	//Case-2 REG8, CL
	int count = Register::REG8(REGISTER::CL);
	int TCount = count;
	Byte OldData = Register::REG8(REG8);
	Byte Data = OldData;
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x01));
		Data >>= 1;
	}
	Register::REG8(REG8, Data);
	UpdateFlags_SHR_8Bit(OldData, Data, count);
	return true;
}

bool ProgramExecutor::SHR_CASE_3(const std::string& REG16, const std::string& IMMD8)
{
	//Case-3 REG16, IMMD8
	int count = Converter::HexToDec(IMMD8);
	int TCount = count;
	_16Bit OldData = Register::REG16(REG16);
	_16Bit Data = OldData;
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x0001));
		Data >>= 1;
	}
	Register::REG16(REG16, Data);
	UpdateFlags_SHR_16Bit(OldData, Data, count);
	return true;
}

bool ProgramExecutor::SHR_CASE_4(const std::string& REG16)
{
	//Case-4 REG16, CL
	int count = Register::REG8(REGISTER::CL);
	int TCount = count;
	_16Bit OldData = Register::REG16(REG16);
	_16Bit Data = OldData;
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x0001));
		Data >>= 1;
	}
	Register::REG16(REG16, Data);
	UpdateFlags_SHR_16Bit(OldData, Data, count);
	return true;
}

bool ProgramExecutor::SHR_CASE_5(const std::string& MEM8, const std::string& IMMD8)
{
	//Case-5 [], IMMD8
	int count = Converter::HexToDec(IMMD8);
	int TCount = count;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte OldData = Memory::Get8Bit(Padd);
	Byte Data = OldData;
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x01));
		Data >>= 1;
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_SHR_8Bit(OldData, Data, count);
	return true;
}

bool ProgramExecutor::SHR_CASE_6(const std::string& MEM8)
{
	//Case-6 [], CL
	int count = Register::REG8(REGISTER::CL);
	int TCount = count;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte OldData = Memory::Get8Bit(Padd);
	Byte Data = OldData;
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x01));
		Data >>= 1;
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_SHR_8Bit(OldData, Data, count);
	return true;
}

bool ProgramExecutor::SHR_CASE_7(const std::string& MEM16, const std::string& IMMD8)
{
	//Case-7 W[], IMMD8
	int count = Converter::HexToDec(IMMD8);
	int TCount = count;
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit OldData = Memory::Get16Bit(Padd);
	_16Bit Data = OldData;
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x0001));
		Data >>= 1;
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_SHR_16Bit(OldData, Data, count);
	return true;
}

bool ProgramExecutor::SHR_CASE_8(const std::string& MEM16)
{
	//Case-8 W[], CL
	int count = Register::REG8(REGISTER::CL);
	int TCount = count;
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit OldData = Memory::Get16Bit(Padd);
	_16Bit Data = OldData;
	while (TCount--)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x0001));
		Data >>= 1;
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_SHR_16Bit(OldData, Data, count);
	return true;
}

bool ProgramExecutor::SHR(const Operand& operand)
{
	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-1 REG8, IMMD8
		return SHR_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-2 REG8, CL
		return SHR_CASE_2(OP1);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-3 REG16, IMMD8
		return SHR_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-4 REG16, CL
		return SHR_CASE_4(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-5 [], IMMD8
		return SHR_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-6 [], CL
		return SHR_CASE_6(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-7 W[], IMMD8
		return SHR_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-8 W[], CL
		return SHR_CASE_8(OP1);

	}
	return Error::LOG("Execution Failed @SHR\n");
}