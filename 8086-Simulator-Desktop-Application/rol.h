#pragma once
#include"8086.h"

//The CF flag contains the value of the bit shifted into it.The OF flag is affected only for singlebit rotates; 
//it is undefined for multi - bit rotates.The SF, ZF, AF, and PF flags are not affected.

/*
In ROL, during every rotation MSB move to LSB as well as to Carry, So Instead of updating carry in each roation we
can update it after all rotations are performed, as the bit which is at LSB after the last rotation must also be at Carry.
Edge Case: If count of roation is zero than do not change carry to LSB as no rotation was there so carry must not be changed.
*/
void ProgramExecutor::UpdateFlags_ROL_8Bit(const Byte Result, int count)
{
	if (count != 0)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Result & 0x01));
	}

	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(Result & 0x80) ^ Register::GetFlag(Register::FLAG::CF));
	}
	//else not defined => (keeping it same)
}

void ProgramExecutor::UpdateFlags_ROL_16Bit(const Word Result, int count)
{
	if (count != 0)
	{
		Register::SetFlag(Register::FLAG::CF, bool(Result & 0x0001));
	}

	if (count == 1)
	{
		Register::SetFlag(Register::FLAG::OF, (bool)(Result & 0x8000) ^ Register::GetFlag(Register::FLAG::CF));
	}
	//else not defined => (keeping it same)
}

bool ProgramExecutor::ROL_CASE_1(const std::string& REG8, const std::string& IMMD8)
{
	//Case-1 REG8, IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 8; //We can consider this as rotating a array of size 8(Will be same after every 8N rotation) 
	Byte Data = Register::REG8(REG8);
	while (OptimalCount--)
	{
		bool MSB = bool(Data & 0x80);
		Data <<= 1;
		Data |= (Byte)MSB;
	}
	Register::REG8(REG8, Data);
	UpdateFlags_ROL_8Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::ROL_CASE_2(const std::string& REG8)
{
	//Case-2 REG8, CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 8;
	Byte Data = Register::REG8(REG8);
	while (OptimalCount--)
	{
		bool MSB = bool(Data & 0x80);
		Data <<= 1;
		Data |= (Byte)MSB;
	}
	Register::REG8(REG8, Data);
	UpdateFlags_ROL_8Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::ROL_CASE_3(const std::string& REG16, const std::string& IMMD8)
{
	//Case-3 REG16, IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 16;//We can consider this as rotating a array of size 16(Will be same after every 16N rotation) 
	Word Data = Register::REG16(REG16);
	while (OptimalCount--)
	{
		bool MSB = bool(Data & 0x8000);
		Data <<= 1;
		Data |= (Word)MSB;
	}
	Register::REG16(REG16, Data);
	UpdateFlags_ROL_16Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::ROL_CASE_4(const std::string& REG16)
{
	//Case-4 REG16, CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 16;
	Word Data = Register::REG16(REG16);
	while (OptimalCount--)
	{
		bool MSB = bool(Data & 0x8000);
		Data <<= 1;
		Data |= (Word)MSB;
	}
	Register::REG16(REG16, Data);
	UpdateFlags_ROL_16Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::ROL_CASE_5(const std::string& MEM8, const std::string& IMMD8)
{
	//Case-5 [], IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 8;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	while (OptimalCount--)
	{
		bool MSB = bool(Data & 0x80);
		Data <<= 1;
		Data |= (Byte)MSB;
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_ROL_8Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::ROL_CASE_6(const std::string& MEM8)
{
	//Case-6 [], CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 8;
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	while (OptimalCount--)
	{
		bool MSB = bool(Data & 0x80);
		Data <<= 1;
		Data |= (Byte)MSB;
	}
	Memory::Set8Bit(Padd, Data);
	UpdateFlags_ROL_8Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::ROL_CASE_7(const std::string& MEM16, const std::string& IMMD8)
{
	//Case-7 W[], IMMD8
	int RealCount = Converter::HexToDec(IMMD8);
	int OptimalCount = RealCount % 16;
	int Padd = Memory::PhysicalAddress(MEM16);
	Word Data = Memory::Get16Bit(Padd);
	while (OptimalCount--)
	{
		bool MSB = bool(Data & 0x8000);
		Data <<= 1;
		Data |= (Word)MSB;
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_ROL_16Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::ROL_CASE_8(const std::string& MEM16)
{
	//Case-8 W[], CL
	int RealCount = Register::REG8(REGISTER::CL);
	int OptimalCount = RealCount % 16;
	int Padd = Memory::PhysicalAddress(MEM16);
	Word Data = Memory::Get16Bit(Padd);
	while (OptimalCount--)
	{
		bool MSB = bool(Data & 0x8000);
		Data <<= 1;
		Data |= (Word)MSB;
	}
	Memory::Set16Bit(Padd, Data);
	UpdateFlags_ROL_16Bit(Data, RealCount);
	return true;
}

bool ProgramExecutor::ROL(const Operand& operand)
{
	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	bool OK = false;

	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-1 REG8, IMMD8
		OK = ROL_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-2 REG8, CL
		OK = ROL_CASE_2(OP1);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-3 REG16, IMMD8
		OK = ROL_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-4 REG16, CL
		OK = ROL_CASE_4(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-5 [], IMMD8
		OK = ROL_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-6 [], CL
		OK = ROL_CASE_6(OP1);

	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-7 W[], IMMD8
		OK = ROL_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-8 W[], CL
		OK = ROL_CASE_8(OP1);
	}
	else
	{
		return Error::LOG("Unhandled Case @ROL");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}