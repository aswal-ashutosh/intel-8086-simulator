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

	static bool ADD_CASE_1(const std::string&, const std::string&);
	static bool ADD_CASE_2(const std::string&, const std::string&);
	static bool ADD_CASE_3(const std::string&, const std::string&);
	static bool ADD_CASE_4(const std::string&, const std::string&);
	static bool ADD_CASE_5(const std::string&, const std::string&);
	static bool ADD_CASE_6(const std::string&, const std::string&);
	static bool ADD_CASE_7(const std::string&, const std::string&);
	static bool ADD_CASE_8(const std::string&, const std::string&);
	static bool ADD_CASE_9(const std::string&, const std::string&);
	static bool ADD_CASE_10(const std::string&, const std::string&);
	static bool ADD_CASE_11(const std::string&, const std::string&);

public:
	static bool MOV(const std::string&, const std::string&);
	static bool ADD(const std::string&, const std::string&);
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

bool Mnemonic::ADD_CASE_1(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-1] REG8, REG8*/
	_16Bit REG1 = Register::REG8(OP1);
	_16Bit REG2 = Register::REG8(OP2);
	REG1 += REG2;
	//[TODO: FLAG CHECKS]
	Register::REG8(OP1, REG1);
	return true;
}

bool Mnemonic::ADD_CASE_2(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-2] REG8, MEM*/
	_16Bit REG = Register::REG8(OP1);
	_16Bit MEM = Memory::Get8Bit(Memory::PhysicalAddress(OP2));
	REG += MEM;
	//[TODO: FLAG CHECKS]
	Register::REG8(OP1, REG);
	return true;
}

bool Mnemonic::ADD_CASE_3(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-3] MEM, REG8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit MEM = Memory::Get8Bit(PAdd);
	_16Bit REG = Register::REG8(OP2);
	MEM += REG;
	//[TODO: FLAG CHECKS]
	Memory::Set8Bit(PAdd, MEM);
	return true;
}

bool Mnemonic::ADD_CASE_4(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-4] REG16, REG16*/
	int REG1 = Register::REG16(OP1);
	int REG2 = Register::REG16(OP2);
	REG1 += REG2;
	//[TODO: FLAG CHECKS]
	Register::REG16(OP1, REG1);
	return true;
}

bool Mnemonic::ADD_CASE_5(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-5] REG16, MEM*/
	int REG = Register::REG16(OP1);
	
	int MEM = Memory::Get16Bit(Memory::PhysicalAddress(OP2));
	REG += MEM;
	//[TODO: FLAG CHECKS]
	Register::REG16(OP1, REG);
	return true;
}

bool Mnemonic::ADD_CASE_6(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-6] MEM, REG16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	int MEM = Memory::Get16Bit(PAdd);
	int REG = Register::REG16(OP2);
	MEM += REG;
	//[TODO: FLAG CHECKS]
	Memory::Set16Bit(PAdd, MEM);
	return true;
}

bool Mnemonic::ADD_CASE_7(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-7] MEM, IMMD8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit MEM = Memory::Get8Bit(PAdd);
	_16Bit IMMD8 = Converter::HexToDec(OP2);
	MEM += IMMD8;
	//[TODO: FLAG CHECKS]
	Memory::Set8Bit(PAdd, MEM);
	return true;
}

bool Mnemonic::ADD_CASE_8(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-8] MEM, IMMD16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	int MEM = Memory::Get16Bit(PAdd);
	int IMMD16 = Converter::HexToDec(OP2);
	MEM += IMMD16;
	//[TODO: FLAG CHECKS]
	Memory::Set16Bit(PAdd, MEM);
	return true;
}

bool Mnemonic::ADD_CASE_9(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-9] REG8, IMMD8*/
	_16Bit REG = Register::REG8(OP1);
	_16Bit IMMD8 = Converter::HexToDec(OP2);
	REG += IMMD8;
	//[TODO: FLAG CHECKS]
	Register::REG8(OP1, REG);
	return true;
}

bool Mnemonic::ADD_CASE_10(const std::string& OP1, const std::string& OP2)
{
	/*CASE-10] REG16, IMMD16*/
	int REG = Register::REG16(OP1);
	int IMMD16 = Converter::HexToDec(OP2);
	REG += IMMD16;
	//[TODO: FLAG CHECKS]
	Register::REG16(OP1, REG);
	return true;
}

bool Mnemonic::ADD_CASE_11(const std::string& OP1, const std::string& OP2)
{
	/*CASE-11] REG16, IMMD8*/
	int REG = Register::REG16(OP1);
	int IMMD8 = Converter::HexToDec(OP2);
	REG += IMMD8;
	//[TODO: FLAG CHECKS]
	Register::REG16(OP1, REG);
	return true;
}

bool Mnemonic::ADD(const std::string& OP1, const std::string& OP2)
{
	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{	/*[CASE-1] REG8, REG8*/
		return ADD_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-2] REG8, MEM*/
		return ADD_CASE_2(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE-3] MEM, REG8*/
		return ADD_CASE_3(OP1, OP2);

	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-4] REG16, REG16*/
		return ADD_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-5] REG16, MEM*/
		return ADD_CASE_5(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-6] MEM, REG16*/
		return ADD_CASE_6(OP1, OP2);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-7] MEM, IMMD8*/
		return ADD_CASE_7(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE-8] MEM, IMMD16*/
		return ADD_CASE_8(OP1, OP2);

	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-9] REG8, IMMD8*/
		return ADD_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*CASE-10] REG16, IMMD16*/
		return ADD_CASE_10(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-11] REG16, IMMD8*/
		return ADD_CASE_11(OP1, OP2);
	}

	return Error::LOG("Execution Failder @ ADD\n");
}