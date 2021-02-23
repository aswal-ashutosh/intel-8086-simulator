#pragma once
#include"8086.h"


void ProgramExecutor::UpdateFlags_LOGIC_8Bit(const Byte Result)
{
	/*
	The OF and CF flags are cleared.
	The SF, ZF, and PF flags are set according to the result.
	The state of the AF flag is undefined.
	*/
	Register::SetFlag(Register::FLAG::CF, false);
	Register::SetFlag(Register::FLAG::OF, false);

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result == 0x00); //Zero Flag

}

void ProgramExecutor::UpdateFlags_LOGIC_16Bit(const Word Result)
{
	/*
	The OF and CF flags are cleared.
	The SF, ZF, and PF flags are set according to the result.
	The state of the AF flag is undefined.
	*/
	Register::SetFlag(Register::FLAG::CF, false);
	Register::SetFlag(Register::FLAG::OF, false);

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result == 0x0000); //Zero Flag

}

bool ProgramExecutor::LOGIC_CASE_1(const std::string& REG8_D, const std::string& REG8_S, const LOGIC& OPERATION)
{
	//Case-1: REG8, REG8
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG8(REG8_D) & Register::REG8(REG8_S); break;
	case LOGIC::OR: Result = Register::REG8(REG8_D) | Register::REG8(REG8_S); break;
	case LOGIC::XOR: Result = Register::REG8(REG8_D) ^ Register::REG8(REG8_S); break;
	}
	Register::REG8(REG8_D, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_2(const std::string& REG8, const std::string& MEM8, const LOGIC& OPERATION)
{
	//Case-2: REG8, []
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG8(REG8) & Memory::Get8Bit(Memory::PhysicalAddress(MEM8)); break;
	case LOGIC::OR: Result = Register::REG8(REG8) | Memory::Get8Bit(Memory::PhysicalAddress(MEM8)); break;
	case LOGIC::XOR: Result = Register::REG8(REG8) ^ Memory::Get8Bit(Memory::PhysicalAddress(MEM8)); break;
	}
	Register::REG8(REG8, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_3(const std::string& MEM8, const std::string& REG8, const LOGIC& OPERATION)
{
	//Case-3: [], REG8
	int PAdd = Memory::PhysicalAddress(MEM8);
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get8Bit(PAdd) & Register::REG8(REG8); break;
	case LOGIC::OR: Result = Memory::Get8Bit(PAdd) | Register::REG8(REG8); break;
	case LOGIC::XOR: Result = Memory::Get8Bit(PAdd) ^ Register::REG8(REG8); break;
	}
	Memory::Set8Bit(PAdd, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_4(const std::string& REG16_D, const std::string& REG16_S, const LOGIC& OPERATION)
{
	//Case-4: REG16, REG16
	Word Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG16(REG16_D) & Register::REG16(REG16_S); break;
	case LOGIC::OR: Result = Register::REG16(REG16_D) | Register::REG16(REG16_S); break;
	case LOGIC::XOR: Result = Register::REG16(REG16_D) ^ Register::REG16(REG16_S); break;
	}
	Register::REG16(REG16_D, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_5(const std::string& REG16, const std::string& MEM, const LOGIC& OPERATION)
{
	//Case-5: REG16, []/W[]
	Word Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG16(REG16) & Memory::Get16Bit(Memory::PhysicalAddress(MEM)); break;
	case LOGIC::OR: Result = Register::REG16(REG16) | Memory::Get16Bit(Memory::PhysicalAddress(MEM)); break;
	case LOGIC::XOR: Result = Register::REG16(REG16) ^ Memory::Get16Bit(Memory::PhysicalAddress(MEM)); break;
	}
	Register::REG16(REG16, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_6(const std::string& MEM, const std::string& REG16, const LOGIC& OPERATION)
{
	//Case-6: []/W[], REG16
	int PAdd = Memory::PhysicalAddress(MEM);
	Word Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get16Bit(PAdd) & Register::REG16(REG16); break;
	case LOGIC::OR: Result = Memory::Get16Bit(PAdd) | Register::REG16(REG16); break;
	case LOGIC::XOR: Result = Memory::Get16Bit(PAdd) ^ Register::REG16(REG16); break;
	}
	Memory::Set16Bit(PAdd, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_7(const std::string& MEM8, const std::string& IMMD8, const LOGIC& OPERATION)
{
	//Case-7: [], IMMD8
	int PAdd = Memory::PhysicalAddress(MEM8);
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get8Bit(PAdd) & (Byte)Converter::HexToDec(IMMD8); break;
	case LOGIC::OR: Result = Memory::Get8Bit(PAdd) | (Byte)Converter::HexToDec(IMMD8); break;
	case LOGIC::XOR: Result = Memory::Get8Bit(PAdd) ^ (Byte)Converter::HexToDec(IMMD8); break;
	}
	Memory::Set8Bit(PAdd, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_8(const std::string& MEM, const std::string& IMMD16, const LOGIC& OPERATION)
{
	//Case-8: []/W[], IMMD16
	int PAdd = Memory::PhysicalAddress(MEM);
	Word Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get16Bit(PAdd) & Converter::HexToDec(IMMD16); break;
	case LOGIC::OR: Result = Memory::Get16Bit(PAdd) | Converter::HexToDec(IMMD16); break;
	case LOGIC::XOR: Result = Memory::Get16Bit(PAdd) ^ Converter::HexToDec(IMMD16); break;
	}
	Memory::Set16Bit(PAdd, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_9(const std::string& REG8, const std::string& IMMD8, const LOGIC& OPERATION)
{
	//Case-9: REG8, IMMD8
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG8(REG8) & (Byte)Converter::HexToDec(IMMD8); break;
	case LOGIC::OR: Result = Register::REG8(REG8) | (Byte)Converter::HexToDec(IMMD8); break;
	case LOGIC::XOR: Result = Register::REG8(REG8) ^ (Byte)Converter::HexToDec(IMMD8); break;
	}
	Register::REG8(REG8, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_10(const std::string& REG16, const std::string& IMMD16, const LOGIC& OPERATION)
{
	//Case-10: REG16, IMMD16
	Word Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG16(REG16) & Converter::HexToDec(IMMD16); break;
	case LOGIC::OR: Result = Register::REG16(REG16) | Converter::HexToDec(IMMD16); break;
	case LOGIC::XOR: Result = Register::REG16(REG16) ^ Converter::HexToDec(IMMD16); break;
	}
	Register::REG16(REG16, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_11(const std::string& REG16, const std::string& IMMD8, const LOGIC& OPERATION)
{
	//Case-11: REG16, IMMD8
	Word Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG16(REG16) & Converter::HexToDec(IMMD8); break;
	case LOGIC::OR: Result = Register::REG16(REG16) | Converter::HexToDec(IMMD8); break;
	case LOGIC::XOR: Result = Register::REG16(REG16) ^ Converter::HexToDec(IMMD8); break;
	}
	Register::REG16(REG16, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_12(const std::string& MEM16, const std::string& IMMD8, const LOGIC& OPERATION)
{
	//Case-12: W[], IMMD8
	Word Result = 0;
	int PAdd = Memory::PhysicalAddress(MEM16);
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get16Bit(PAdd) & Converter::HexToDec(IMMD8); break;
	case LOGIC::OR: Result = Memory::Get16Bit(PAdd) | Converter::HexToDec(IMMD8); break;
	case LOGIC::XOR: Result = Memory::Get16Bit(PAdd) ^ Converter::HexToDec(IMMD8); break;
	}
	Memory::Set16Bit(PAdd, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGICAL_OPERATION(const Operand& operand, const LOGIC& OPERATION)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1: REG8, REG8
		return LOGIC_CASE_1(OP1, OP2, OPERATION);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		return LOGIC_CASE_2(OP1, OP2, OPERATION);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		return LOGIC_CASE_3(OP1, OP2, OPERATION);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		return LOGIC_CASE_4(OP1, OP2, OPERATION);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		return LOGIC_CASE_5(OP1, OP2, OPERATION);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		return LOGIC_CASE_6(OP1, OP2, OPERATION);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		return LOGIC_CASE_7(OP1, OP2, OPERATION);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		return LOGIC_CASE_8(OP1, OP2, OPERATION);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		return LOGIC_CASE_9(OP1, OP2, OPERATION);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		return LOGIC_CASE_10(OP1, OP2, OPERATION);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		return LOGIC_CASE_11(OP1, OP2, OPERATION);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		return LOGIC_CASE_12(OP1, OP2, OPERATION);
	}

	return Error::LOG("Execution Failed @ Logical Operation\n");
}

bool ProgramExecutor::AND(const Operand& operand)
{
	return LOGICAL_OPERATION(operand, LOGIC::AND) ? true : Error::LOG("Execution Failed @ AND\n");
}

bool ProgramExecutor::OR(const Operand& operand)
{
	return LOGICAL_OPERATION(operand, LOGIC::OR) ? true : Error::LOG("Execution Failed @ OR\n");
}

bool ProgramExecutor::XOR(const Operand& operand)
{
	return LOGICAL_OPERATION(operand, LOGIC::XOR) ? true : Error::LOG("Execution Failed @ XOR\n");
}
