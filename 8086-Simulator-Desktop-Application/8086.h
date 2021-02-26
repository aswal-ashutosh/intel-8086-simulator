#pragma once
#include"error_handler.h"
#include"typedef.h"
#include"utility.h"
#include"register.h"
#include"memory.h"
#include"instruction.h"
#include"labels.h"
#include<unordered_map>
#include"program_loader.h"

class ProgramExecutor
{
	static int CurrInsIndex;
	static bool HLT_STATE_REACHED;
	static std::unordered_map<std::string, bool (*)(const Operand&)> CallBacks;
	static std::vector<Instruction> Program;
	static std::vector<int> CallStack;

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

	static bool SHL_SAL_CASE_1(const std::string&, const std::string&);
	static bool SHL_SAL_CASE_2(const std::string&);
	static bool SHL_SAL_CASE_3(const std::string&, const std::string&);
	static bool SHL_SAL_CASE_4(const std::string&);
	static bool SHL_SAL_CASE_5(const std::string&, const std::string&);
	static bool SHL_SAL_CASE_6(const std::string&);
	static bool SHL_SAL_CASE_7(const std::string&, const std::string&);
	static bool SHL_SAL_CASE_8(const std::string&);

	static bool SHR_CASE_1(const std::string&, const std::string&);
	static bool SHR_CASE_2(const std::string&);
	static bool SHR_CASE_3(const std::string&, const std::string&);
	static bool SHR_CASE_4(const std::string&);
	static bool SHR_CASE_5(const std::string&, const std::string&);
	static bool SHR_CASE_6(const std::string&);
	static bool SHR_CASE_7(const std::string&, const std::string&);
	static bool SHR_CASE_8(const std::string&);

	static bool SAR_CASE_1(const std::string&, const std::string&);
	static bool SAR_CASE_2(const std::string&);
	static bool SAR_CASE_3(const std::string&, const std::string&);
	static bool SAR_CASE_4(const std::string&);
	static bool SAR_CASE_5(const std::string&, const std::string&);
	static bool SAR_CASE_6(const std::string&);
	static bool SAR_CASE_7(const std::string&, const std::string&);
	static bool SAR_CASE_8(const std::string&);

	static bool RCL_CASE_1(const std::string&, const std::string&);
	static bool RCL_CASE_2(const std::string&);
	static bool RCL_CASE_3(const std::string&, const std::string&);
	static bool RCL_CASE_4(const std::string&);
	static bool RCL_CASE_5(const std::string&, const std::string&);
	static bool RCL_CASE_6(const std::string&);
	static bool RCL_CASE_7(const std::string&, const std::string&);
	static bool RCL_CASE_8(const std::string&);

	static bool RCR_CASE_1(const std::string&, const std::string&);
	static bool RCR_CASE_2(const std::string&);
	static bool RCR_CASE_3(const std::string&, const std::string&);
	static bool RCR_CASE_4(const std::string&);
	static bool RCR_CASE_5(const std::string&, const std::string&);
	static bool RCR_CASE_6(const std::string&);
	static bool RCR_CASE_7(const std::string&, const std::string&);
	static bool RCR_CASE_8(const std::string&);

	static bool ROL_CASE_1(const std::string&, const std::string&);
	static bool ROL_CASE_2(const std::string&);
	static bool ROL_CASE_3(const std::string&, const std::string&);
	static bool ROL_CASE_4(const std::string&);
	static bool ROL_CASE_5(const std::string&, const std::string&);
	static bool ROL_CASE_6(const std::string&);
	static bool ROL_CASE_7(const std::string&, const std::string&);
	static bool ROL_CASE_8(const std::string&);

	static bool ROR_CASE_1(const std::string&, const std::string&);
	static bool ROR_CASE_2(const std::string&);
	static bool ROR_CASE_3(const std::string&, const std::string&);
	static bool ROR_CASE_4(const std::string&);
	static bool ROR_CASE_5(const std::string&, const std::string&);
	static bool ROR_CASE_6(const std::string&);
	static bool ROR_CASE_7(const std::string&, const std::string&);
	static bool ROR_CASE_8(const std::string&);

