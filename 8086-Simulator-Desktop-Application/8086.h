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
	static bool MOV_CASE_11(const std::string&, const std::string&);
	static bool MOV_CASE_12(const std::string&, const std::string&);
	static bool MOV_CASE_13(const std::string&, const std::string&);
	static bool MOV_CASE_14(const std::string&, const std::string&);
	static bool MOV_CASE_15(const std::string&, const std::string&);

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
	static bool ADD_CASE_12(const std::string&, const std::string&, const bool);



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
	static bool SUB_CASE_12(const std::string&, const std::string&, const bool);


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
	static bool LOGIC_CASE_12(const std::string&, const std::string&, const LOGIC&);
	static bool LOGICAL_OPERATION(const Operand&, const LOGIC&);


	static bool MUL_CASE_1(const std::string&);
	static bool MUL_CASE_2(const std::string&);
	static bool MUL_CASE_3(const std::string&);
	static bool MUL_CASE_4(const std::string&);

	static bool IMUL_CASE_1(const std::string&);
	static bool IMUL_CASE_2(const std::string&);
	static bool IMUL_CASE_3(const std::string&);
	static bool IMUL_CASE_4(const std::string&);

	static bool DIV_CASE_1(const std::string&);
	static bool DIV_CASE_2(const std::string&);
	static bool DIV_CASE_3(const std::string&);
	static bool DIV_CASE_4(const std::string&);

	static bool IDIV_CASE_1(const std::string&);
	static bool IDIV_CASE_2(const std::string&);
	static bool IDIV_CASE_3(const std::string&);
	static bool IDIV_CASE_4(const std::string&);


	static bool NEG_CASE_1(const std::string&);
	static bool NEG_CASE_2(const std::string&);
	static bool NEG_CASE_3(const std::string&);
	static bool NEG_CASE_4(const std::string&);

	static bool NOT_CASE_1(const std::string&);
	static bool NOT_CASE_2(const std::string&);
	static bool NOT_CASE_3(const std::string&);
	static bool NOT_CASE_4(const std::string&);

	static bool DEC_CASE_1(const std::string&);
	static bool DEC_CASE_2(const std::string&);
	static bool DEC_CASE_3(const std::string&);
	static bool DEC_CASE_4(const std::string&);

	static bool INC_CASE_1(const std::string&);
	static bool INC_CASE_2(const std::string&);
	static bool INC_CASE_3(const std::string&);
	static bool INC_CASE_4(const std::string&);

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
	static bool CMP_CASE_12(const std::string&, const std::string&);

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
	
	static void UpdateFlags_NEG_8Bit(const Byte);
	static void UpdateFlags_NEG_16Bit(const _16Bit);

	static void UpdateFlags_DEC_8Bit(const Byte);
	static void UpdateFlags_DEC_16Bit(const _16Bit);
	static void UpdateFlags_INC_8Bit(const Byte);
	static void UpdateFlags_INC_16Bit(const _16Bit);

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
	static bool NEG(const Operand&);
	static bool NOT(const Operand&);
	static bool DEC(const Operand&);
	static bool INC(const Operand&);
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
	CallBacks[MNEMONIC::NEG] = NEG;
	CallBacks[MNEMONIC::NOT] = NOT;
	CallBacks[MNEMONIC::DEC] = DEC;
	CallBacks[MNEMONIC::INC] = INC;
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
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits

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
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits

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
		Register::SetFlag(Register::FLAG::OF, MidWayOF | (bool)((ResFinal & (1 << 7)) ^ (OP1 & (1 << 7))));
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
	_16Bit Result16Bit = (_16Bit)Result; //Truncating Extra Bits

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
	_16Bit Result16Bit = (_16Bit)Result; //Truncating Extra Bits

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
		Register::SetFlag(Register::FLAG::OF, WidWayOF | (bool)((ResFinal & (1 << 15)) ^ (OP1 & (1 << 15))));
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
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits

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
	_16Bit Result16Bit = (_16Bit)Result; //Truncating Extra Bits

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
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits

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
		Register::SetFlag(Register::FLAG::OF, MidWayOF | (bool)((ResFinal & (1 << 7)) ^ (OP1 & (1 << 7))));
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
	_16Bit Result16Bit = (_16Bit)Result; //Truncating Extra Bits

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
		Register::SetFlag(Register::FLAG::OF, WidWayOF | (bool)((ResFinal & (1 << 15)) ^ (OP1 & (1 << 15))));
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
	Byte Result8Bit = (Byte)Result; //Truncating Extra Bits

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

