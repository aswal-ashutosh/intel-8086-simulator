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


	enum class LOGIC{AND, OR, XOR};
	//Will Perform Logical Operations i.e AND, OR, XOR
	static bool LOGIC_CASE_1(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_2(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_3(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_4(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_5(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_6(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_7(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_8(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_9(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_10(const std::string&, const std::string&, const LOGIC&);
	static bool LOGIC_CASE_11(const std::string&, const std::string&, const LOGIC&);
	static bool LOGICAL_OPERATION(const Operand&, const LOGIC&);


	static bool MUL_CASE_1(const std::string&);
	static bool MUL_CASE_2(const std::string&);
	static bool MUL_CASE_3(const std::string&);

	static bool IMUL_CASE_1(const std::string&);
	static bool IMUL_CASE_2(const std::string&);
	static bool IMUL_CASE_3(const std::string&);

	static bool DIV_CASE_1(const std::string&);
	static bool DIV_CASE_2(const std::string&);
	static bool DIV_CASE_3(const std::string&);

	static bool IDIV_CASE_1(const std::string&);
	static bool IDIV_CASE_2(const std::string&);
	static bool IDIV_CASE_3(const std::string&);

	static bool CMP_CASE_1(const std::string&, const std::string&);
	static bool CMP_CASE_2(const std::string&, const std::string&);
	static bool CMP_CASE_3(const std::string&, const std::string&);
	static bool CMP_CASE_4(const std::string&, const std::string&);
	static bool CMP_CASE_5(const std::string&, const std::string&);
	static bool CMP_CASE_6(const std::string&, const std::string&);
	static bool CMP_CASE_7(const std::string&, const std::string&);
	static bool CMP_CASE_8(const std::string&, const std::string&);
	static bool CMP_CASE_9(const std::string&, const std::string&);
	static bool CMP_CASE_10(const std::string&, const std::string&);
	static bool CMP_CASE_11(const std::string&, const std::string&);

	//Functions to update flag register after executing a instruction
	static void UpdateFlags_ADD_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_ADD_16Bit(const _16Bit, const _16Bit, const uint32_t);
	static void UpdateFlags_ADC_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_ADC_16Bit(const _16Bit, const _16Bit, const uint32_t);
	static void UpdateFlags_SUB_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_SUB_16Bit(const _16Bit, const _16Bit, const uint32_t);
	static void UpdateFlags_SBB_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_SBB_16Bit(const _16Bit, const _16Bit, const uint32_t);

	static void UpdateFlags_CMP_8Bit(const Byte, const Byte, const _16Bit);
	static void UpdateFlags_CMP_16Bit(const _16Bit, const _16Bit, const uint32_t);


	//Will update flags for AND, XOR & OR
	static void UpdateFlags_LOGIC_8Bit(const Byte);
	static void UpdateFlags_LOGIC_16Bit(const _16Bit);

	//Will also Update the flags for IMUL
	static void UpdateFlags_MUL_8Bit();
	static void UpdateFlags_MUL_16Bit();

public:
	static void LoadCallBacks();
	static bool Execute(const std::vector<Instruction>&);


	static bool MOV(const Operand&);
	static bool ADD(const Operand&);
	static bool ADC(const Operand&);
	static bool SUB(const Operand&);
	static bool SBB(const Operand&);
	static bool MUL(const Operand&);
	static bool IMUL(const Operand&);
	static bool DIV(const Operand&);
	static bool IDIV(const Operand&);
	static bool AND(const Operand&);
	static bool OR(const Operand&);
	static bool XOR(const Operand&);
	static bool CMP(const Operand&);
};

std::unordered_map<std::string, bool (*)(const Operand&)> ProgramExecutor::CallBacks;

void ProgramExecutor::LoadCallBacks()
{
	CallBacks[MNEMONIC::MOV] = MOV;
	CallBacks[MNEMONIC::ADD] = ADD;
	CallBacks[MNEMONIC::ADC] = ADC;
	CallBacks[MNEMONIC::SUB] = SUB;
	CallBacks[MNEMONIC::SBB] = SBB;
	CallBacks[MNEMONIC::MUL] = MUL;
	CallBacks[MNEMONIC::IMUL] = IMUL;
	CallBacks[MNEMONIC::DIV] = DIV;
	CallBacks[MNEMONIC::IDIV] = IDIV;
	CallBacks[MNEMONIC::AND] = AND;
	CallBacks[MNEMONIC::OR] = OR;
	CallBacks[MNEMONIC::XOR] = XOR;
	CallBacks[MNEMONIC::CMP] = CMP;
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

	Register::SetFlag(Register::FLAG::ZF, Result8Bit == 0x00); //Zero Flag

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
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x000f) + (OP2 & 0x000f) > 0x000f); //Auxillary Carry Flag
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

	Register::SetFlag(Register::FLAG::ZF, Result16Bit == 0x0000); //Zero Flag

	/*[TODO][DF]*/
}

void ProgramExecutor::UpdateFlags_ADC_16Bit(const _16Bit OP1, const _16Bit OP2, const uint32_t Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Register::SetFlag(Register::FLAG::CF, Result > 0xffff); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x000f) + (OP2 & 0x000f) > 0x000f); //Auxillary Carry Flag
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
	Register::SetFlag(Register::FLAG::CF, OP1 < OP2); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) < (OP2 & 0x0f)); //Auxillary Carry Flag
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

void ProgramExecutor::UpdateFlags_SBB_8Bit(const Byte OP1, const Byte OP2, const _16Bit Result)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Byte _2SC = -OP2;
	Byte _2SC_CF = oldCF ? 0xff : 0x00;
	Register::SetFlag(Register::FLAG::CF, OP1 < OP2); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) < (OP2 & 0x0f)); //Auxillary Carry Flag
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
	Register::SetFlag(Register::FLAG::CF, OP1 < OP2); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x000f) < (OP2 & 0x000f)); //Auxillary Carry Flag
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