	static bool XCHG_CASE_1(std::string&, std::string&);
	static bool XCHG_CASE_2(std::string&, std::string&);
	static bool XCHG_CASE_3(std::string&, std::string&);
	static bool XCHG_CASE_4(std::string&, std::string&);
	static bool XCHG_CASE_5(std::string&, std::string&);
	static bool XCHG_CASE_6(std::string&, std::string&);

	//Functions to update flag register after executing a instruction
	static void UpdateFlags_ADD_8Bit(const Byte, const Byte, const Word);
	static void UpdateFlags_ADD_16Bit(const Word, const Word, const uint32_t);
	static void UpdateFlags_ADC_8Bit(const Byte, const Byte, const Word);
	static void UpdateFlags_ADC_16Bit(const Word, const Word, const uint32_t);
	static void UpdateFlags_SUB_8Bit(const Byte, const Byte, const Word);
	static void UpdateFlags_SUB_16Bit(const Word, const Word, const uint32_t);
	static void UpdateFlags_SBB_8Bit(const Byte, const Byte, const Word);
	static void UpdateFlags_SBB_16Bit(const Word, const Word, const uint32_t);

	static void UpdateFlags_CMP_8Bit(const Byte, const Byte, const Word);
	static void UpdateFlags_CMP_16Bit(const Word, const Word, const uint32_t);


	//Will update flags for AND, XOR & OR
	static void UpdateFlags_LOGIC_8Bit(const Byte);
	static void UpdateFlags_LOGIC_16Bit(const Word);

	//Will also Update the flags for IMUL
	static void UpdateFlags_MUL_8Bit();
	static void UpdateFlags_MUL_16Bit();
	
	static void UpdateFlags_NEG_8Bit(const Byte);
	static void UpdateFlags_NEG_16Bit(const Word);

	static void UpdateFlags_DEC_8Bit(const Byte);
	static void UpdateFlags_DEC_16Bit(const Word);
	static void UpdateFlags_INC_8Bit(const Byte);
	static void UpdateFlags_INC_16Bit(const Word);

	static void UpdateFlags_SHL_SAL_8Bit(const Byte, int);
	static void UpdateFlags_SHL_SAL_16Bit(const Word, int);

	static void UpdateFlags_SHR_8Bit(const Byte, const Byte, int);
	static void UpdateFlags_SHR_16Bit(const Word, const Word, int);

	static void UpdateFlags_SAR_8Bit(const Byte, int);
	static void UpdateFlags_SAR_16Bit(const Word, int);

	static void UpdateFlags_RCL_8Bit(const Byte, int);
	static void UpdateFlags_RCL_16Bit(const Word, int);

	static void UpdateFlags_RCR_8Bit(const Byte, int);
	static void UpdateFlags_RCR_16Bit(const Word, int);

	static void UpdateFlags_ROL_8Bit(const Byte, int);
	static void UpdateFlags_ROL_16Bit(const Word, int);

	static void UpdateFlags_ROR_8Bit(const Byte, int);
	static void UpdateFlags_ROR_16Bit(const Word, int);

	//Check if there is a instruction at index pointed by CurrentInsIndex and update the IP.
	static bool NextInstructionExist();
public:
	static void ClearProgram();
	static void LoadCallBacks();
	static bool Execute();
	static bool ExecuteOne();
	static int GetCurrInsLineNumber();
	static bool ReachedHLT();
	static void GetProgramFromLoader();


	static bool MOV(const Operand&);
	static bool XCHG(const Operand&);
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
	static bool SHR(const Operand&);
	static bool SAR(const Operand&);
	static bool RCL(const Operand&);
	static bool RCR(const Operand&);
	static bool ROL(const Operand&);
	static bool ROR(const Operand&);
	static bool STC(const Operand&);
	static bool CLC(const Operand&);
	static bool CMC(const Operand&);
	static bool JMP(const Operand&);
	static bool JC(const Operand&);
	static bool JNC(const Operand&);
	static bool JZ_JE(const Operand&);
	static bool JNZ_JNE(const Operand&);
	static bool JPE_JP(const Operand&);
	static bool JPO_JNP(const Operand&);
	static bool JS(const Operand&);
	static bool JNS(const Operand&);
	static bool JO(const Operand&);
	static bool JNO(const Operand&);
	static bool CALL(const Operand&);
	static bool RET(const Operand&);
	static bool HLT(const Operand&);
};