void ProgramExecutor::UpdateFlags_NEG_8Bit(const Byte Data)
{
	Register::SetFlag(Register::FLAG::CF, Data != 0);//Carry Flag
	Register::SetFlag(Register::FLAG::AF, (Data & 0x0f) != 0);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (Byte)0x80);//Overflow Flag
	Byte Result = -Data;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 7)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x00); //Zero Flag
}

void ProgramExecutor::UpdateFlags_NEG_16Bit(const _16Bit Data)
{
	Register::SetFlag(Register::FLAG::CF, Data != 0);//Carry Flag
	Register::SetFlag(Register::FLAG::AF, (Data & 0x000f) != 0);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (_16Bit)0x8000);//Overflow Flag
	_16Bit Result = -Data;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 15)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x0000); //Zero Flag
}

void ProgramExecutor::UpdateFlags_DEC_8Bit(const Byte Data)
{
	Register::SetFlag(Register::FLAG::AF, (Data & 0x0f) < 0x01);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (Byte)0x80);//Overflow Flag
	Byte Result = Data - 1;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 7)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x00); //Zero Flag
}

void ProgramExecutor::UpdateFlags_DEC_16Bit(const _16Bit Data)
{
	Register::SetFlag(Register::FLAG::AF, (Data & 0x000f) < 0x0001);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (_16Bit)0x8000);//Overflow Flag
	_16Bit Result = Data - 1;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 15)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x0000); //Zero Flag
}

void ProgramExecutor::UpdateFlags_INC_8Bit(const Byte Data)
{
	Register::SetFlag(Register::FLAG::AF, (Data & 0x0f) + 0x01 > 0x0f);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (Byte)0x7f);//Overflow Flag
	Byte Result = Data + 1;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 7)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x00); //Zero Flag
}

void ProgramExecutor::UpdateFlags_INC_16Bit(const _16Bit Data)
{
	Register::SetFlag(Register::FLAG::AF, (Data & 0x000f) + 0x0001 > 0x000f);//Auxiliary Carry Flag
	Register::SetFlag(Register::FLAG::OF, Data == (_16Bit)0x7fff);//Overflow Flag
	_16Bit Result = Data + 1;
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(Result) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, Result & (1 << 15)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, Result == 0x0000); //Zero Flag
}

//[TODO] Updating IP

