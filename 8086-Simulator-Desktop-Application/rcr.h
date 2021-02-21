#pragma once
#include"8086.h"

//The CF flag contains the value of the bit shifted into it.The OF flag is affected only for singlebit rotates; 
//it is undefined for multi - bit rotates.The SF, ZF, AF, and PF flags are not affected.

void ProgramExecutor::UpdateFlags_RCR_8Bit(const Byte OldData, int count)
{
	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(OldData & 0x80) ^ Register::GetFlag(Register::FLAG::CF));
	}
	//else not defined => (keeping it same)
}

void ProgramExecutor::UpdateFlags_RCR_16Bit(const _16Bit OldData, int count)
{
	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(OldData & 0x8000) ^ Register::GetFlag(Register::FLAG::CF));
	}
	//else not defined => (keeping it same)
}

bool ProgramExecutor::RCR_CASE_1(const std::string& REG8, const std::string& IMMD8)
{
	//Case-1 REG8, IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 9; //We can consider this as rotating a array of size 9(Will be same after every 9N rotation)
	Byte OldData = Register::REG8(REG8);
	Byte Data = OldData;
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x01));
		Data >>= 1;
		Data |= (Byte)(OldCarry << 7);
	}
	Register::REG8(REG8, Data);
	UpdateFlags_RCR_8Bit(OldData, RealCount);
	return true;
}

bool ProgramExecutor::RCR_CASE_2(const std::string& REG8)
{
	//Case-2 REG8, CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 9;
	Byte OldData = Register::REG8(REG8);
	Byte Data = OldData;
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x01));
		Data >>= 1;
		Data |= (Byte)(OldCarry << 7);
	}
	Register::REG8(REG8, Data);
	UpdateFlags_RCR_8Bit(OldData, RealCount);
	return true;
}

bool ProgramExecutor::RCR_CASE_3(const std::string& REG16, const std::string& IMMD8)
{
	//Case-3 REG16, IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 17;//We can consider this as rotating a array of size 17(Will be same after every 17N rotation) 
	_16Bit OldData = Register::REG16(REG16);
	_16Bit Data = OldData;
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x0001));
		Data >>= 1;
		Data |= (_16Bit)(OldCarry << 15);
	}
	Register::REG16(REG16, Data);
	UpdateFlags_RCR_16Bit(OldData, RealCount);
	return true;
}

bool ProgramExecutor::RCR_CASE_4(const std::string& REG16)
{
	//Case-4 REG16, CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 17;
	_16Bit OldData = Register::REG16(REG16);
	_16Bit Data = OldData;
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x0001));
		Data >>= 1;
		Data |= (_16Bit)(OldCarry << 15);
	}
	Register::REG16(REG16, Data);
	UpdateFlags_RCR_16Bit(OldData, RealCount);
	return true;
}

bool ProgramExecutor::RCR_CASE_5(const std::string& MEM8, const std::string& IMMD8)
{
	//Case-5 [], IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 9;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte OldData = Memory::Get8Bit(Padd);
	Byte Data = OldData;
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x01));
		Data >>= 1;
		Data |= (Byte)(OldCarry << 7);
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_RCR_8Bit(OldData, RealCount);
	return true;
}

bool ProgramExecutor::RCR_CASE_6(const std::string& MEM8)
{
	//Case-6 [], CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 9;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte OldData = Memory::Get8Bit(Padd);
	Byte Data = OldData;
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x01));
		Data >>= 1;
		Data |= (Byte)(OldCarry << 7);
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_RCR_8Bit(OldData, RealCount);
	return true;
}

bool ProgramExecutor::RCR_CASE_7(const std::string& MEM16, const std::string& IMMD8)
{
	//Case-7 W[], IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 17;
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit OldData = Memory::Get16Bit(Padd);
	_16Bit Data = OldData;
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x0001));
		Data >>= 1;
		Data |= (_16Bit)(OldCarry << 15);
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_RCR_16Bit(OldData, RealCount);
	return true;
}

bool ProgramExecutor::RCR_CASE_8(const std::string& MEM16)
{
	//Case-8 W[], CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 17;
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit OldData = Memory::Get16Bit(Padd);
	_16Bit Data = OldData;
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x0001));
		Data >>= 1;
		Data |= (_16Bit)(OldCarry << 15);
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_RCR_16Bit(OldData, RealCount);
	return true;
}

bool ProgramExecutor::RCR(const Operand& operand)
{
	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-1 REG8, IMMD8
		return RCR_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-2 REG8, CL
		return RCR_CASE_2(OP1);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-3 REG16, IMMD8
		return RCR_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-4 REG16, CL
		return RCR_CASE_4(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-5 [], IMMD8
		return RCR_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-6 [], CL
		return RCR_CASE_6(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-7 W[], IMMD8
		return RCR_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-8 W[], CL
		return RCR_CASE_8(OP1);

	}
	return Error::LOG("Execution Failed @RCR\n");
}