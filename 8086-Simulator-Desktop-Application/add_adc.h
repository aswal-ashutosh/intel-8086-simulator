#pragma once
#include"8086.h"


/*
	If 2 Two's Complement numbers are added, and they both have the same sign, then
	overflow occurs if and only if the result has the opposite sign. Overflow nerver occurs
	when adding operands with different signs.
*/
void ProgramExecutor::UpdateFlags_ADD_8Bit(const Byte OP1, const Byte OP2, const Word Result)
{
	Register::SetFlag(Register::FLAG::CF, Result > 0x00ff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) + (OP2 & 0x0f) > 0x0f); //Auxillary Carry Flag
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits
	Register::SetFlag(Register::FLAG::OF, (OP1 ^ Result8Bit) & (OP2 ^ Result8Bit) & 0x80);//Overflow Flag
	/*
		Same as above one line for Overflow flag
		if ((OP1 & (1 << 7)) ^ (OP2 & (1 << 7)))
		{
			//Different Sign
			Register::SetFlag(Register::FLAG::OF, false);
		}
		else
		{
			//Same Sign
			Register::SetFlag(Register::FLAG::OF, (Result8Bit & (1 << 7)) ^ (OP1 & (1 << 7)));
		}
	*/
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00); //Zero Flag

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_ADC_8Bit(const Byte OP1, const Byte OP2, const Word Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Register::SetFlag(Register::FLAG::CF, Result > 0x00ff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) + (OP2 & 0x0f) > 0x0f); //Auxillary Carry Flag
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits

	Byte OP2_CF = OP2 + oldCF;
	bool MidWayOF = (OP2 ^ OP2_CF) & ((Byte)oldCF ^ OP2_CF) & 0x80;
	Register::SetFlag(Register::FLAG::OF, MidWayOF | (bool)((OP1 ^ Result8Bit) & (OP2_CF ^ Result8Bit) & 0x80));//Over Flow Flag

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_ADD_16Bit(const Word OP1, const Word OP2, const uint32_t Result)
{
	Register::SetFlag(Register::FLAG::CF, Result > 0x0000ffff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x000f) + (OP2 & 0x000f) > 0x000f); //Auxillary Carry Flag
	Word Result16Bit = (Word)Result; //Truncating Extra Bits

	Register::SetFlag(Register::FLAG::OF, (OP1 ^ Result16Bit) & (OP2 ^ Result16Bit) & 0x8000);//Over Flow Flag
	/*
		Same as above one line for Overflow flag
		if ((OP1 & (1 << 15)) ^ (OP2 & (1 << 15)))
		{
			//Different Sign
			Register::SetFlag(Register::FLAG::OF, false);
		}
		else
		{
			//Same Sign
			Register::SetFlag(Register::FLAG::OF, (Result16Bit & (1 << 15)) ^ (OP1 & (1 << 15)));
		}
	*/

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000); //Zero Flag

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_ADC_16Bit(const Word OP1, const Word OP2, const uint32_t Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Register::SetFlag(Register::FLAG::CF, Result > 0x0000ffff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x000f) + (OP2 & 0x000f) > 0x000f); //Auxillary Carry Flag
	Word Result16Bit = (Word)Result; //Truncating Extra Bits

	Word OP2_CF = OP2 + oldCF;
	bool MidWayOF = (OP2 ^ OP2_CF) & ((Word)oldCF ^ OP2_CF) & 0x8000;
	Register::SetFlag(Register::FLAG::OF, MidWayOF | (bool)((OP1 ^ Result16Bit) & (OP2_CF ^ Result16Bit) & 0x8000));

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000);

	/*[TODO][DF]*/
}


