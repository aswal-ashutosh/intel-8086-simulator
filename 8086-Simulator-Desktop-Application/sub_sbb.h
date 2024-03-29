#pragma once
#include"8086.h"

/*
	If 2 Two's Complement numbers are added, and they both have the same sign, then
	overflow occurs if and only if the result has the opposite sign. Overflow nerver occurs
	when adding operands with different signs.
*/

void ProgramExecutor::UpdateFlags_SUB_8Bit(const Byte OP1, const Byte OP2, const Word Result)
{
	Byte _2SC = -OP2;
	Register::SetFlag(Register::FLAG::CF, OP1 < OP2); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) < (OP2 & 0x0f)); //Auxillary Carry Flag
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits

	Register::SetFlag(Register::FLAG::OF, (OP1 ^ Result8Bit) & (_2SC ^ Result8Bit) & 0x80);//Overflow Flag

	//if ((OP1 & (1 << 7)) ^ (_2SC & (1 << 7)))
	//{
	//	//Different Sign
	//	Register::SetFlag(Register::FLAG::OF, false);
	//}
	//else
	//{
	//	//Same Sign
	//	Register::SetFlag(Register::FLAG::OF, (Result8Bit & (1 << 7)) ^ (OP1 & (1 << 7)));
	//}

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_SUB_16Bit(const Word OP1, const Word OP2, const uint32_t Result)
{
	Word _2SC = -OP2;
	Register::SetFlag(Register::FLAG::CF, OP1 < OP2); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x000f) < (OP2 & 0x000f)); //Auxillary Carry Flag
	Word Result16Bit = (Word)Result; //Truncating Extra Bits

	Register::SetFlag(Register::FLAG::OF, (OP1 ^ Result16Bit) & (_2SC ^ Result16Bit) & 0x8000);//Over Flow Flag

	//if ((OP1 & (1 << 15)) ^ (_2SC & (1 << 15)))
	//{
	//	//Different Sign
	//	Register::SetFlag(Register::FLAG::OF, false);
	//}
	//else
	//{
	//	//Same Sign
	//	Register::SetFlag(Register::FLAG::OF, (Result16Bit & (1 << 15)) ^ (OP1 & (1 << 15)));
	//}

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_SBB_8Bit(const Byte OP1, const Byte OP2, const Word Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Byte _2SC_OP2 = -OP2;
	Byte _2SC_CF = oldCF ? 0xff : 0x00;
	Register::SetFlag(Register::FLAG::CF, OP1 < (OP2 + oldCF)); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) < (OP2 & 0x0f)); //Auxillary Carry Flag
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits


	Byte _2SC_OP2_CF = _2SC_OP2 + _2SC_CF;
	bool MidWayOF = (_2SC_OP2 ^ _2SC_OP2_CF) & (_2SC_CF ^ _2SC_OP2_CF) & 0x80;
	Register::SetFlag(Register::FLAG::OF, MidWayOF | (bool)((OP1 ^ Result8Bit) & (_2SC_OP2_CF ^ Result8Bit) & 0x80));//Overflow Flag

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_SBB_16Bit(const Word OP1, const Word OP2, const uint32_t Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Word _2SC_OP2 = -OP2;
	Word _2SC_CF = oldCF ? 0xffff : 0x0000;
	Register::SetFlag(Register::FLAG::CF, OP1 < (OP2 + oldCF)); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x000f) < (OP2 & 0x000f)); //Auxillary Carry Flag
	Word Result16Bit = (Word)Result; //Truncating Extra Bits

	Word _2SC_OP2_CF = _2SC_OP2 + _2SC_CF;
	bool MidWayOF = (_2SC_OP2 ^ _2SC_OP2_CF) & (_2SC_CF ^ _2SC_OP2_CF) & 0x8000;
	Register::SetFlag(Register::FLAG::OF, MidWayOF | (bool)((OP1 ^ Result16Bit) & (_2SC_OP2_CF ^ Result16Bit) & 0x8000));//Overflow Flag

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000);

	/*[TODO][DF]*/
}



