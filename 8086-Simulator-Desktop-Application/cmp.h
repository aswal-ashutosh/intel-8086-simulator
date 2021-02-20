#pragma once
#include"8086.h"

void ProgramExecutor::UpdateFlags_CMP_8Bit(const Byte OP1, const Byte OP2, const _16Bit Result)
{
	Byte _2SC = -OP2;
	Register::SetFlag(Register::FLAG::CF, OP1 < OP2); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) < (OP2 & 0x0f)); //Auxillary Carry Flag
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits

	//Over Flow Flag
	/*
		If 2 Two's Complement numbers are subtracted, and their signs are different, then
		overflow occurs if and only if the result has the same sign as the subtrahend.
										OR
		We can just calculate it by considering it the sum of OP1 and 2s complement of OP2
	*/

	if ((OP1 & (1 << 7)) ^ (_2SC & (1 << 7)))
	{
		//Different Sign
		Register::SetFlag(Register::FLAG::OF, false);
	}
	else
	{
		//Same Sign
		Register::SetFlag(Register::FLAG::OF, (Result8Bit & (1 << 7)) ^ (OP1 & (1 << 7)));
	}

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_CMP_16Bit(const _16Bit OP1, const _16Bit OP2, const uint32_t Result)
{
	_16Bit _2SC = -OP2;
	Register::SetFlag(Register::FLAG::CF, OP1 < OP2); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x000f) < (OP2 & 0x000f)); //Auxillary Carry Flag
	_16Bit Result16Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
	if ((OP1 & (1 << 15)) ^ (_2SC & (1 << 15)))
	{
		//Different Sign
		Register::SetFlag(Register::FLAG::OF, false);
	}
	else
	{
		//Same Sign
		Register::SetFlag(Register::FLAG::OF, (Result16Bit & (1 << 15)) ^ (OP1 & (1 << 15)));
	}

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000);

	/*[TODO][DF]*/
}

bool ProgramExecutor::CMP_CASE_1(const std::string& REG8_D, const std::string& REG8_S)
{
	//Case-1: REG8, REG8
	Byte X = Register::REG8(REG8_D);
	Byte Y = Register::REG8(REG8_S);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_2(const std::string& REG8, const std::string& MEM8)
{
	//Case-2: REG8, []
	Byte X = Register::REG8(REG8);
	Byte Y = Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_3(const std::string& MEM, const std::string& REG8)
{
	//Case-3: [], REG8
	int PAdd = Memory::PhysicalAddress(MEM);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Register::REG8(REG8);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_4(const std::string& REG16_D, const std::string& REG16_S)
{
	//Case-4: REG16, REG16
	_16Bit X = Register::REG16(REG16_D);
	_16Bit Y = Register::REG16(REG16_S);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_5(const std::string& REG16, const std::string& MEM)
{
	//Case-5: REG16, []/W[]
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Memory::Get16Bit(Memory::PhysicalAddress(MEM));
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_6(const std::string& MEM, const std::string& REG16)
{
	//Case-6: []/W[], REG16
	int PAdd = Memory::PhysicalAddress(MEM);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Register::REG16(REG16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_7(const std::string& MEM8, const std::string& IMMD8)
{
	//Case-7: [], IMMD8
	int PAdd = Memory::PhysicalAddress(MEM8);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = (Byte)Converter::HexToDec(IMMD8);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_8(const std::string& MEM, const std::string& REG16)
{
	//Case-8: []/W[], IMMD16
	int PAdd = Memory::PhysicalAddress(MEM);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Converter::HexToDec(REG16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_9(const std::string& REG8, const std::string& IMMD8)
{
	//Case-9: REG8, IMMD8
	Byte X = Register::REG8(REG8);
	Byte Y = (Byte)Converter::HexToDec(IMMD8);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_10(const std::string& REG16, const std::string& IMMD16)
{
	//Case-10: REG16, IMMD16
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Converter::HexToDec(IMMD16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_11(const std::string& REG16, const std::string& IMMD8)
{
	//Case-11: REG16, IMMD8
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Converter::HexToDec(IMMD8);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_12(const std::string& MEM16, const std::string& IMMD8)
{
	//Case-12: W[], IMMD8
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit X = Memory::Get16Bit(Padd);
	_16Bit Y = Converter::HexToDec(IMMD8);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1: REG8, REG8
		return CMP_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		return CMP_CASE_2(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		return CMP_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		return CMP_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		return CMP_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		return CMP_CASE_6(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		return CMP_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		return CMP_CASE_8(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		return CMP_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		return CMP_CASE_10(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		return CMP_CASE_11(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		return CMP_CASE_12(OP1, OP2);
	}
	return Error::LOG("Execution Failed @ CMP\n");
}