bool ProgramExecutor::ADD_CASE_1(const std::string& REG8_D, const std::string& REG8_S, const bool ADC = false)
{
	//Case-1: REG8, REG8
	Byte X = Register::REG8(REG8_D);
	Byte Y = Register::REG8(REG8_S);
	Word REG1 = X;
	Word REG2 = Y;
	REG1 += REG2 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(REG8_D, (Byte)REG1);
	if (ADC)
	{
		UpdateFlags_ADC_8Bit(X, Y, REG1);
	}
	else
	{
		UpdateFlags_ADD_8Bit(X, Y, REG1);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_2(const std::string& REG8, const std::string& MEM8, const bool ADC = false)
{
	//Case-2: REG8, []
	Byte X = Register::REG8(REG8);
	Byte Y = Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	Word REG = X;
	Word MEM = Y;
	REG += MEM + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(REG8, (Byte)REG);
	if (ADC)
	{
		UpdateFlags_ADC_8Bit(X, Y, REG);
	}
	else
	{
		UpdateFlags_ADD_8Bit(X, Y, REG);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_3(const std::string& MEM8, const std::string& REG8, const bool ADC = false)
{
	//Case-3: [], REG8
	int PAdd = Memory::PhysicalAddress(MEM8);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Register::REG8(REG8);
	Word MEM = X;
	Word REG = Y;
	MEM += REG + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set8Bit(PAdd, (Byte)MEM);
	if (ADC)
	{
		UpdateFlags_ADC_8Bit(X, Y, MEM);
	}
	else
	{
		UpdateFlags_ADD_8Bit(X, Y, MEM);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_4(const std::string& REG16_D, const std::string& REG16_S, const bool ADC = false)
{
	//Case-4: REG16, REG16
	Word X = Register::REG16(REG16_D);
	Word Y = Register::REG16(REG16_S);
	uint32_t REG1 = X;
	uint32_t REG2 = Y;
	REG1 += REG2 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(REG16_D, (Word)REG1);
	if (ADC)
	{
		UpdateFlags_ADC_16Bit(X, Y, REG1);
	}
	else
	{
		UpdateFlags_ADD_16Bit(X, Y, REG1);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_5(const std::string& REG16, const std::string& MEM, const bool ADC = false)
{
	//Case-5: REG16, []/W[]
	Word X = Register::REG16(REG16);
	Word Y = Memory::Get16Bit(Memory::PhysicalAddress(MEM));
	uint32_t REG = X;
	uint32_t _MEM = Y;
	REG += _MEM + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(REG16, (Word)REG);
	if (ADC)
	{
		UpdateFlags_ADC_16Bit(X, Y, REG);
	}
	else
	{
		UpdateFlags_ADD_16Bit(X, Y, REG);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_6(const std::string& MEM, const std::string& REG16, const bool ADC = false)
{
	//Case-6: []/W[], REG16
	int PAdd = Memory::PhysicalAddress(MEM);
	Word X = Memory::Get16Bit(PAdd);
	Word Y = Register::REG16(REG16);
	uint32_t _MEM = X;
	uint32_t REG = Y;
	_MEM += REG + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(PAdd, (Word)_MEM);
	if (ADC)
	{
		UpdateFlags_ADC_16Bit(X, Y, _MEM);
	}
	else
	{
		UpdateFlags_ADD_16Bit(X, Y, _MEM);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_7(const std::string& MEM8, const std::string& IMMD8, const bool ADC = false)
{
	//Case-7: [], IMMD8
	int PAdd = Memory::PhysicalAddress(MEM8);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = (Byte)Converter::HexToDec(IMMD8);
	Word MEM = X;
	Word _IMMD8 = Y;
	MEM += _IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set8Bit(PAdd, (Byte)MEM);
	if (ADC)
	{
		UpdateFlags_ADC_8Bit(X, Y, MEM);
	}
	else
	{
		UpdateFlags_ADD_8Bit(X, Y, MEM);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_8(const std::string& MEM, const std::string& IMMD16, const bool ADC = false)
{
	//Case-8: []/W[], IMMD16
	int PAdd = Memory::PhysicalAddress(MEM);
	Word X = Memory::Get16Bit(PAdd);
	Word Y = Converter::HexToDec(IMMD16);
	uint32_t _MEM = X;
	uint32_t _IMMD16 = Y;
	_MEM += _IMMD16 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(PAdd, (Word)_MEM);
	if (ADC)
	{
		UpdateFlags_ADC_16Bit(X, Y, _MEM);
	}
	else
	{
		UpdateFlags_ADD_16Bit(X, Y, _MEM);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_9(const std::string& REG8, const std::string& IMMD8, const bool ADC = false)
{
	//Case-9: REG8, IMMD8
	Byte X = Register::REG8(REG8);
	Byte Y = (Byte)Converter::HexToDec(IMMD8);
	Word REG = X;
	Word _IMMD8 = Y;
	REG += _IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(REG8, (Byte)REG);
	if (ADC)
	{
		UpdateFlags_ADC_8Bit(X, Y, REG);
	}
	else
	{
		UpdateFlags_ADD_8Bit(X, Y, REG);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_10(const std::string& REG16, const std::string& IMMD16, const bool ADC = false)
{
	//Case-10: REG16, IMMD16
	Word X = Register::REG16(REG16);
	Word Y = Converter::HexToDec(IMMD16);
	uint32_t REG = X;
	uint32_t _IMMD16 = Y;
	REG += _IMMD16 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(REG16, (Word)REG);
	if (ADC)
	{
		UpdateFlags_ADC_16Bit(X, Y, REG);
	}
	else
	{
		UpdateFlags_ADD_16Bit(X, Y, REG);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_11(const std::string& REG16, const std::string& IMMD8, const bool ADC = false)
{
	//Case-11: REG16, IMMD8
	Word X = Register::REG16(REG16);
	Word Y = Converter::HexToDec(IMMD8);
	uint32_t REG = X;
	uint32_t _IMMD8 = Y;
	REG += _IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(REG16, (Word)REG);
	if (ADC)
	{
		UpdateFlags_ADC_16Bit(X, Y, REG);
	}
	else
	{
		UpdateFlags_ADD_16Bit(X, Y, REG);
	}
	return true;
}

bool ProgramExecutor::ADD_CASE_12(const std::string& MEM16, const std::string& IMMD8, const bool ADC = false)
{
	//Case-12: W[], IMMD8
	int Padd = Memory::PhysicalAddress(MEM16);
	Word X = Memory::Get16Bit(Padd);
	Word Y = Converter::HexToDec(IMMD8);
	uint32_t MEM = X;
	uint32_t _IMMD8 = Y;
	MEM += _IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(Padd, (Word)MEM);
	if (ADC)
	{
		UpdateFlags_ADC_16Bit(X, Y, MEM);
	}
	else
	{
		UpdateFlags_ADD_16Bit(X, Y, MEM);
	}
	return true;
}

bool ProgramExecutor::ADD(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1: REG8, REG8
		return ADD_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		return ADD_CASE_2(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		return ADD_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		return ADD_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		return ADD_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		return ADD_CASE_6(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		return ADD_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		return ADD_CASE_8(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		return ADD_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		return ADD_CASE_10(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		return ADD_CASE_11(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		return ADD_CASE_12(OP1, OP2);
	}
	return Error::LOG("Execution Failed @ ADD\n");
}

bool ProgramExecutor::ADC(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1: REG8, REG8
		return ADD_CASE_1(OP1, OP2, true);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		return ADD_CASE_2(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		return ADD_CASE_3(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		return ADD_CASE_4(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		return ADD_CASE_5(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		return ADD_CASE_6(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		return ADD_CASE_7(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		return ADD_CASE_8(OP1, OP2, true);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		return ADD_CASE_9(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		return ADD_CASE_10(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		return ADD_CASE_11(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		return ADD_CASE_12(OP1, OP2, true);
	}

	return Error::LOG("Execution Failed @ ADC\n");
}
