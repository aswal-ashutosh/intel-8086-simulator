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
	static bool DAA(const Operand&);
	static bool SHL_SAL(const Operand&);
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
	CallBacks[MNEMONIC::DAA] = DAA;
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
