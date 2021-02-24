#pragma once
#include"8086.h"

bool ProgramExecutor::MOV_CASE_1(const std::string& REG8, const std::string& IMMD8)
{
	//Case-1:MOV REG8, immd8
	Register::REG8(REG8, (Byte)Converter::HexToDec(IMMD8));
	return true;
}

bool ProgramExecutor::MOV_CASE_2(const std::string& REG16, const std::string& IMMD)
{
	//Case-2:MOV REG16, immd16/immd8
	Register::REG16(REG16, Converter::HexToDec(IMMD));
	return true;
}

bool ProgramExecutor::MOV_CASE_3(const std::string& MEM8, const std::string& IMMD8)
{
	//Case-3:[], immd8
	Memory::Set8Bit(Memory::PhysicalAddress(MEM8), (Byte)Converter::HexToDec(IMMD8));
	return true;
}

bool ProgramExecutor::MOV_CASE_4(const std::string& MEM, const std::string& IMMD16)
{
	//Case-4:[]/W[], immd16
	Memory::Set16Bit(Memory::PhysicalAddress(MEM), Converter::HexToDec(IMMD16));
	return true;
}

bool ProgramExecutor::MOV_CASE_5(const std::string& MEM16, const std::string& IMMD8)
{
	//Case-5:W[], immd8
	Memory::Set16Bit(Memory::PhysicalAddress(MEM16), Converter::HexToDec(IMMD8));
	return true;
}

bool ProgramExecutor::MOV_CASE_6(const std::string& REG8_D, const std::string& REG8_S)
{
	//Case-6: REG8, REG8
	Register::REG8(REG8_D, Register::REG8(REG8_S));
	return true;
}

bool ProgramExecutor::MOV_CASE_7(const std::string& REG16_D, const std::string& REG16_S)
{
	//Case-7: REG16, REG16
	Register::REG16(REG16_D, Register::REG16(REG16_S));
	return true;
}

bool ProgramExecutor::MOV_CASE_8(const std::string& REG8, const std::string& MEM8)
{
	//Case-8: REG8, []
	Register::REG8(REG8, Memory::Get8Bit(Memory::PhysicalAddress(MEM8)));
	return true;
}

bool ProgramExecutor::MOV_CASE_9(const std::string& REG16, const std::string& MEM)
{
	//Case-9: REG16, []/W[]
	Register::REG16(REG16, Memory::Get16Bit(Memory::PhysicalAddress(MEM)));
	return true;
}

bool ProgramExecutor::MOV_CASE_10(const std::string& MEM8, const std::string& REG8)
{
	//Case-10: [], REG8
	Memory::Set8Bit(Memory::PhysicalAddress(MEM8), Register::REG8(REG8));
	return true;
}

bool ProgramExecutor::MOV_CASE_11(const std::string& MEM, const std::string& REG16)
{
	//Case-11: []/W[], REG16
	Memory::Set16Bit(Memory::PhysicalAddress(MEM), Register::REG16(REG16));
	return true;
}

bool ProgramExecutor::MOV_CASE_12(const std::string& SREG, const std::string& REG16)
{
	//Case-12: SREG, REG16
	Register::REG16(SREG, Register::REG16(REG16));
	return true;
}

bool ProgramExecutor::MOV_CASE_13(const std::string& SREG, const std::string& MEM)
{
	//Case-13: SREG, []/W[]
	Register::REG16(SREG, Memory::Get16Bit(Memory::PhysicalAddress(MEM)));
	return true;
}

bool ProgramExecutor::MOV_CASE_14(const std::string& REG16, const std::string& SREG)
{
	//Case-14: REG16, SREG
	Register::REG16(REG16, Register::REG16(SREG));
	return true;
}

bool ProgramExecutor::MOV_CASE_15(const std::string& MEM, const std::string& SREG)
{
	//Case-15: []/W[], SREG
	Memory::Set16Bit(Memory::PhysicalAddress(MEM), Register::REG16(SREG));
	return true;
}

bool ProgramExecutor::MOV(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;

	bool OK = false;

	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-1:MOV REG8, immd8
		OK = MOV_CASE_1(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-2:MOV REG16, immd16/immd8
		OK = MOV_CASE_2(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-3:[], immd8
		OK = MOV_CASE_3(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-4:[]/W[], immd16
		OK = MOV_CASE_4(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-5:W[], immd8
		OK = MOV_CASE_5(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-6: REG8, REG8
		OK = MOV_CASE_6(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-7: REG16, REG16
		OK = MOV_CASE_7(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-8: REG8, []
		OK = MOV_CASE_8(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-9: REG16, []/W[]
		OK = MOV_CASE_9(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-10: [], REG8
		OK = MOV_CASE_10(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-11: []/W[], REG16
		OK = MOV_CASE_11(OP1, OP2);
	}
	else if (Utility::IsSegmentRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-12: SREG, REG16
		OK = MOV_CASE_12(OP1, OP2);
	}
	else if (Utility::IsSegmentRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-13: SREG, []/W[]
		OK = MOV_CASE_13(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsSegmentRegister(OP2))
	{
		//Case-14: REG16, SREG
		OK = MOV_CASE_14(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsSegmentRegister(OP2))
	{
		//Case-15: []/W[], SREG
		OK = MOV_CASE_15(OP1, OP2);
	}
	else
	{
		return Error::LOG("Unhandled Case @MOV");
	}
	++CurrInsIndex;
	return OK ? NextInstructionExist() : false;
}