/*<-----------------------------------------MOV------------------------------------------>*/

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


	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-1:MOV REG8, immd8
		return MOV_CASE_1(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-2:MOV REG16, immd16/immd8
		return MOV_CASE_2(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-3:[], immd8
		return MOV_CASE_3(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-4:[]/W[], immd16
		return MOV_CASE_4(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-5:W[], immd8
		return MOV_CASE_5(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-6: REG8, REG8
		return MOV_CASE_6(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-7: REG16, REG16
		return MOV_CASE_7(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-8: REG8, []
		return MOV_CASE_8(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-9: REG16, []/W[]
		return MOV_CASE_9(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-10: [], REG8
		return MOV_CASE_10(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-11: []/W[], REG16
		return MOV_CASE_11(OP1, OP2);
	}
	else if (Utility::IsSegmentRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-12: SREG, REG16
		return MOV_CASE_12(OP1, OP2);
	}
	else if (Utility::IsSegmentRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-13: SREG, []/W[]
		return MOV_CASE_13(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsSegmentRegister(OP2))
	{
		//Case-14: REG16, SREG
		return MOV_CASE_14(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsSegmentRegister(OP2))
	{
		//Case-15: []/W[], SREG
		return MOV_CASE_15(OP1, OP2);
	}

	return Error::LOG("Executon Failed @ MOV\n");
}

/*<-----------------------------------------ADD/ADC------------------------------------------>*/
bool ProgramExecutor::ADD_CASE_1(const std::string& REG8_D, const std::string& REG8_S, const bool ADC = false)
{
	//Case-1: REG8, REG8
	Byte X = Register::REG8(REG8_D);
	Byte Y = Register::REG8(REG8_S);
	_16Bit REG1 = X;
	_16Bit REG2 = Y;
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
	_16Bit REG = X;
	_16Bit MEM = Y;
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
	_16Bit MEM = X;
	_16Bit REG = Y;
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
	_16Bit X = Register::REG16(REG16_D);
	_16Bit Y = Register::REG16(REG16_S);
	uint32_t REG1 = X;
	uint32_t REG2 = Y;
	REG1 += REG2 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(REG16_D, (_16Bit)REG1);
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
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Memory::Get16Bit(Memory::PhysicalAddress(MEM));
	uint32_t REG = X;
	uint32_t _MEM = Y;
	REG += _MEM + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(REG16, (_16Bit)REG);
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
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Register::REG16(REG16);
	uint32_t _MEM = X;
	uint32_t REG = Y;
	_MEM += REG + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(PAdd, (_16Bit)_MEM);
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
	_16Bit MEM = X;
	_16Bit _IMMD8 = Y;
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
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Converter::HexToDec(IMMD16);
	uint32_t _MEM = X;
	uint32_t _IMMD16 = Y;
	_MEM += _IMMD16 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(PAdd, (_16Bit)_MEM);
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
	_16Bit REG = X;
	_16Bit _IMMD8 = Y;
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
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Converter::HexToDec(IMMD16);
	uint32_t REG = X;
	uint32_t _IMMD16 = Y;
	REG += _IMMD16 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(REG16, (_16Bit)REG);
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
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Converter::HexToDec(IMMD8);
	uint32_t REG = X;
	uint32_t _IMMD8 = Y;
	REG += _IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Register::REG16(REG16, (_16Bit)REG);
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
	_16Bit X = Memory::Get16Bit(Padd);
	_16Bit Y = Converter::HexToDec(IMMD8);
	uint32_t MEM = X;
	uint32_t _IMMD8 = Y;
	MEM += _IMMD8 + (ADC ? Register::GetFlag(Register::FLAG::CF) : 0);
	Memory::Set16Bit(Padd, (_16Bit)MEM);
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

/*-----------------------------------------SUB/SBB--------------------------------------------------------------*/
bool ProgramExecutor::SUB_CASE_1(const std::string& REG8_D, const std::string& REG8_S, const bool SBB = false)
{
	//Case-1: REG8, REG8
	Byte X = Register::REG8(REG8_D);
	Byte Y = Register::REG8(REG8_S);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
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
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
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
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
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
	_16Bit X = Register::REG16(REG16_D);
	_16Bit Y = Register::REG16(REG16_S);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(REG16_D, (_16Bit)Result);
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
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Memory::Get16Bit(Memory::PhysicalAddress(MEM));
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(REG16, (_16Bit)Result);
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
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Register::REG16(REG16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Memory::Set16Bit(PAdd, (_16Bit)Result);
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
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
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
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Converter::HexToDec(IMMD16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Memory::Set16Bit(PAdd, (_16Bit)Result);
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
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
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
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Converter::HexToDec(IMMD16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(REG16, (_16Bit)Result);
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
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Converter::HexToDec(IMMD8);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Register::REG16(REG16, (_16Bit)Result);
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
	_16Bit X = Memory::Get16Bit(Padd);
	_16Bit Y = Converter::HexToDec(IMMD8);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	if (SBB && Register::GetFlag(Register::FLAG::CF))
	{
		Result += 0xffff;//2sc complement of 1
	}
	Memory::Set16Bit(Padd, (_16Bit)Result);
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
	{
		//Case-1: REG8, REG8
		return SUB_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		return SUB_CASE_2(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		return SUB_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		return SUB_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		return SUB_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		return SUB_CASE_6(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		return SUB_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		return SUB_CASE_8(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		return SUB_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		return SUB_CASE_10(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		return SUB_CASE_11(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		return SUB_CASE_12(OP1, OP2);
	}
	return Error::LOG("Execution Failed @ SUB\n");
}

bool ProgramExecutor::SBB(const Operand& operand)
{
	const std::string& OP1 = operand.first;
	const std::string& OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1: REG8, REG8
		return SUB_CASE_1(OP1, OP2, true);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		return SUB_CASE_2(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		return SUB_CASE_3(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		return SUB_CASE_4(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		return SUB_CASE_5(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		return SUB_CASE_6(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		return SUB_CASE_7(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		return SUB_CASE_8(OP1, OP2, true);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		return SUB_CASE_9(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		return SUB_CASE_10(OP1, OP2, true);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		return SUB_CASE_11(OP1, OP2, true);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		return SUB_CASE_12(OP1, OP2, true);
	}
	return Error::LOG("Execution Failed @ SBB\n");
}

/*<---------------------------------------------MUL/IMUL------------------------------------------>*/

bool ProgramExecutor::MUL_CASE_1(const std::string& MEM8)
{
	//Case-1: MUL []
	_16Bit multiplicand = Register::REG8(REGISTER::AL);
	_16Bit mulitplier = Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	_16Bit Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::MUL_CASE_2(const std::string& MEM16)
{
	//Case-2: MUL W[]
	uint32_t multiplicand = Register::REG16(REGISTER::AX);
	uint32_t mulitplier = Memory::Get16Bit(Memory::PhysicalAddress(MEM16));
	uint32_t Result = multiplicand * mulitplier;
	_16Bit UpperHalf = (Result & 0xffff0000) >> 16;
	_16Bit LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::MUL_CASE_3(const std::string& REG8)
{
	//Case-3: MUL REG8
	_16Bit multiplicand = Register::REG8(REGISTER::AL);
	_16Bit mulitplier = Register::REG8(REG8);
	_16Bit Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::MUL_CASE_4(const std::string& REG16)
{
	//Case-4: MUL REG16
	uint32_t multiplicand = Register::REG16(REGISTER::AX);
	uint32_t mulitplier = Register::REG16(REG16);
	uint32_t Result = multiplicand * mulitplier;
	_16Bit UpperHalf = (Result & 0xffff0000) >> 16;
	_16Bit LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_1(const std::string& MEM8)
{
	//Case-1: IMUL []
	short multiplicand = (char)Register::REG8(REGISTER::AL);
	short mulitplier = (char)Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	short Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_2(const std::string& MEM16)
{
	//Case-2: IMUL W[]
	int multiplicand = (short)Register::REG16(REGISTER::AX);
	int mulitplier = (short)Memory::Get16Bit(Memory::PhysicalAddress(MEM16));
	int Result = multiplicand * mulitplier;
	_16Bit UpperHalf = (Result & 0xffff0000) >> 16;
	_16Bit LowerHalf = (Result & 0x0000ffff);
	Register::REG16(REGISTER::DX, UpperHalf);
	Register::REG16(REGISTER::AX, LowerHalf);
	UpdateFlags_MUL_16Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_3(const std::string& REG8)
{
	//Case-3: IMUL REG8
	short multiplicand = (char)Register::REG8(REGISTER::AL);
	short mulitplier = (char)Register::REG8(REG8);
	short Result = multiplicand * mulitplier;
	Register::REG16(REGISTER::AX, Result);
	UpdateFlags_MUL_8Bit();
	return true;
}

bool ProgramExecutor::IMUL_CASE_4(const std::string& REG16)
{
	//Case-4: IMUL REG16
	int multiplicand = (short)Register::REG16(REGISTER::AX);
	int mulitplier = (short)Register::REG16(REG16);
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

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: MUL []
		return MUL_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: MUL W[]
		return MUL_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: MUL REG8
		return MUL_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: MUL REG16
		return MUL_CASE_4(OP);
	}
	return Error::LOG("Execution Failed @MUL\n");
}

bool ProgramExecutor::IMUL(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: IMUL []
		return IMUL_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: IMUL W[]
		return IMUL_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: IMUL REG8
		return IMUL_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: IMUL REG16
		return IMUL_CASE_4(OP);
	}
	return Error::LOG("Execution Failed @IMUL\n");
}

/*<------------------------------------DIV/IDIV----------------------------------->*/

bool ProgramExecutor::DIV_CASE_1(const std::string& MEM8)
{
	//Case-1: DIV []
	_16Bit divisor = Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	_16Bit dividend = Register::REG16(REGISTER::AX);
	_16Bit quotient = dividend / divisor;
	_16Bit remainder = dividend % divisor;
	if (quotient > 0xff) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, (Byte)quotient);
	Register::REG8(REGISTER::AH, (Byte)remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV_CASE_2(const std::string& MEM16)
{
	//Case-2: DIV W[]
	uint32_t divisor = Memory::Get16Bit(Memory::PhysicalAddress(MEM16));
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

bool ProgramExecutor::DIV_CASE_3(const std::string& REG8)
{
	//Case-3: DIV REG8
	_16Bit divisor = Register::REG8(REG8);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	_16Bit dividend = Register::REG16(REGISTER::AX);
	_16Bit quotient = dividend / divisor;
	_16Bit remainder = dividend % divisor;
	if (quotient > 0xff) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, (Byte)quotient);
	Register::REG8(REGISTER::AH, (Byte)remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::DIV_CASE_4(const std::string& REG16)
{
	//Case-4: DIV REG16
	uint32_t divisor = Register::REG16(REG16);
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

bool ProgramExecutor::IDIV_CASE_1(const std::string& MEM8)
{
	//Case-1: IDIV []
	short divisor = (char)Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	short dividend = Register::REG16(REGISTER::AX);
	short quotient = dividend / divisor;
	short remainder = dividend % divisor;
	if (quotient > 0x7f || quotient < (char)0x80) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, (Byte)quotient);
	Register::REG8(REGISTER::AH, (Byte)remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_2(const std::string& MEM16)
{
	//Case-2: IDIV W[]
	int divisor = (short)Memory::Get16Bit(Memory::PhysicalAddress(MEM16));
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

bool ProgramExecutor::IDIV_CASE_3(const std::string& REG8)
{
	//Case-3: IDIV REG8
	short divisor = (char)Register::REG8(REG8);
	if (divisor == 0) { return Error::LOG("Division By 0\n"); }
	short dividend = Register::REG16(REGISTER::AX);
	short quotient = dividend / divisor;
	short remainder = dividend % divisor;
	if (quotient > 0x7f || quotient < (char)0x80) { return Error::LOG("Division Error. Result can't be fit in AL\n"); }
	Register::REG8(REGISTER::AL, (Byte)quotient);
	Register::REG8(REGISTER::AH, (Byte)remainder);
	//Flags are Undefined
	return true;
}

bool ProgramExecutor::IDIV_CASE_4(const std::string& REG16)
{
	//Case-4: IDIV REG16
	int divisor = (short)Register::REG16(REG16);
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

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: DIV []
		return DIV_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: DIV W[]
		return DIV_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: DIV REG8
		return DIV_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: DIV REG16
		return DIV_CASE_4(OP);
	}

	return Error::LOG("Execution Failed @DIV\n");
}

bool ProgramExecutor::IDIV(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: IDIV []
		return IDIV_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: IDIV W[]
		return IDIV_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: IDIV REG8
		return IDIV_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: IDIV REG16
		return IDIV_CASE_4(OP);
	}

	return Error::LOG("Execution Failed @IDIV\n");
}

/*<--------------------------LOGICAL OPERATION---------------------------------------->*/

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
	 _16Bit Result = 0;
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
	_16Bit Result = 0;
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
	_16Bit Result = 0;
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
	_16Bit Result = 0;
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
	_16Bit Result = 0;
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
	_16Bit Result = 0;
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
	_16Bit Result = 0;
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

/*<---------------------------------------CMP----------------------------------------------->*/

bool ProgramExecutor::CMP_CASE_1(const std::string& REG8_D, const std::string& REG8_S)
{
	//Case-1: REG8, REG8
	Byte X = Register::REG8(REG8_D);
	Byte Y = Register::REG8(REG8_S);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_2(const std::string& REG8, const std::string& MEM8)
{
	//Case-2: REG8, []
	Byte X = Register::REG8(REG8);
	Byte Y = Memory::Get8Bit(Memory::PhysicalAddress(MEM8));
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_3(const std::string& MEM, const std::string& REG8)
{
	//Case-3: [], REG8
	int PAdd = Memory::PhysicalAddress(MEM);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = Register::REG8(REG8);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_4(const std::string& REG16_D, const std::string& REG16_S)
{
	//Case-4: REG16, REG16
	_16Bit X = Register::REG16(REG16_D);
	_16Bit Y = Register::REG16(REG16_S);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_5(const std::string& REG16, const std::string& MEM)
{
	//Case-5: REG16, []/W[]
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Memory::Get16Bit(Memory::PhysicalAddress(MEM));
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_6(const std::string& MEM, const std::string& REG16)
{
	//Case-6: []/W[], REG16
	int PAdd = Memory::PhysicalAddress(MEM);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Register::REG16(REG16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_7(const std::string& MEM8, const std::string& IMMD8)
{
	//Case-7: [], IMMD8
	int PAdd = Memory::PhysicalAddress(MEM8);
	Byte X = Memory::Get8Bit(PAdd);
	Byte Y = (Byte)Converter::HexToDec(IMMD8);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_8(const std::string& MEM, const std::string& REG16)
{
	//Case-8: []/W[], IMMD16
	int PAdd = Memory::PhysicalAddress(MEM);
	_16Bit X = Memory::Get16Bit(PAdd);
	_16Bit Y = Converter::HexToDec(REG16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_9(const std::string& REG8, const std::string& IMMD8)
{
	//Case-9: REG8, IMMD8
	Byte X = Register::REG8(REG8);
	Byte Y = (Byte)Converter::HexToDec(IMMD8);
	Byte _2SC = -Y;
	_16Bit Result = _16Bit(X) + _16Bit(_2SC);
	UpdateFlags_CMP_8Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_10(const std::string& REG16, const std::string& IMMD16)
{
	//Case-10: REG16, IMMD16
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Converter::HexToDec(IMMD16);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_11(const std::string& REG16, const std::string& IMMD8)
{
	//Case-11: REG16, IMMD8
	_16Bit X = Register::REG16(REG16);
	_16Bit Y = Converter::HexToDec(IMMD8);
	_16Bit _2SC = -Y;
	uint32_t Result = uint32_t(X) + uint32_t(_2SC);
	UpdateFlags_CMP_16Bit(X, Y, Result);
	return true;
}

bool ProgramExecutor::CMP_CASE_12(const std::string& MEM16, const std::string& IMMD8)
{
	//Case-12: W[], IMMD8
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit X = Memory::Get16Bit(Padd);
	_16Bit Y = Converter::HexToDec(IMMD8);
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
	{
		//Case-1: REG8, REG8
		return CMP_CASE_1(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		return CMP_CASE_2(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		return CMP_CASE_3(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		return CMP_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		return CMP_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		return CMP_CASE_6(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		return CMP_CASE_7(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		return CMP_CASE_8(OP1, OP2);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		return CMP_CASE_9(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		return CMP_CASE_10(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		return CMP_CASE_11(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		return CMP_CASE_12(OP1, OP2);
	}
	return Error::LOG("Execution Failed @ CMP\n");
}

/*<---------------------------------------------NEG------------------------------------->*/

//The CF flag set to 0 if the source operand is 0; otherwise it is set to 1. The OF, SF, ZF, AF, and PF flags are set according to the result.
//Neg can be considered as 0 - DATA. Usefull statement for updating flags.
//Negating the smallest signed integer in a register results in a positive integer, which cannot fit into the same register.

bool ProgramExecutor::NEG_CASE_1(const std::string& MEM8)
{
	//Case-1: NEG []
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	Memory::Set8Bit(Padd, -Data);
	UpdateFlags_NEG_8Bit(Data);
	return true;
}

bool ProgramExecutor::NEG_CASE_2(const std::string& MEM16)
{
	//Case-2: NEG W[]
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit Data = Memory::Get16Bit(Padd);
	Memory::Set16Bit(Padd, -Data);
	UpdateFlags_NEG_16Bit(Data);
	return true;
}

bool ProgramExecutor::NEG_CASE_3(const std::string& REG8)
{
	//Case-3: NEG REG8
	Byte Data = Register::REG8(REG8);
	Register::REG8(REG8, -Data);
	UpdateFlags_NEG_8Bit(Data);
	return true;
}

bool ProgramExecutor::NEG_CASE_4(const std::string& REG16)
{
	//Case-4: NEG REG16
	_16Bit Data = Register::REG16(REG16);
	Register::REG16(REG16, -Data);
	UpdateFlags_NEG_16Bit(Data);
	return true;
}

bool ProgramExecutor::NEG(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: NEG []
		return NEG_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: NEG W[]
		return NEG_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: NEG REG8
		return NEG_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: NEG REG16
		return NEG_CASE_4(OP);
	}

	return Error::LOG("Execution Failed @NEG\n");
}

/*<----------------------------------NOT------------------------------------------------>*/

//No flags are affected

bool ProgramExecutor::NOT_CASE_1(const std::string& MEM8)
{
	//Case-1: NOT []
	int Padd = Memory::PhysicalAddress(MEM8);
	Memory::Set8Bit(Padd, ~Memory::Get8Bit(Padd));
	return true;
}
bool ProgramExecutor::NOT_CASE_2(const std::string& MEM16)
{
	//Case-2: NOT W[]
	int Padd = Memory::PhysicalAddress(MEM16);
	Memory::Set16Bit(Padd, ~Memory::Get16Bit(Padd));
	return true;
}
bool ProgramExecutor::NOT_CASE_3(const std::string& REG8)
{
	//Case-3: NOT REG8
	Register::REG8(REG8, ~Register::REG8(REG8));
	return true;
}
bool ProgramExecutor::NOT_CASE_4(const std::string& REG16)
{
	//Case-4: NOT REG16
	Register::REG16(REG16, ~Register::REG16(REG16));
	return true;
}
bool ProgramExecutor::NOT(const Operand& operand)
{
	std::string OP = operand.first;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: NOT []
		return NOT_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: NOT W[]
		return NOT_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: NOT REG8
		return NOT_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: NOT REG16
		return NOT_CASE_4(OP);
	}

	return Error::LOG("Execution Failed @NOT\n");
}

/*<-------------------------------------------DEC------------------------------->*/
//The CF flag is not affected.The OF, SF, ZF, AF, and PF flags are set according to the result.

bool ProgramExecutor::DEC_CASE_1(const std::string& MEM8)
{
	//Case-1: DEC []
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	Memory::Set8Bit(Padd, Data - 1);
	UpdateFlags_DEC_8Bit(Data);
	return true;

}

bool ProgramExecutor::DEC_CASE_2(const std::string& MEM16)
{
	//Case-2: DEC W[]
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit Data = Memory::Get16Bit(Padd);
	Memory::Set16Bit(Padd, Data - 1);
	UpdateFlags_DEC_16Bit(Data);
	return true;
}

bool ProgramExecutor::DEC_CASE_3(const std::string& REG8)
{
	//Case-3: DEC REG8
	Byte Data = Register::REG8(REG8);
	Register::REG8(REG8, Data - 1);
	UpdateFlags_DEC_8Bit(Data);
	return true;
}

bool ProgramExecutor::DEC_CASE_4(const std::string& REG16)
{
	//Case-4: DEC REG16
	_16Bit Data = Register::REG16(REG16);
	Register::REG16(REG16, Data - 1);
	UpdateFlags_DEC_16Bit(Data);
	return true;
}

bool ProgramExecutor::DEC(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand @DEC\n");
	}

	std::string OP = operand.first;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: DEC []
		return DEC_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: DEC W[]
		return DEC_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: DEC REG8
		return DEC_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: DEC REG16
		return DEC_CASE_4(OP);
	}

	return Error::LOG("Wrong Syntax @DEC\n");
}

/*<-------------------------------INC------------------------------>*/
//The CF flag is not affected. The OF, SF, ZF, AF, and PF flags are set according to the result.

bool ProgramExecutor::INC_CASE_1(const std::string& MEM8)
{
	//Case-1: INC []
	int Padd = Memory::PhysicalAddress(MEM8);
	Byte Data = Memory::Get8Bit(Padd);
	Memory::Set8Bit(Padd, Data + 1);
	UpdateFlags_INC_8Bit(Data);
	return true;
}

bool ProgramExecutor::INC_CASE_2(const std::string& MEM16)
{
	//Case-2: INC W[]
	int Padd = Memory::PhysicalAddress(MEM16);
	_16Bit Data = Memory::Get16Bit(Padd);
	Memory::Set16Bit(Padd, Data + 1);
	UpdateFlags_INC_16Bit(Data);
	return true;
}

bool ProgramExecutor::INC_CASE_3(const std::string& REG8)
{
	//Case-3: INC REG8
	Byte Data = Register::REG8(REG8);
	Register::REG8(REG8, Data + 1);
	UpdateFlags_INC_8Bit(Data);
	return true;
}

bool ProgramExecutor::INC_CASE_4(const std::string& REG16)
{
	//Case-4: INC REG16
	_16Bit Data = Register::REG16(REG16);
	Register::REG16(REG16, Data + 1);
	UpdateFlags_INC_16Bit(Data);
	return true;
}

bool ProgramExecutor::INC(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand @INC\n");
	}

	std::string OP = operand.first;

	if (Utility::IsValidMemory(OP) && Utility::IsByteMemory(OP))
	{
		//Case-1: INC []
		return INC_CASE_1(OP);
	}
	else if (Utility::IsValidMemory(OP) && Utility::IsWordMemory(OP))
	{
		//Case-2: INC W[]
		return INC_CASE_2(OP);
	}
	else if (Utility::Is8BitRegister(OP))
	{
		//Case-3: INC REG8
		return INC_CASE_3(OP);
	}
	else if (Utility::Is16BitRegister(OP))
	{
		//Case-4: INC REG16
		return INC_CASE_4(OP);
	}

	return Error::LOG("Wrong Syntax @INC\n");
}