void ProgramExecutor::UpdateFlags_MUL_8Bit()
{
	//MUL only affects OF and CF based upon the upper half of the result all other flags are undefined
	Byte AH = Register::REG8(REGISTER::AH);
	Register::SetFlag(Register::FLAG::CF, AH != 0x00);
	Register::SetFlag(Register::FLAG::OF, AH != 0x00);
}

void ProgramExecutor::UpdateFlags_MUL_16Bit()
{
	//MUL only affects OF and CF based upon the upper half of the result all other flags are undefined
	_16Bit DX = Register::REG16(REGISTER::DX);
	Register::SetFlag(Register::FLAG::CF, DX != 0x0000);
	Register::SetFlag(Register::FLAG::OF, DX != 0x0000);
}

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

void ProgramExecutor::UpdateFlags_LOGIC_16Bit(const _16Bit Result)
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

void ProgramExecutor::UpdateFlags_CMP_8Bit(const Byte OP1, const Byte OP2, const _16Bit Result)
{
	Byte _2SC = -OP2;
	Register::SetFlag(Register::FLAG::CF, OP1 < OP2); //Carry Flag
	Register::SetFlag(Register::FLAG::AF, (OP1 & 0x0f) < (OP2 & 0x0f)); //Auxillary Carry Flag
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

	return Error::LOG("Execution Failed @ SUB\n");
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

	return Error::LOG("Execution Failed @ SBB\n");
}

/*<---------------------------------------------MUL------------------------------------------>*/

