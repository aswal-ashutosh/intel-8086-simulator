#pragma once
#include"error_handler.h"
#include"typedef.h"
#include"utility.h"
#include"register.h"
#include"memory.h"

class Mnemonic
{
	static bool MOV_CASE_1(const std::string&, const std::string&);
	static bool MOV_CASE_2(const std::string&, const std::string&);
	static bool MOV_CASE_3(const std::string&, const std::string&);
	static bool MOV_CASE_4(const std::string&, const std::string&);
	static bool MOV_CASE_5(const std::string&, const std::string&);
	static bool MOV_CASE_6(const std::string&, const std::string&);
	static bool MOV_CASE_7(const std::string&, const std::string&);
	static bool MOV_CASE_8(const std::string&, const std::string&);
	static bool MOV_CASE_9(const std::string&, const std::string&);
	static bool MOV_CASE_10(const std::string&, const std::string&);

	static bool ADD_CASE_1(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_2(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_3(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_4(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_5(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_6(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_7(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_8(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_9(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_10(const std::string&, const std::string&, const bool);
	static bool ADD_CASE_11(const std::string&, const std::string&, const bool);

public:
	static bool MOV(const std::string&, const std::string&);
	static bool ADD(const std::string&, const std::string&, const bool);
	static bool ADC(const std::string&, const std::string&);
};

//[TODO] Updating IP

/*<-----------------------------------------MOV------------------------------------------>*/

bool Mnemonic::MOV_CASE_1(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:1] MOV REG8, REG8*/
	Register::REG8(OP1, Register::REG8(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_2(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:2] MOV REG16, REG16*/
	Register::REG16(OP1, Register::REG16(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_3(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:3] MOV [MEM], REG8*/
	Memory::Set8Bit(Memory::PhysicalAddress(OP1), Register::REG8(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_4(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:4] MOV [MEM], REG16*/
	Memory::Set16Bit(Memory::PhysicalAddress(OP1), Register::REG16(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_5(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:5] MOV [MEM], IMMD8*/
	Memory::Set8Bit(Memory::PhysicalAddress(OP1), Converter::HexToDec(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_6(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:6] MOV [MEM], IMMD16*/
	Memory::Set16Bit(Memory::PhysicalAddress(OP1), Converter::HexToDec(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_7(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:7] MOV REG8, [MEM]*/
	Register::REG8(OP1, Memory::Get8Bit(Memory::PhysicalAddress(OP2)));
	return true;
}

bool Mnemonic::MOV_CASE_8(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:8] MOV REG16, [MEM]*/
	Register::REG16(OP1, Memory::Get16Bit(Memory::PhysicalAddress(OP2)));
	return true;
}

bool Mnemonic::MOV_CASE_9(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:9] MOV REG8, IMMD8*/
	Register::REG8(OP1, Converter::HexToDec(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_10(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:10] MOV REG16, IMMD16*/
	Register::REG16(OP1, Converter::HexToDec(OP2));
	return true;
}

bool Mnemonic::MOV(const std::string& OP1, const std::string& OP2)
{
	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE:1] MOV REG8, REG8*/
		return MOV_CASE_1(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE:2] MOV REG16, REG16*/
		return MOV_CASE_2(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE:3] MOV [MEM], REG8*/
		return MOV_CASE_3(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE:4] MOV [MEM], REG16*/
		return MOV_CASE_4(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE:5] MOV [MEM], IMMD8*/
		return MOV_CASE_5(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE:6] MOV [MEM], IMMD16*/
		return MOV_CASE_6(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE:7] MOV REG8, [MEM]*/
		return MOV_CASE_7(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE:8] MOV REG16, [MEM]*/
		return MOV_CASE_8(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE:9] MOV REG8, IMMD8*/
		return MOV_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		/*[CASE:10] MOV REG16, IMMD16*/
		return MOV_CASE_10(OP1, OP2);
	}
	else if (Utility::IsSegmentRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE:11] MOV SREG16, [MEM]*/
		return MOV_CASE_8(OP1, OP2); //Equivalent to case-8
	}
	else if (Utility::IsMemory(OP1) && Utility::IsSegmentRegister(OP2))
	{
		/*[CASE:12] MOV [MEM], SREG16*/
		return MOV_CASE_4(OP1, OP2); //Equivalent to case-4
	}
	else if (Utility::IsSegmentRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE:13] MOV SREG16, REG16*/
		return MOV_CASE_2(OP1, OP2);//Equivalent to case-2
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsSegmentRegister(OP2))
	{
		/*[CASE:13] MOV REG16, SREG16*/
		return MOV_CASE_2(OP1, OP2);//Equivalent to case-2
	}
	return Error::LOG("Executon Failed @ MOV\n");
}

/*<-----------------------------------------ADD------------------------------------------>*/

bool Mnemonic::ADD_CASE_1(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-1] REG8, REG8*/
	Byte X = Register::REG8(OP1);
	Byte Y = Register::REG8(OP2);
	_16Bit REG1 = X;
	_16Bit REG2 = Y;
	REG1 += REG2 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(OP1, REG1);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
	Register::UpdateFlags8Bit(X, Y, REG1, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_2(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-2] REG8, MEM*/
	Byte X = Register::REG8(OP1);
	Byte Y = Memory::Get8Bit(Memory::PhysicalAddress(OP2));
	_16Bit REG = X;
	_16Bit MEM = Y;
	REG += MEM + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
	Register::UpdateFlags8Bit(X, Y, REG, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_3(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-3] MEM, REG8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Register::REG8(OP2);
	_16Bit MEM = X;
	_16Bit REG = Y;
	MEM += REG + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set8Bit(PAdd, MEM);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
	Register::UpdateFlags8Bit(X, Y, MEM, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_4(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-4] REG16, REG16*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Register::REG16(OP2);
	int REG1 = X;
	int REG2 = Y;
	REG1 += REG2 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(OP1, REG1);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
	Register::UpdateFlags16Bit(X, Y, REG1, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_5(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-5] REG16, MEM*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Memory::Get16Bit(Memory::PhysicalAddress(OP2));
	int REG = X;
	int MEM = Y;
	REG += MEM + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
	Register::UpdateFlags16Bit(X, Y, REG, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_6(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-6] MEM, REG16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Register::REG16(OP2);
	int MEM = X;
	int REG = Y;
	MEM += REG + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(PAdd, MEM);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
	Register::UpdateFlags16Bit(X, Y, MEM, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_7(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-7] MEM, IMMD8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Converter::HexToDec(OP2);
	_16Bit MEM = X;
	_16Bit IMMD8 = Y;
	MEM += IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set8Bit(PAdd, MEM);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
	Register::UpdateFlags8Bit(X, Y, MEM, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_8(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-8] MEM, IMMD16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Converter::HexToDec(OP2);
	int MEM = X;
	int IMMD16 = Y;
	MEM += IMMD16 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(PAdd, MEM);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
	Register::UpdateFlags16Bit(X, Y, MEM, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_9(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*[CASE-9] REG8, IMMD8*/
	Byte X = Register::REG8(OP1);
	Byte Y = Converter::HexToDec(OP2);
	_16Bit REG = X;
	_16Bit IMMD8 = Y;
	REG += IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
	Register::UpdateFlags8Bit(X, Y, REG, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_10(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*CASE-10] REG16, IMMD16*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Converter::HexToDec(OP2);
	int REG = X;
	int IMMD16 = Y;
	REG += IMMD16 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
	Register::UpdateFlags16Bit(X, Y, REG, ADC);
	return true;
}

bool Mnemonic::ADD_CASE_11(const std::string& OP1, const std::string& OP2, const bool ADC)
{
	/*CASE-11] REG16, IMMD8*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Converter::HexToDec(OP2);
	int REG = X;
	int IMMD8 = Y;
	REG += IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
	//This 16 Bit operation will affect the aux flag
	Register::SetFlag(Register::FLAG::AF, (X & 0x000f) + (Y & 0x000f) > 0x000f);//Explicitly Checking aur Auxillary Carry
	Register::UpdateFlags16Bit(X, Y, REG, ADC);
	return true;
}

bool Mnemonic::ADD(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{	/*[CASE-1] REG8, REG8*/
		return ADD_CASE_1(OP1, OP2, ADC);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-2] REG8, MEM*/
		return ADD_CASE_2(OP1, OP2, ADC);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE-3] MEM, REG8*/
		return ADD_CASE_3(OP1, OP2, ADC);

	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-4] REG16, REG16*/
		return ADD_CASE_4(OP1, OP2, ADC);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-5] REG16, MEM*/
		return ADD_CASE_5(OP1, OP2, ADC);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-6] MEM, REG16*/
		return ADD_CASE_6(OP1, OP2, ADC);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-7] MEM, IMMD8*/
		return ADD_CASE_7(OP1, OP2, ADC);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE-8] MEM, IMMD16*/
		return ADD_CASE_8(OP1, OP2, ADC);

	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-9] REG8, IMMD8*/
		return ADD_CASE_9(OP1, OP2, ADC);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*CASE-10] REG16, IMMD16*/
		return ADD_CASE_10(OP1, OP2, ADC);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-11] REG16, IMMD8*/
		return ADD_CASE_11(OP1, OP2, ADC);
	}

	return Error::LOG("Execution Failder @ ADD\n");
}

bool Mnemonic::ADC(const std::string& OP1, const std::string& OP2)
{
	return ADD(OP1, OP2, true);
}