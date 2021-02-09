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
	std::string dis = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(OP1, dis);

	if (onlyDisp)
	{
		int targetLocation = Register::REG16(REGISTER::DS) * 0x10 + Converter::HexToDec(dis);
		Memory::Set(targetLocation, Register::REG8(OP2));
	}
	else
	{

	}
	return true;
}

bool Mnemonic::MOV_CASE_4(const std::string& OP1, const std::string& OP2)
{
	return true;

}

bool Mnemonic::MOV_CASE_5(const std::string& OP1, const std::string& OP2)
{
	return true;

}

bool Mnemonic::MOV_CASE_6(const std::string& OP1, const std::string& OP2)
{
	return true;

}

bool Mnemonic::MOV_CASE_7(const std::string& OP1, const std::string& OP2)
{
	return true;

}

bool Mnemonic::MOV_CASE_8(const std::string& OP1, const std::string& OP2)
{
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

	return Error::LOG("MOV Executon Failed\n");
}