bool ProgramExecutor::MUL_CASE_1(const std::string& OP)
{
	//Memory
	_16Bit multiplicand = Register::REG8(REGISTER::AL);
	_16Bit mulitplier = Memory::Get8Bit(Memory::PhysicalAddress(OP));
	_16Bit Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::MUL_CASE_2(const std::string& OP)
{
	//REG8
	_16Bit multiplicand = Register::REG8(REGISTER::AL);
	_16Bit mulitplier = Register::REG8(OP);
	_16Bit Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::MUL_CASE_3(const std::string& OP)
{
	//REG16
	uint32_t multiplicand = Register::REG16(REGISTER::AX);
	uint32_t mulitplier = Register::REG16(OP);
	uint32_t Result = multiplicand * mulitplier;
	_16Bit UpperHalf = (Result & 0xffff0000) >> 16;
	_16Bit LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_1(const std::string& OP)
{
	//Memory
	short multiplicand = (char)Register::REG8(REGISTER::AL);
	short mulitplier = (char)Memory::Get8Bit(Memory::PhysicalAddress(OP));
	short Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_2(const std::string& OP)
{
	//REG8
	short multiplicand = (char)Register::REG8(REGISTER::AL);
	short mulitplier = (char)Register::REG8(OP);
	short Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_3(const std::string& OP)
{
	//REG16
	int multiplicand = (short)Register::REG16(REGISTER::AX);
	int mulitplier = (short)Register::REG16(OP);
	int Result = multiplicand * mulitplier;
	_16Bit UpperHalf = (Result & 0xffff0000) >> 16;
	_16Bit LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::MUL(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsMemory(OP))
	{
		return MUL_CASE_1(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		return MUL_CASE_2(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		return MUL_CASE_3(OP);
	}

	return Error::LOG("Execution Failed @MUL\n");
}

bool ProgramExecutor::IMUL(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsMemory(OP))
	{
		return IMUL_CASE_1(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		return IMUL_CASE_2(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		return IMUL_CASE_3(OP);
	}

	return Error::LOG("Execution Failed @IMUL\n");
}

/*<------------------------------------DIV----------------------------------->*/

bool ProgramExecutor::DIV_CASE_1(const std::string& OP)
{
	//Memory
	_16Bit divisor = Memory::Get8Bit(Memory::PhysicalAddress(OP));
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	_16Bit dividend = Register::REG16(REGISTER::AX);
	_16Bit quotient = dividend / divisor;
	_16Bit remainder = dividend % divisor;
	if (quotient > 0xff) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, quotient);
	Register::REG8(REGISTER::AH, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV_CASE_2(const std::string& OP)
{
	//REG8
	_16Bit divisor = Register::REG8(OP);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	_16Bit dividend = Register::REG16(REGISTER::AX);
	_16Bit quotient = dividend / divisor;
	_16Bit remainder = dividend % divisor;
	if (quotient > 0xff) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, quotient);
	Register::REG8(REGISTER::AH, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV_CASE_3(const std::string& OP)
{
	//REG16
	uint32_t divisor = Register::REG16(OP);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	uint32_t dividendLowerHalf = Register::REG16(REGISTER::AX);
	uint32_t dividendUpperHalf = Register::REG16(REGISTER::DX);
	uint32_t dividend = (dividendUpperHalf << 16) | dividendLowerHalf;
	uint32_t quotient = dividend / divisor;
	uint32_t remainder = dividend % divisor;
	if (quotient > 0xffff) { return Error::LOG("Division Error. Result can't be fit in AX\n"); }
	Register::REG16(REGISTER::AX, quotient);
	Register::REG16(REGISTER::DX, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_1(const std::string& OP)
{
	//Memory
	short divisor = (char)Memory::Get8Bit(Memory::PhysicalAddress(OP));
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	short dividend = Register::REG16(REGISTER::AX);
	short quotient = dividend / divisor;
	short remainder = dividend % divisor;
	if (quotient > 0x7f || quotient < (char)0x80) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, quotient);
	Register::REG8(REGISTER::AH, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_2(const std::string& OP)
{
	//REG8
	short divisor = (char)Register::REG8(OP);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	short dividend = Register::REG16(REGISTER::AX);
	short quotient = dividend / divisor;
	short remainder = dividend % divisor;
	if (quotient > 0x7f || quotient < (char)0x80) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, quotient);
	Register::REG8(REGISTER::AH, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_3(const std::string& OP)
{
	//REG16
	int divisor = (short)Register::REG16(OP);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	uint32_t dividendLowerHalf = Register::REG16(REGISTER::AX);
	uint32_t dividendUpperHalf = Register::REG16(REGISTER::DX);
	int dividend = (dividendUpperHalf << 16) | dividendLowerHalf;
	int quotient = dividend / divisor;
	int remainder = dividend % divisor;
	if (quotient > 0x7fff || quotient < (short)0x8000) { return Error::LOG("Division Error. Result can't be fit in AX\n"); }
	Register::REG16(REGISTER::AX, quotient);
	Register::REG16(REGISTER::DX, remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsMemory(OP))
	{
		return DIV_CASE_1(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		return DIV_CASE_2(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		return DIV_CASE_3(OP);
	}

	return Error::LOG("Execution Failed @DIV\n");
}

bool ProgramExecutor::IDIV(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsMemory(OP))
	{
		return IDIV_CASE_1(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		return IDIV_CASE_2(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		return IDIV_CASE_3(OP);
	}

	return Error::LOG("Execution Failed @IDIV\n");
}

/*<--------------------------LOGICAL OPERATION---------------------------------------->*/



bool ProgramExecutor::LOGIC_CASE_1(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-1] REG8, REG8*/
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG8(OP1) & Register::REG8(OP2); break;
	case LOGIC::OR: Result = Register::REG8(OP1) | Register::REG8(OP2); break;
	case LOGIC::XOR: Result = Register::REG8(OP1) ^ Register::REG8(OP2); break;
	}
	Register::REG8(OP1, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_2(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-2] REG8, MEM*/
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG8(OP1) & Memory::Get8Bit(Memory::PhysicalAddress(OP2)); break;
	case LOGIC::OR: Result = Register::REG8(OP1) | Memory::Get8Bit(Memory::PhysicalAddress(OP2)); break;
	case LOGIC::XOR: Result = Register::REG8(OP1) ^ Memory::Get8Bit(Memory::PhysicalAddress(OP2)); break;
	}
	Register::REG8(OP1, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_3(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-3] MEM, REG8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get8Bit(PAdd) & Register::REG8(OP2); break;
	case LOGIC::OR: Result = Memory::Get8Bit(PAdd) | Register::REG8(OP2); break;
	case LOGIC::XOR: Result = Memory::Get8Bit(PAdd) ^ Register::REG8(OP2); break;
	}
	Memory::Set8Bit(PAdd, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_4(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-4] REG16, REG16*/
	 _16Bit Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG16(OP1) & Register::REG16(OP2); break;
	case LOGIC::OR: Result = Register::REG16(OP1) | Register::REG16(OP2); break;
	case LOGIC::XOR: Result = Register::REG16(OP1) ^ Register::REG16(OP2); break;
	}
	Register::REG16(OP1, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_5(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-5] REG16, MEM*/
	_16Bit Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG16(OP1) & Memory::Get16Bit(Memory::PhysicalAddress(OP2)); break;
	case LOGIC::OR: Result = Register::REG16(OP1) | Memory::Get16Bit(Memory::PhysicalAddress(OP2)); break;
	case LOGIC::XOR: Result = Register::REG16(OP1) ^ Memory::Get16Bit(Memory::PhysicalAddress(OP2)); break;
	}
	Register::REG16(OP1, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_6(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-6] MEM, REG16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get16Bit(PAdd) & Register::REG16(OP2); break;
	case LOGIC::OR: Result = Memory::Get16Bit(PAdd) | Register::REG16(OP2); break;
	case LOGIC::XOR: Result = Memory::Get16Bit(PAdd) ^ Register::REG16(OP2); break;
	}
	Memory::Set16Bit(PAdd, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_7(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-7] MEM, IMMD8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get8Bit(PAdd) & Converter::HexToDec(OP2); break;
	case LOGIC::OR: Result = Memory::Get8Bit(PAdd) | Converter::HexToDec(OP2); break;
	case LOGIC::XOR: Result = Memory::Get8Bit(PAdd) ^ Converter::HexToDec(OP2); break;
	}
	Memory::Set8Bit(PAdd, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_8(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-8] MEM, IMMD16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Memory::Get16Bit(PAdd) & Converter::HexToDec(OP2); break;
	case LOGIC::OR: Result = Memory::Get16Bit(PAdd) | Converter::HexToDec(OP2); break;
	case LOGIC::XOR: Result = Memory::Get16Bit(PAdd) ^ Converter::HexToDec(OP2); break;
	}
	Memory::Set16Bit(PAdd, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_9(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*[CASE-9] REG8, IMMD8*/
	Byte Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG8(OP1) & Converter::HexToDec(OP2); break;
	case LOGIC::OR: Result = Register::REG8(OP1) | Converter::HexToDec(OP2); break;
	case LOGIC::XOR: Result = Register::REG8(OP1) ^ Converter::HexToDec(OP2); break;
	}
	Register::REG8(OP1, Result);
	UpdateFlags_LOGIC_8Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_10(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*CASE-10] REG16, IMMD16*/
	_16Bit Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG16(OP1) & Converter::HexToDec(OP2); break;
	case LOGIC::OR: Result = Register::REG16(OP1) | Converter::HexToDec(OP2); break;
	case LOGIC::XOR: Result = Register::REG16(OP1) ^ Converter::HexToDec(OP2); break;
	}
	Register::REG16(OP1, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGIC_CASE_11(const std::string& OP1, const std::string& OP2, const LOGIC& OPERATION)
{
	/*CASE-11] REG16, IMMD8*/
	_16Bit Result = 0;
	switch (OPERATION)
	{
	case LOGIC::AND: Result = Register::REG16(OP1) & Converter::HexToDec(OP2); break;
	case LOGIC::OR: Result = Register::REG16(OP1) | Converter::HexToDec(OP2); break;
	case LOGIC::XOR: Result = Register::REG16(OP1) ^ Converter::HexToDec(OP2); break;
	}
	Register::REG16(OP1, Result);
	UpdateFlags_LOGIC_16Bit(Result);
	return true;
}

bool ProgramExecutor::LOGICAL_OPERATION(const Operand& operand, const LOGIC& OPERATION)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;
	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{	/*[CASE-1] REG8, REG8*/
		return LOGIC_CASE_1(OP1, OP2, OPERATION);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-2] REG8, MEM*/
		return LOGIC_CASE_2(OP1, OP2, OPERATION);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE-3] MEM, REG8*/
		return LOGIC_CASE_3(OP1, OP2, OPERATION);

	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-4] REG16, REG16*/
		return LOGIC_CASE_4(OP1, OP2, OPERATION);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-5] REG16, MEM*/
		return LOGIC_CASE_5(OP1, OP2, OPERATION);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-6] MEM, REG16*/
		return LOGIC_CASE_6(OP1, OP2, OPERATION);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-7] MEM, IMMD8*/
		return LOGIC_CASE_7(OP1, OP2, OPERATION);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE-8] MEM, IMMD16*/
		return LOGIC_CASE_8(OP1, OP2, OPERATION);

	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-9] REG8, IMMD8*/
		return LOGIC_CASE_9(OP1, OP2, OPERATION);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*CASE-10] REG16, IMMD16*/
		return LOGIC_CASE_10(OP1, OP2, OPERATION);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-11] REG16, IMMD8*/
		return LOGIC_CASE_11(OP1, OP2, OPERATION);
	}

	return Error::LOG("Failed To Perform Logical Operation\n");
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

/*<---------------------------------------CMP----------------------------------------------->*/

bool ProgramExecutor::CMP_CASE_1(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-1] REG8, REG8*/
	Byte X = Register::REG8(OP1);
	Byte Y = Register::REG8(OP2);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_2(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-2] REG8, MEM*/
	Byte X = Register::REG8(OP1);
	Byte Y = Memory::Get8Bit(Memory::PhysicalAddress(OP2));
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_3(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-3] MEM, REG8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Register::REG8(OP2);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_4(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-4] REG16, REG16*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Register::REG16(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_5(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-5] REG16, MEM*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Memory::Get16Bit(Memory::PhysicalAddress(OP2));
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_6(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-6] MEM, REG16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Register::REG16(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_7(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-7] MEM, IMMD8*/
	int PAdd = Memory::PhysicalAddress(OP1);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Converter::HexToDec(OP2);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_8(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-8] MEM, IMMD16*/
	int PAdd = Memory::PhysicalAddress(OP1);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Converter::HexToDec(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_9(const std::string& OP1, const std::string& OP2)
{
	/*[CASE-9] REG8, IMMD8*/
	Byte X = Register::REG8(OP1);
	Byte Y = Converter::HexToDec(OP2);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_10(const std::string& OP1, const std::string& OP2)
{
	/*CASE-10] REG16, IMMD16*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Converter::HexToDec(OP2);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_11(const std::string& OP1, const std::string& OP2)
{
	/*CASE-11] REG16, IMMD8*/
	_16Bit X = Register::REG16(OP1);
	_16Bit Y = Converter::HexToDec(OP2);
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
	{	/*[CASE-1] REG8, REG8*/
		return CMP_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-2] REG8, MEM*/
		return CMP_CASE_2(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE-3] MEM, REG8*/
		return CMP_CASE_3(OP1, OP2);

	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-4] REG16, REG16*/
		return CMP_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-5] REG16, MEM*/
		return CMP_CASE_5(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-6] MEM, REG16*/
		return CMP_CASE_6(OP1, OP2);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-7] MEM, IMMD8*/
		return CMP_CASE_7(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE-8] MEM, IMMD16*/
		return	CMP_CASE_8(OP1, OP2);

	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-9] REG8, IMMD8*/
		return CMP_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*CASE-10] REG16, IMMD16*/
		return CMP_CASE_10(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-11] REG16, IMMD8*/
		return CMP_CASE_11(OP1, OP2);
	}

	return Error::LOG("Execution Failed @ CMP\n");
}