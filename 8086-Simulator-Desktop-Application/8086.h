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
public:
	static bool MOV(const std::string&, const std::string&);
};

//[TODO] Updating IP

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
	Memory::Set(Memory::PhysicalAddress(OP1), Register::REG8(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_4(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:4] MOV [MEM], REG16*/
	_16Bit R16Data = Register::REG16(OP2);
	Byte Lbyte = R16Data & 0x00ff;
	Byte Hbyte = (R16Data & 0xff00) >> 8;
	int pAddressL = Memory::PhysicalAddress(OP1);
	int pAddressH = pAddressL + 1 > 0xfffff ? 0x00000 : pAddressL + 1; //Address should be in range[00000H-FFFFFH]
	Memory::Set(pAddressL, Lbyte);
	Memory::Set(pAddressH, Hbyte);
	return true;
}

bool Mnemonic::MOV_CASE_5(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:5] MOV [MEM], IMMD8*/
	Memory::Set(Memory::PhysicalAddress(OP1), Converter::HexToDec(OP2));
	return true;
}

bool Mnemonic::MOV_CASE_6(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:6] MOV [MEM], IMMD16*/
	_16Bit I16Data = Converter::HexToDec(OP2);
	Byte Lbyte = I16Data & 0x00ff;
	Byte Hbyte = (I16Data & 0xff00) >> 8;
	int pAddressL = Memory::PhysicalAddress(OP1);
	int pAddressH = pAddressL + 1 > 0xfffff ? 0x00000 : pAddressL + 1; //Address should be in range[00000H-FFFFFH]
	Memory::Set(pAddressL, Lbyte);
	Memory::Set(pAddressH, Hbyte);
	return true;
}

bool Mnemonic::MOV_CASE_7(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:7] MOV REG8, [MEM]*/
	Register::REG8(OP1, Memory::Get(Memory::PhysicalAddress(OP2)));
	return true;
}

bool Mnemonic::MOV_CASE_8(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:8] MOV REG16, [MEM]*/
	int pAddressL = Memory::PhysicalAddress(OP2);
	int pAddressH = pAddressL + 1 > 0xfffff ? 0x00000 : pAddressL + 1; //Address should be in range[00000H-FFFFFH]
	_16Bit Data = Memory::Get(pAddressH);
	Data <<= 8;
	Data |= Memory::Get(pAddressL);
	Register::REG16(OP1, Data);
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
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
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
	return Error::LOG("MOV Executon Failed\n");
}