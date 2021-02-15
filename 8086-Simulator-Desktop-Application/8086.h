#pragma once
#include"error_handler.h"
#include"typedef.h"
#include"utility.h"
#include"register.h"
#include"memory.h"
#include<unordered_map>
#include"instruction.h"

class ProgramExecutor
{
	static std::unordered_map<std::string, bool (*)(const Operand&)> CallBacks;
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

	//Will work for ADC also when bool value provided to function is true
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


	//Will work for SBB also when bool value provided to function is true
	static bool SUB_CASE_1(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_2(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_3(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_4(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_5(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_6(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_7(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_8(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_9(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_10(const std::string&, const std::string&, const bool);
	static bool SUB_CASE_11(const std::string&, const std::string&, const bool);


	//Functions to update flag register after executing a instruction
	static void UpdateFlags_ADD_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_ADD_16Bit(const _16Bit, const _16Bit, const uint32_t);
	static void UpdateFlags_ADC_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_ADC_16Bit(const _16Bit, const _16Bit, const uint32_t);
	static void UpdateFlags_SUB_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_SUB_16Bit(const _16Bit, const _16Bit, const uint32_t);
	static void UpdateFlags_SBB_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_SBB_16Bit(const _16Bit, const _16Bit, const uint32_t);

public:
	static void LoadCallBacks();
	static bool Execute(const std::vector<Instruction>&);


	static bool MOV(const Operand&);
	static bool ADD(const Operand&);
	static bool ADC(const Operand&);
	static bool SUB(const Operand&);
	static bool SBB(const Operand&);
};

std::unordered_map<std::string, bool (*)(const Operand&)> ProgramExecutor::CallBacks;

void ProgramExecutor::LoadCallBacks()
{
	CallBacks[MNEMONIC::MOV] = MOV;
	CallBacks[MNEMONIC::ADD] = ADD;
	CallBacks[MNEMONIC::ADC] = ADC;
	CallBacks[MNEMONIC::SUB] = SUB;
	CallBacks[MNEMONIC::SBB] = SBB;
}

bool ProgramExecutor::Execute(const std::vector<Instruction>& Program)
{
	//[TODO:] Remove extra checking at release version
	for (const Instruction& I : Program)
	{
		if (CallBacks.count(I.Mnemonic))
		{
			if (!CallBacks[I.Mnemonic](I.operand))
			{
				return Error::LOG("Execution Faild!\n");
			}
		}
		else
		{
			return Error::LOG(I.Mnemonic + " is not implemented yet! @ Execute\n");
		}
	}

	return true;
}


/*<-------------------------------------------FLAG UPDATE----------------------------------->*/

void ProgramExecutor::UpdateFlags_ADD_8Bit(const Byte OP1, const Byte OP2, const _16Bit Result)
{
	Register::SetFlag(Register::FLAG::CF, Result > 0x00ff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) + (OP2 & 0x0f) > 0x0f); //Auxillary Carry Flag
	Byte Result8Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
	/*
		If 2 Two's Complement numbers are added, and they both have the same sign, then
		overflow occurs if and only if the result has the opposite sign. Overflow nerver occurs
		when adding operands with different signs.
	*/
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

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_ADC_8Bit(const Byte OP1, const Byte OP2, const _16Bit Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Register::SetFlag(Register::FLAG::CF, Result > 0x00ff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) + (OP2 & 0x0f) > 0x0f); //Auxillary Carry Flag
	Byte Result8Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
	_16Bit MidWAyResult = _16Bit(OP2) + _16Bit(oldCF);
	bool MidWayOF = false;
	if ((OP2 & (1 << 7)) ^ (Byte(oldCF) & (1 << 7)))
	{
		MidWayOF = false;
	}
	else
	{
		MidWayOF = (MidWAyResult & (1 << 7)) ^ (OP2 & (1 << 7));
	}

	MidWAyResult = Byte(MidWAyResult); //Truncating Extra Bits

	_16Bit ResFinal = OP1 + MidWAyResult;

	if ((OP1 & (1 << 7)) ^ (MidWAyResult & (1 << 7)))
	{
		//Different Sign
		Register::SetFlag(Register::FLAG::OF, MidWayOF);
	}
	else
	{
		//Same Sign
		Register::SetFlag(Register::FLAG::OF, MidWayOF | ((ResFinal & (1 << 7)) ^ (OP1 & (1 << 7))));
	}

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_ADD_16Bit(const _16Bit OP1, const _16Bit OP2, const uint32_t Result)
{
	Register::SetFlag(Register::FLAG::CF, Result > 0xffff); //Carry Flag
	_16Bit Result16Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
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

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_ADC_16Bit(const _16Bit OP1, const _16Bit OP2, const uint32_t Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Register::SetFlag(Register::FLAG::CF, Result > 0xffff); //Carry Flag
	_16Bit Result16Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
	uint32_t MidWayResult = uint32_t(OP2) + uint32_t(oldCF);
	bool WidWayOF = false;

	if ((OP2 & (1 << 15)) ^ (_16Bit(oldCF) & (1 << 15)))
	{
		WidWayOF = false;
	}
	else
	{
		WidWayOF = (MidWayResult & (1 << 15)) ^ (OP2 & (1 << 15));
	}

	MidWayResult = _16Bit(MidWayResult); //Truncating Extra Bits

	uint32_t ResFinal = OP1 + MidWayResult;

	if ((OP1 & (1 << 15)) ^ (MidWayResult & (1 << 15)))
	{
		//Different Sign
		Register::SetFlag(Register::FLAG::OF, WidWayOF);
	}
	else
	{
		//Same Sign
		Register::SetFlag(Register::FLAG::OF, WidWayOF | ((ResFinal & (1 << 15)) ^ (OP1 & (1 << 15))));
	}

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_SUB_8Bit(const Byte OP1, const Byte OP2, const _16Bit Result)
{
	Byte _2SC = -OP2;
	Register::SetFlag(Register::FLAG::CF, Result > 0x00ff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) + (_2SC & 0x0f) > 0x0f); //Auxillary Carry Flag
	Byte Result8Bit = Result; //Truncating Extra Bits

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

void ProgramExecutor::UpdateFlags_SUB_16Bit(const _16Bit OP1, const _16Bit OP2, const uint32_t Result)
{
	_16Bit _2SC = -OP2;
	Register::SetFlag(Register::FLAG::CF, Result > 0xffff); //Carry Flag
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

	/*[TODO][DF]*/
}


void ProgramExecutor::UpdateFlags_SBB_8Bit(const Byte OP1, const Byte OP2, const _16Bit Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Byte _2SC = -OP2;
	Byte _2SC_CF = oldCF ? 0xff : 0x00;
	Register::SetFlag(Register::FLAG::CF, Result > 0x00ff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) + (OP2 & 0x0f) > 0x0f); //Auxillary Carry Flag
	Byte Result8Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
	_16Bit MidWAyResult = _16Bit(_2SC) + _16Bit(_2SC_CF);
	bool MidWayOF = false;
	if ((_2SC & (1 << 7)) ^ (_2SC_CF & (1 << 7)))
	{
		MidWayOF = false;
	}
	else
	{
		MidWayOF = (MidWAyResult & (1 << 7)) ^ (_2SC & (1 << 7));
	}

	MidWAyResult = Byte(MidWAyResult); //Truncating Extra Bits

	_16Bit ResFinal = OP1 + MidWAyResult;

	if ((OP1 & (1 << 7)) ^ (MidWAyResult & (1 << 7)))
	{
		//Different Sign
		Register::SetFlag(Register::FLAG::OF, MidWayOF);
	}
	else
	{
		//Same Sign
		Register::SetFlag(Register::FLAG::OF, MidWayOF | ((ResFinal & (1 << 7)) ^ (OP1 & (1 << 7))));
	}

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00);

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_SBB_16Bit(const _16Bit OP1, const _16Bit OP2, const uint32_t Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	_16Bit _2SC = -OP2;
	_16Bit _2SC_CF = oldCF ? 0xffff : 0x0000;
	Register::SetFlag(Register::FLAG::CF, Result > 0xffff); //Carry Flag
	_16Bit Result16Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
	uint32_t MidWayResult = uint32_t(_2SC) + uint32_t(_2SC_CF);
	bool WidWayOF = false;

	if ((_2SC & (1 << 15)) ^ (_2SC_CF & (1 << 15)))
	{
		WidWayOF = false;
	}
	else
	{
		WidWayOF = (MidWayResult & (1 << 15)) ^ (_2SC & (1 << 15));
	}

	MidWayResult = _16Bit(MidWayResult); //Truncating Extra Bits

	uint32_t ResFinal = OP1 + MidWayResult;

	if ((OP1 & (1 << 15)) ^ (MidWayResult & (1 << 15)))
	{
		//Different Sign
		Register::SetFlag(Register::FLAG::OF, WidWayOF);
	}
	else
	{
		//Same Sign
		Register::SetFlag(Register::FLAG::OF, WidWayOF | ((ResFinal & (1 << 15)) ^ (OP1 & (1 << 15))));
	}

	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(Register::FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000);

	/*[TODO][DF]*/
}

//[TODO] Updating IP

/*<-----------------------------------------MOV------------------------------------------>*/

bool ProgramExecutor::MOV_CASE_1(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:1] MOV REG8, REG8*/
	Register::REG8(OP1, Register::REG8(OP2));
	return true;
}

bool ProgramExecutor::MOV_CASE_2(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:2] MOV REG16, REG16*/
	Register::REG16(OP1, Register::REG16(OP2));
	return true;
}

bool ProgramExecutor::MOV_CASE_3(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:3] MOV [MEM], REG8*/
	Memory::Set8Bit(Memory::PhysicalAddress(OP1), Register::REG8(OP2));
	return true;
}

bool ProgramExecutor::MOV_CASE_4(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:4] MOV [MEM], REG16*/
	Memory::Set16Bit(Memory::PhysicalAddress(OP1), Register::REG16(OP2));
	return true;
}

bool ProgramExecutor::MOV_CASE_5(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:5] MOV [MEM], IMMD8*/
	Memory::Set8Bit(Memory::PhysicalAddress(OP1), Converter::HexToDec(OP2));
	return true;
}

bool ProgramExecutor::MOV_CASE_6(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:6] MOV [MEM], IMMD16*/
	Memory::Set16Bit(Memory::PhysicalAddress(OP1), Converter::HexToDec(OP2));
	return true;
}

bool ProgramExecutor::MOV_CASE_7(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:7] MOV REG8, [MEM]*/
	Register::REG8(OP1, Memory::Get8Bit(Memory::PhysicalAddress(OP2)));
	return true;
}

bool ProgramExecutor::MOV_CASE_8(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:8] MOV REG16, [MEM]*/
	Register::REG16(OP1, Memory::Get16Bit(Memory::PhysicalAddress(OP2)));
	return true;
}

bool ProgramExecutor::MOV_CASE_9(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:9] MOV REG8, IMMD8*/
	Register::REG8(OP1, Converter::HexToDec(OP2));
	return true;
}

bool ProgramExecutor::MOV_CASE_10(const std::string& OP1, const std::string& OP2)
{
	/*[CASE:10] MOV REG16, IMMD16*/
	Register::REG16(OP1, Converter::HexToDec(OP2));
	return true;
}

bool ProgramExecutor::MOV(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;
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

bool ProgramExecutor::ADD_CASE_1(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-1] REG8, REG8*/
	Byte X = Register::REG8(OP1);
	Byte Y = Register::REG8(OP2);
	_16Bit REG1 = X;
	_16Bit REG2 = Y;
	REG1 += REG2 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(OP1, REG1);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::ADD_CASE_2(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-2] REG8, MEM*/
	Byte X = Register::REG8(OP1);
	Byte Y = Memory::Get8Bit(Memory::PhysicalAddress(OP2));
	_16Bit REG = X;
	_16Bit MEM = Y;
	REG += MEM + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::ADD_CASE_3(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-3] MEM, REG8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Register::REG8(OP2);
	_16Bit MEM = X;
	_16Bit REG = Y;
	MEM += REG + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set8Bit(PAdd, MEM);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::ADD_CASE_4(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-4] REG16, REG16*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Register::REG16(OP2);
	uint32_t REG1 = X;
	uint32_t REG2 = Y;
	REG1 += REG2 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(OP1, REG1);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::ADD_CASE_5(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-5] REG16, MEM*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Memory::Get16Bit(Memory::PhysicalAddress(OP2));
	uint32_t REG = X;
	uint32_t MEM = Y;
	REG += MEM + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::ADD_CASE_6(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-6] MEM, REG16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Register::REG16(OP2);
	uint32_t MEM = X;
	uint32_t REG = Y;
	MEM += REG + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(PAdd, MEM);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::ADD_CASE_7(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-7] MEM, IMMD8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Converter::HexToDec(OP2);
	_16Bit MEM = X;
	_16Bit IMMD8 = Y;
	MEM += IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set8Bit(PAdd, MEM);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::ADD_CASE_8(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-8] MEM, IMMD16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Converter::HexToDec(OP2);
	uint32_t MEM = X;
	uint32_t IMMD16 = Y;
	MEM += IMMD16 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(PAdd, MEM);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::ADD_CASE_9(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*[CASE-9] REG8, IMMD8*/
	Byte X = Register::REG8(OP1);
	Byte Y = Converter::HexToDec(OP2);
	_16Bit REG = X;
	_16Bit IMMD8 = Y;
	REG += IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG8(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::ADD_CASE_10(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*CASE-10] REG16, IMMD16*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Converter::HexToDec(OP2);
	uint32_t REG = X;
	uint32_t IMMD16 = Y;
	REG += IMMD16 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::ADD_CASE_11(const std::string& OP1, const std::string& OP2, const bool ADC = false)
{
	/*CASE-11] REG16, IMMD8*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Converter::HexToDec(OP2);
	uint32_t REG = X;
	uint32_t IMMD8 = Y;
	REG += IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(OP1, REG);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
	//This 16 Bit operation will affect the aux flag
	Register::SetFlag(Register::FLAG::AF, (X & 0x000f) + (Y & 0x000f) > 0x000f);//Explicitly Checking aur Auxillary Carry
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

bool ProgramExecutor::ADD(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;
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

bool ProgramExecutor::ADC(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;
	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{	/*[CASE-1] REG8, REG8*/
		return ADD_CASE_1(OP1, OP2, true);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-2] REG8, MEM*/
		return ADD_CASE_2(OP1, OP2, true);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE-3] MEM, REG8*/
		return ADD_CASE_3(OP1, OP2, true);

	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-4] REG16, REG16*/
		return ADD_CASE_4(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-5] REG16, MEM*/
		return ADD_CASE_5(OP1, OP2, true);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-6] MEM, REG16*/
		return ADD_CASE_6(OP1, OP2, true);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-7] MEM, IMMD8*/
		return ADD_CASE_7(OP1, OP2, true);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE-8] MEM, IMMD16*/
		return ADD_CASE_8(OP1, OP2, true);

	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-9] REG8, IMMD8*/
		return ADD_CASE_9(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*CASE-10] REG16, IMMD16*/
		return ADD_CASE_10(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-11] REG16, IMMD8*/
		return ADD_CASE_11(OP1, OP2, true);
	}

	return Error::LOG("Execution Failder @ ADC\n");
}