bool ProgramExecutor::SUB_CASE_1(const std::string& REG8_D, const std::string& REG8_S, const bool SBB = false)
{
	//Case-1: REG8, REG8
	Byte X = Register::REG8(REG8_D);
	Byte Y = Register::REG8(REG8_S);
	Byte _2SC = -Y;
	Word Result = Word(X) + Word(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Register::REG8(REG8_D, (Byte)Result);
	if (SBB)
	{
		UpdateFlags_SBB_8Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_8Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_2(const std::string& REG8, const std::string& MEM8, const bool SBB = false)
{
	//Case-2: REG8, []
	Byte X = Register::REG8(REG8);
	Byte Y = Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	Byte _2SC = -Y;
	Word Result = Word(X) + Word(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Register::REG8(REG8, (Byte)Result);
	if (SBB)
	{
		UpdateFlags_SBB_8Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_8Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_3(const std::string& MEM8, const std::string& REG8, const bool SBB = false)
{
	//Case-3: [], REG8
	int PAdd = Memory::PhysicalAddress(MEM8);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Register::REG8(REG8);
	Byte _2SC = -Y;
	Word Result = Word(X) + Word(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Memory::Set8Bit(PAdd, (Byte)Result);
	if (SBB)
	{
		UpdateFlags_SBB_8Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_8Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_4(const std::string& REG16_D, const std::string& REG16_S, const bool SBB = false)
{
	//Case-4: REG16, REG16
	Word X = Register::REG16(REG16_D);
	Word Y = Register::REG16(REG16_S);
	Word _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(REG16_D, (Word)Result);
	if (SBB)
	{
		UpdateFlags_SBB_16Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_16Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_5(const std::string& REG16, const std::string& MEM, const bool SBB = false)
{
	//Case-5: REG16, []/W[]
	Word X = Register::REG16(REG16);
	Word Y = Memory::Get16Bit(Memory::PhysicalAddress(MEM));
	Word _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(REG16, (Word)Result);
	if (SBB)
	{
		UpdateFlags_SBB_16Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_16Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_6(const std::string& MEM, const std::string& REG16, const bool SBB = false)
{
	//Case-6: []/W[], REG16
	int PAdd = Memory::PhysicalAddress(MEM);
	Word X = Memory::Get16Bit(PAdd);
	Word Y = Register::REG16(REG16);
	Word _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Memory::Set16Bit(PAdd, (Word)Result);
	if (SBB)
	{
		UpdateFlags_SBB_16Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_16Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_7(const std::string& MEM8, const std::string& IMMD8, const bool SBB = false)
{
	//Case-7: [], IMMD8
	int PAdd = Memory::PhysicalAddress(MEM8);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = (Byte)Converter::HexToDec(IMMD8);
	Byte _2SC = -Y;
	Word Result = Word(X) + Word(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Memory::Set8Bit(PAdd, (Byte)Result);
	if (SBB)
	{
		UpdateFlags_SBB_8Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_8Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_8(const std::string& MEM, const std::string& IMMD16, const bool SBB = false)
{
	//Case-8: []/W[], IMMD16
	int PAdd = Memory::PhysicalAddress(MEM);
	Word X = Memory::Get16Bit(PAdd);
	Word Y = Converter::HexToDec(IMMD16);
	Word _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Memory::Set16Bit(PAdd, (Word)Result);
	if (SBB)
	{
		UpdateFlags_SBB_16Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_16Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_9(const std::string& REG8, const std::string& IMMD8, const bool SBB = false)
{
	//Case-9: REG8, IMMD8
	Byte X = Register::REG8(REG8);
	Byte Y = (Byte)Converter::HexToDec(IMMD8);
	Byte _2SC = -Y;
	Word Result = Word(X) + Word(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Register::REG8(REG8, (Byte)Result);
	if (SBB)
	{
		UpdateFlags_SBB_8Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_8Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_10(const std::string& REG16, const std::string& IMMD16, const bool SBB = false)
{
	//Case-10: REG16, IMMD16
	Word X = Register::REG16(REG16);
	Word Y = Converter::HexToDec(IMMD16);
	Word _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(REG16, (Word)Result);
	if (SBB)
	{
		UpdateFlags_SBB_16Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_16Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_11(const std::string& REG16, const std::string& IMMD8, const bool SBB = false)
{
	//Case-11: REG16, IMMD8
	Word X = Register::REG16(REG16);
	Word Y = Converter::HexToDec(IMMD8);
	Word _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(REG16, (Word)Result);
	if (SBB)
	{
		UpdateFlags_SBB_16Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_16Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB_CASE_12(const std::string& MEM16, const std::string& IMMD8, const bool SBB = false)
{
	//Case-12: W[], IMMD8
	int Padd = Memory::PhysicalAddress(MEM16);
	Word X = Memory::Get16Bit(Padd);
	Word Y = Converter::HexToDec(IMMD8);
	Word _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Memory::Set16Bit(Padd, (Word)Result);
	if (SBB)
	{
		UpdateFlags_SBB_16Bit(X, Y, Result);
	}
	else
	{
		UpdateFlags_SUB_16Bit(X, Y, Result);
	}
	return true;
}

bool ProgramExecutor::SUB(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;

	bool OK = false;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1: REG8, REG8
		OK = SUB_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		OK = SUB_CASE_2(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		OK = SUB_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		OK = SUB_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		OK = SUB_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		OK = SUB_CASE_6(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		OK = SUB_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		OK = SUB_CASE_8(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		OK = SUB_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		OK = SUB_CASE_10(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		OK = SUB_CASE_11(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		OK = SUB_CASE_12(OP1, OP2);
	}
	else
	{
		return Error::LOG("Unhandled Case @SUB");
	}	
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}

bool ProgramExecutor::SBB(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;

	bool OK = false;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1: REG8, REG8
		OK = SUB_CASE_1(OP1, OP2, true);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		OK = SUB_CASE_2(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		OK = SUB_CASE_3(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		OK = SUB_CASE_4(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		OK = SUB_CASE_5(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		OK = SUB_CASE_6(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		OK = SUB_CASE_7(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		OK = SUB_CASE_8(OP1, OP2, true);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		OK = SUB_CASE_9(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		OK = SUB_CASE_10(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		OK = SUB_CASE_11(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		OK = SUB_CASE_12(OP1, OP2, true);
	}
	else
	{
		return Error::LOG("Unhandled Case @SBB");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}