int ProgramExecutor::CurrInsIndex = 0;
bool ProgramExecutor::HLT_STATE_REACHED = false;
std::vector<int> ProgramExecutor::CallStack;
std::vector<Instruction> ProgramExecutor::Program;
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
	CallBacks[MNEMONIC::SAL] = SHL_SAL;
	CallBacks[MNEMONIC::SHL] = SHL_SAL;
	CallBacks[MNEMONIC::SHR] = SHR;
	CallBacks[MNEMONIC::SAR] = SAR;
	CallBacks[MNEMONIC::RCL] = RCL;
	CallBacks[MNEMONIC::RCR] = RCR;
	CallBacks[MNEMONIC::ROL] = ROL;
	CallBacks[MNEMONIC::ROR] = ROR;
	CallBacks[MNEMONIC::STC] = STC;
	CallBacks[MNEMONIC::CLC] = CLC;
	CallBacks[MNEMONIC::CMC] = CMC;
	CallBacks[MNEMONIC::XCHG] = XCHG;
	CallBacks[MNEMONIC::JMP] = JMP;
	CallBacks[MNEMONIC::JC] = JC;
	CallBacks[MNEMONIC::JNC] = JNC;
	CallBacks[MNEMONIC::JZ] = JZ_JE;
	CallBacks[MNEMONIC::JE] = JZ_JE;
	CallBacks[MNEMONIC::JNZ] = JNZ_JNE;
	CallBacks[MNEMONIC::JNE] = JNZ_JNE;
	CallBacks[MNEMONIC::JPE] = JPE_JP;
	CallBacks[MNEMONIC::JP] = JPE_JP;
	CallBacks[MNEMONIC::JPO] = JPO_JNP;
	CallBacks[MNEMONIC::JNP] = JPO_JNP;
	CallBacks[MNEMONIC::JS] = JS;
	CallBacks[MNEMONIC::JNS] = JNS;
	CallBacks[MNEMONIC::JO] = JO;
	CallBacks[MNEMONIC::JNO] = JNO;
	CallBacks[MNEMONIC::CALL] = CALL;
	CallBacks[MNEMONIC::RET] = RET;
	CallBacks[MNEMONIC::HLT] = HLT;
}

void ProgramExecutor::GetProgramFromLoader()
{
	ProgramExecutor::Program = ProgramLoader::GetProgram();
}

bool ProgramExecutor::Execute()
{
	//[TODO:] Remove extra checking at release version
	while(!HLT_STATE_REACHED)
	{
		const Instruction& Ins = Program[CurrInsIndex];
		if (!CallBacks[Ins.Mnemonic](Ins.operand))
		{
			return false;
		}
	}
	return true;
}

bool ProgramExecutor::ExecuteOne()
{
	const Instruction& Ins = Program[CurrInsIndex];
	return CallBacks[Ins.Mnemonic](Ins.operand);
}

int ProgramExecutor::GetCurrInsLineNumber()
{
	return Program[CurrInsIndex].LineNumber;
}

bool ProgramExecutor::ReachedHLT()
{
	return HLT_STATE_REACHED;
}

bool ProgramExecutor::NextInstructionExist()
{
	if (CurrInsIndex < ProgramLoader::ProgramSize())
	{
		Register::IP(Program[CurrInsIndex].Offset);
		return true;
	}
	else
	{
		return Error::LOG(ERROR_TYPE::NEVER_REACHED_HLT);
	}
}

void ProgramExecutor::ClearProgram()
{
	ProgramExecutor::Program.clear();
	ProgramExecutor::CurrInsIndex = 0;
	ProgramExecutor::HLT_STATE_REACHED = false;
}