/*-----------------------------------------SUB--------------------------------------------------------------*/
bool ProgramExecutor::SUB_CASE_1(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-1] REG8, REG8*/
	Byte X = Register::REG8(OP1);
	Byte Y = Register::REG8(OP2);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Register::REG8(OP1, Result);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::SUB_CASE_2(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-2] REG8, MEM*/
	Byte X = Register::REG8(OP1);
	Byte Y = Memory::Get8Bit(Memory::PhysicalAddress(OP2));
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Register::REG8(OP1, Result);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::SUB_CASE_3(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-3] MEM, REG8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Register::REG8(OP2);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Memory::Set8Bit(PAdd, Result);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::SUB_CASE_4(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-4] REG16, REG16*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Register::REG16(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(OP1, Result);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::SUB_CASE_5(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-5] REG16, MEM*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Memory::Get16Bit(Memory::PhysicalAddress(OP2));
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(OP1, Result);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::SUB_CASE_6(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-6] MEM, REG16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Register::REG16(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Memory::Set16Bit(PAdd, Result);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::SUB_CASE_7(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-7] MEM, IMMD8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Converter::HexToDec(OP2);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Memory::Set8Bit(PAdd, Result);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::SUB_CASE_8(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-8] MEM, IMMD16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Converter::HexToDec(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Memory::Set16Bit(PAdd, Result);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::SUB_CASE_9(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*[CASE-9] REG8, IMMD8*/
	Byte X = Register::REG8(OP1);
	Byte Y = Converter::HexToDec(OP2);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xff; //2s complement of 1
	}
	Register::REG8(OP1, Result);//Extra Bits will automatically get truncated as we are assigning 16Bit to 8Bit
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

bool ProgramExecutor::SUB_CASE_10(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*CASE-10] REG16, IMMD16*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Converter::HexToDec(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(OP1, Result);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
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

bool ProgramExecutor::SUB_CASE_11(const std::string& OP1, const std::string& OP2, const bool SBB = false)
{
	/*CASE-11] REG16, IMMD8*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Converter::HexToDec(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(OP1, Result);//Extra Bits will automatically get truncated as we are assigning 32Bit to 16Bit
	//This 16 Bit operation will affect the aux flag
	Register::SetFlag(Register::FLAG::AF, (X & 0x000f) + (_2SC & 0x000f) > 0x000f);//Explicitly Checking aur Auxillary Carry
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
	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{	/*[CASE-1] REG8, REG8*/
		return SUB_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-2] REG8, MEM*/
		return SUB_CASE_2(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE-3] MEM, REG8*/
		return SUB_CASE_3(OP1, OP2);

	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-4] REG16, REG16*/
		return SUB_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-5] REG16, MEM*/
		return SUB_CASE_5(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-6] MEM, REG16*/
		return SUB_CASE_6(OP1, OP2);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-7] MEM, IMMD8*/
		return SUB_CASE_7(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE-8] MEM, IMMD16*/
		return	SUB_CASE_8(OP1, OP2);

	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-9] REG8, IMMD8*/
		return SUB_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*CASE-10] REG16, IMMD16*/
		return SUB_CASE_10(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-11] REG16, IMMD8*/
		return SUB_CASE_11(OP1, OP2);
	}

	return Error::LOG("Execution Failder @ ADD\n");
}

bool ProgramExecutor::SBB(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;
	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{	/*[CASE-1] REG8, REG8*/
		return SUB_CASE_1(OP1, OP2, true);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-2] REG8, MEM*/
		return SUB_CASE_2(OP1, OP2, true);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE-3] MEM, REG8*/
		return SUB_CASE_3(OP1, OP2, true);

	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-4] REG16, REG16*/
		return SUB_CASE_4(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-5] REG16, MEM*/
		return SUB_CASE_5(OP1, OP2, true);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-6] MEM, REG16*/
		return SUB_CASE_6(OP1, OP2, true);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-7] MEM, IMMD8*/
		return SUB_CASE_7(OP1, OP2, true);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE-8] MEM, IMMD16*/
		return	SUB_CASE_8(OP1, OP2, true);

	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-9] REG8, IMMD8*/
		return SUB_CASE_9(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*CASE-10] REG16, IMMD16*/
		return SUB_CASE_10(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-11] REG16, IMMD8*/
		return SUB_CASE_11(OP1, OP2, true);
	}

	return Error::LOG("Execution Failder @ ADD\n");
}