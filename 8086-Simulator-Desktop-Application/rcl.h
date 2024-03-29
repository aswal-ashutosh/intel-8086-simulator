#pragma once
#include"8086.h"

//The CF flag contains the value of the bit shifted into it.The OF flag is affected only for singlebit rotates; 
//it is undefined for multi - bit rotates.The SF, ZF, AF, and PF flags are not affected.

void ProgramExecutor::UpdateFlags_RCL_8Bit(const Byte Result, int count)
{
	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(Result & 0x80) ^ Register::GetFlag(Register::FLAG::CF));
	}
	//else not defined => (keeping it same)
}

void ProgramExecutor::UpdateFlags_RCL_16Bit(const Word Result, int count)
{
	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(Result & 0x8000) ^ Register::GetFlag(Register::FLAG::CF));
	}
	//else not defined => (keeping it same)
}

bool ProgramExecutor::RCL_CASE_1(const std::string& REG8, const std::string& IMMD8)
{
	//Case-1 REG8, IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 9; //We can consider this as rotating a array of size 9(Will be same after every 9N rotation) 
	Byte Data = Register::REG8(REG8);
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x80));
		Data <<= 1;
		Data |= (Byte)OldCarry;
	}
	Register::REG8(REG8, Data);
	UpdateFlags_RCL_8Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::RCL_CASE_2(const std::string& REG8)
{
	//Case-2 REG8, CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 9;
	Byte Data = Register::REG8(REG8);
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x80));
		Data <<= 1;
		Data |= (Byte)OldCarry;
	}
	Register::REG8(REG8, Data);
	UpdateFlags_RCL_8Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::RCL_CASE_3(const std::string& REG16, const std::string& IMMD8)
{
	//Case-3 REG16, IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 17;//We can consider this as rotating a array of size 17(Will be same after every 17N rotation) 
	Word Data = Register::REG16(REG16);
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x8000));
		Data <<= 1;
		Data |= (Word)OldCarry;
	}
	Register::REG16(REG16, Data);
	UpdateFlags_RCL_16Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::RCL_CASE_4(const std::string& REG16)
{
	//Case-4 REG16, CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 17;
	Word Data = Register::REG16(REG16);
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x8000));
		Data <<= 1;
		Data |= (Word)OldCarry;
	}
	Register::REG16(REG16, Data);
	UpdateFlags_RCL_16Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::RCL_CASE_5(const std::string& MEM8, const std::string& IMMD8)
{
	//Case-5 [], IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 9;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x80));
		Data <<= 1;
		Data |= (Byte)OldCarry;
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_RCL_8Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::RCL_CASE_6(const std::string& MEM8)
{
	//Case-6 [], CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 9;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x80));
		Data <<= 1;
		Data |= (Byte)OldCarry;
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_RCL_8Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::RCL_CASE_7(const std::string& MEM16, const std::string& IMMD8)
{
	//Case-7 W[], IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 17;
	int Padd = Memory::PhysicalAddress(MEM16);
	Word Data = Memory::Get16Bit(Padd);
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x8000));
		Data <<= 1;
		Data |= (Word)OldCarry;
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_RCL_16Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::RCL_CASE_8(const std::string& MEM16)
{
	//Case-8 W[], CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 17;
	int Padd = Memory::PhysicalAddress(MEM16);
	Word Data = Memory::Get16Bit(Padd);
	while (OptimalCount--)
	{
		bool OldCarry = Register::GetFlag(Register::FLAG::CF);
		Register::SetFlag(Register::FLAG::CF, bool(Data & 0x8000));
		Data <<= 1;
		Data |= (Word)OldCarry;
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_RCL_16Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::RCL(const Operand& operand)
{
	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	bool OK = false;

	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-1 REG8, IMMD8
		OK = RCL_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-2 REG8, CL
		OK = RCL_CASE_2(OP1);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-3 REG16, IMMD8
		OK = RCL_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-4 REG16, CL
		OK = RCL_CASE_4(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-5 [], IMMD8
		OK = RCL_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-6 [], CL
		OK = RCL_CASE_6(OP1);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-7 W[], IMMD8
		OK = RCL_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-8 W[], CL
		OK = RCL_CASE_8(OP1);
	}
	else
	{
		return Error::LOG("Unhandled Case @RCL");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}