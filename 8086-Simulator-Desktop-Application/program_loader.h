#pragma once
#include"operands.h"
#include"utility.h"
#include"error_handler.h"
#include<fstream>
#include"converter.h"
#include<iostream>
#include<unordered_map>
#include"instruction.h"
#include"hex_size.h"
#include"labels.h"
#include<iomanip>
#include"register.h"
#include"memory.h"

class ProgramLoader
{
	static std::vector<Instruction> Program;
	static int CurrInsIndex;
	//static int CurrentLoadingAddressOffset;

	static std::unordered_map<std::string, bool (*)(const Operand&)> CallBacks;
	static std::fstream MACHINE_CODE;

	static bool MOV_CASE_1(std::string&, std::string&);
	static bool MOV_CASE_2(std::string&, std::string&);
	static bool MOV_CASE_3(std::string&, std::string&);
	static bool MOV_CASE_4(std::string&, std::string&);
	static bool MOV_CASE_5(std::string&, std::string&);
	static bool MOV_CASE_6(std::string&, std::string&);
	static bool MOV_CASE_7(std::string&, std::string&);
	static bool MOV_CASE_8(std::string&, std::string&);
	static bool MOV_CASE_9(std::string&, std::string&);
	static bool MOV_CASE_10(std::string&, std::string&);
	static bool MOV_CASE_11(std::string&, std::string&);
	static bool MOV_CASE_12(std::string&, std::string&);
	static bool MOV_CASE_13(std::string&, std::string&);
	static bool MOV_CASE_14(std::string&, std::string&);
	static bool MOV_CASE_15(std::string&, std::string&);

	static bool XCHG_CASE_1(std::string&, std::string&);
	static bool XCHG_CASE_2(std::string&, std::string&);
	static bool XCHG_CASE_3(std::string&, std::string&);
	static bool XCHG_CASE_4(std::string&, std::string&);
	static bool XCHG_CASE_5(std::string&, std::string&);
	static bool XCHG_CASE_6(std::string&, std::string&);

	//AAACOSSX generate machine code for => ADD, ADC, AND, CMP, OR, SUB, SBB, XOR
	static bool AAACOSSX(const Operand&, const Byte, const Byte);
	static bool AAACOSSX_CASE_1(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_2(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_3(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_4(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_5(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_6(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_7(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_8(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_9(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_10(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_11(std::string&, std::string&, const Byte, const Byte);
	static bool AAACOSSX_CASE_12(std::string&, std::string&, const Byte, const Byte);


	static bool MUL_CASE_1(std::string&);
	static bool MUL_CASE_2(std::string&);
	static bool MUL_CASE_3(std::string&);
	static bool MUL_CASE_4(std::string&);
	
	static bool IMUL_CASE_1(std::string&);
	static bool IMUL_CASE_2(std::string&);
	static bool IMUL_CASE_3(std::string&);
	static bool IMUL_CASE_4(std::string&);

	static bool DIV_CASE_1(std::string&);
	static bool DIV_CASE_2(std::string&);
	static bool DIV_CASE_3(std::string&);
	static bool DIV_CASE_4(std::string&);

	static bool IDIV_CASE_1(std::string&);
	static bool IDIV_CASE_2(std::string&);
	static bool IDIV_CASE_3(std::string&);
	static bool IDIV_CASE_4(std::string&);

	static bool NEG_CASE_1(std::string&);
	static bool NEG_CASE_2(std::string&);
	static bool NEG_CASE_3(std::string&);
	static bool NEG_CASE_4(std::string&);

	static bool NOT_CASE_1(std::string&);
	static bool NOT_CASE_2(std::string&);
	static bool NOT_CASE_3(std::string&);
	static bool NOT_CASE_4(std::string&);

	static bool DEC_CASE_1(std::string&);
	static bool DEC_CASE_2(std::string&);
	static bool DEC_CASE_3(std::string&);
	static bool DEC_CASE_4(std::string&);

	static bool INC_CASE_1(std::string&);
	static bool INC_CASE_2(std::string&);
	static bool INC_CASE_3(std::string&);
	static bool INC_CASE_4(std::string&);

	//Will Generate Machine Code for Shifting and rotation related instruction
	static bool ROTATE_SHIFT(const Operand&, Byte);
	static bool ROTATE_SHIFT_CASE_1(std::string&, std::string&, Byte);
	static bool ROTATE_SHIFT_CASE_2(std::string&, Byte);
	static bool ROTATE_SHIFT_CASE_3(std::string&, std::string&, Byte);
	static bool ROTATE_SHIFT_CASE_4(std::string&, Byte);
	static bool ROTATE_SHIFT_CASE_5(std::string&, std::string&, Byte);
	static bool ROTATE_SHIFT_CASE_6(std::string&, Byte);
	static bool ROTATE_SHIFT_CASE_7(std::string&, std::string&, Byte);
	static bool ROTATE_SHIFT_CASE_8(std::string&, Byte);

public:

	static void HandleForwardReferencing();

	//Function to check wether a string is Mnemonic or not
	static bool IsValidMnemonic(const std::string& s);
	static bool IsJumpCallInstruction(const std::string& s);
	
	//Program
	static void AddInstruction(const Instruction&);
	static int ProgramSize();
	static std::vector<Instruction> GetProgram();
	static void ClearProgram();

	static void LoadCallBacks();
	static bool Load();

	static bool MOV(const Operand&);
	static bool XCHG(const Operand&);
	static bool ADD(const Operand&);
	static bool ADC(const Operand&);
	static bool AND(const Operand&);
	static bool CMP(const Operand&);
	static bool OR(const Operand&);
	static bool SUB(const Operand&);
	static bool SBB(const Operand&);
	static bool XOR(const Operand&);
	static bool MUL(const Operand&);
	static bool IMUL(const Operand&);
	static bool DIV(const Operand&);
	static bool IDIV(const Operand&);
	static bool NEG(const Operand&);
	static bool NOT(const Operand&);
	static bool DEC(const Operand&);
	static bool INC(const Operand&);
	static bool DAA(const Operand&);
	static bool SHL(const Operand&);
	static bool SAL(const Operand&);
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

std::fstream ProgramLoader::MACHINE_CODE;

std::unordered_map<std::string, bool (*)(const Operand&)> ProgramLoader::CallBacks;

std::vector<Instruction> ProgramLoader::Program;

int ProgramLoader::CurrInsIndex = 0;

//int ProgramLoader::CurrentLoadingAddressOffset = 0;

void ProgramLoader::AddInstruction(const Instruction& instruction)
{
	Program.push_back(instruction);
}

int ProgramLoader::ProgramSize()
{
	return Program.size();
}

std::vector<Instruction> ProgramLoader::GetProgram()
{
	return Program;
}

void ProgramLoader::ClearProgram()
{
	ProgramLoader::Program.clear();
	ProgramLoader::CurrInsIndex = 0;
}

void ProgramLoader::LoadCallBacks()
{
	CallBacks[MNEMONIC::MOV] = MOV;
	CallBacks[MNEMONIC::XCHG] = XCHG;
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
	CallBacks[MNEMONIC::SHL] = SHL;
	CallBacks[MNEMONIC::SAL] = SAL;
	CallBacks[MNEMONIC::SHR] = SHR;
	CallBacks[MNEMONIC::SAR] = SAR;
	CallBacks[MNEMONIC::RCL] = RCL;
	CallBacks[MNEMONIC::RCR] = RCR;
	CallBacks[MNEMONIC::ROL] = ROL;
	CallBacks[MNEMONIC::ROR] = ROR;
	CallBacks[MNEMONIC::STC] = STC;
	CallBacks[MNEMONIC::CLC] = CLC;
	CallBacks[MNEMONIC::CMC] = CMC;
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

void ProgramLoader::HandleForwardReferencing()
{
	unsigned int Offset = 0;
	std::unordered_map<std::string, std::vector<int>> Pos;
	
	for (int i = 0; i < (int)Program.size(); ++i)
	{
		Instruction& ins = Program[i];
		ins.Offset = Offset;
		/*
			For JUMP Instructions label address can be of 1 bytes or 2 byte which is not known yet. Assuming the size of label as 1 Byte the size of
			instruction will be 2 byte. It this assumption is found wrong it will be updated later.
			For Call label address will always take 2 Byte which means the total size of instruction will be 3 bytes.
		*/
		if (ins.Mnemonic == MNEMONIC::CALL)
		{
			Offset += 3;
			Pos[ins.operand.first].push_back(i);
		}
		else if (IsJumpCallInstruction(ins.Mnemonic)) //JUMP instructions
		{
			Offset += 2;

			Pos[ins.operand.first].push_back(i);
		}
		else
		{
			Offset += ins.MachineCode.size();
		}
	}

	const std::unordered_map<std::string, int> Labels = Label::GetLabels();

	std::unordered_map<std::string, HEX_SIZE> AllocatedSize;

	for (const std::pair<std::string, int> x : Labels)
	{
		AllocatedSize[x.first] = HEX_SIZE::BYTE;
	}

	//Lamda to calculate the size of location
	auto Size = [](const unsigned int Offset)->HEX_SIZE
	{
		if (Offset >= 0x00 && Offset <= 0xff)
		{
			return HEX_SIZE::BYTE;
		}
		else if (Offset > 0xff && Offset <= 0xffff)
		{
			return HEX_SIZE::WORD;
		}
		else
		{
			//ToDo[Remove in release]
			Error::LOG("Lamda doesn't expect this size\n");
			return HEX_SIZE::WORD;
		}
	};

	bool NeedToBalance = true;
	while (NeedToBalance)
	{
		NeedToBalance = false;//Assuming
		for (const std::pair<const std::string, int>& x : Labels)
		{
			const std::string& label = x.first;
			const int Index = x.second;
			if (Size(Program[Index].Offset) != AllocatedSize[label])
			{
				NeedToBalance = true;
				AllocatedSize[label] = Size(Program[Index].Offset);
				//We have assumed Byte size but it's found different => Word size => So we need to increment offset of each
				//instruction after it.
				//But if the the instruction there is call then no need to increment by 1(As already given required size)
				for (int start : Pos[label])
				{
					if (Program[start].Mnemonic == MNEMONIC::CALL) { continue; }

					for (int k = start + 1; k < (int)Program.size(); ++k)
					{
						Program[k].Offset += 1;
					}
				}
			}
		}
	}

	for (const std::pair<const std::string, int>& x : Labels)
	{
		const std::string& label = x.first;
		const Word Address = Program[x.second].Offset;
		for (int Idx : Pos[label])
		{
			//Add more
			if (Program[Idx].Mnemonic == MNEMONIC::CALL)
			{
				Program[Idx].MachineCode.push_back((Byte)(Address & 0x00ff));
				Program[Idx].MachineCode.push_back((Byte)((Address & 0xff00) >> 8));
			}
			else if (Program[Idx].Mnemonic == MNEMONIC::JMP)
			{
				if (AllocatedSize[label] == HEX_SIZE::BYTE)
				{
					//Short jmp
					Program[Idx].MachineCode.push_back(0xEB);
					Program[Idx].MachineCode.push_back((Byte)(Address & 0x00ff));
				}
				else
				{
					//near jmp
					Program[Idx].MachineCode.push_back(0xE9);
					Program[Idx].MachineCode.push_back((Byte)(Address & 0x00ff));
					Program[Idx].MachineCode.push_back((Byte)((Address & 0xff00) >> 8));
				}
			}
			else
			{
				//JNC,JC...etc
				if (AllocatedSize[label] == HEX_SIZE::BYTE)
				{
					//Short jmp
					Program[Idx].MachineCode.push_back((Byte)(Address & 0x00ff));
				}
				else
				{
					//near jmp
					Program[Idx].MachineCode.push_back((Byte)(Address & 0x00ff));
					Program[Idx].MachineCode.push_back((Byte)((Address & 0xff00) >> 8));
				}
			}
		}
	}

	MACHINE_CODE.open("machine_code.txt", std::ios::out);

	for (const Instruction& Ins : Program)
	{
		MACHINE_CODE << Converter::DecToHex(Ins.Offset, HEX_SIZE::WORD).substr(0, 4) << ": ";
		std::string OPCODE;
		for (int i = 0, k = 0; i < (int)Ins.MachineCode.size(); ++i)
		{
			//Start-Load in memory
			int Padd = (int)Register::REG16(REGISTER::CS) * 0x10 + (Ins.Offset + i);
			Memory::Set8Bit(Padd, Ins.MachineCode[i]);
			//End-Load in memory

			OPCODE += Converter::DecToHex(Ins.MachineCode[i]).substr(0, 2) + ' ';
			if (++k == 6)
			{
				k = 0;
				MACHINE_CODE << std::left << std::setw(18) << OPCODE;
				OPCODE.clear();
				if (i + 1 < (int)Ins.MachineCode.size())
				{
					
					MACHINE_CODE << "\n      ";
				}
			}
		}
		if (!OPCODE.empty())
		{
			MACHINE_CODE << std::left << std::setw(18) << OPCODE;
		}
		

		std::string CODE;
		CODE += "\t\t[" + Ins.Mnemonic;
		if (!Ins.operand.first.empty())
		{
			CODE += ' ' + Ins.operand.first;
			
		}
		if (!Ins.operand.second.empty())
		{
			CODE += ' ' + Ins.operand.second;
		}
		CODE += "]\n";
		MACHINE_CODE << CODE;
	}
	MACHINE_CODE << std::flush;
	MACHINE_CODE.close();
}

bool ProgramLoader::Load()
{
	//[TODO:] Remove extra checking at release version
	const int ProgramSize = Program.size();
	for (ProgramLoader::CurrInsIndex = 0; ProgramLoader::CurrInsIndex < ProgramSize; ++ProgramLoader::CurrInsIndex)
	{
		const Instruction& CurrIns = Program[CurrInsIndex];
		if (CallBacks.count(CurrIns.Mnemonic))
		{
			if (!CallBacks[CurrIns.Mnemonic](CurrIns.operand))
			{
				return false;
			}
		}
		else
		{
			return Error::LOG(CurrIns.Mnemonic + " is not implemented yet! @ Load\n");
		}
	}
	HandleForwardReferencing();
	return true;
}


bool ProgramLoader::IsValidMnemonic(const std::string& s)
{
	return CallBacks.count(s);
}

bool ProgramLoader::IsJumpCallInstruction(const std::string& S)
{
	bool OK = false;
	OK |= (S == MNEMONIC::JMP);
	OK |= (S == MNEMONIC::JC);
	OK |= (S == MNEMONIC::JNC);
	OK |= (S == MNEMONIC::JZ);
	OK |= (S == MNEMONIC::JE);
	OK |= (S == MNEMONIC::JNZ);
	OK |= (S == MNEMONIC::JNE);
	OK |= (S == MNEMONIC::JPE);
	OK |= (S == MNEMONIC::JP);
	OK |= (S == MNEMONIC::JPO);
	OK |= (S == MNEMONIC::JNP);
	OK |= (S == MNEMONIC::JS);
	OK |= (S == MNEMONIC::JNS);
	OK |= (S == MNEMONIC::JO);
	OK |= (S == MNEMONIC::JNO);
	OK |= (S == MNEMONIC::CALL);
	return OK;
}
/*<-------------------------------------MOV-------------------------------------->*/

bool ProgramLoader::MOV_CASE_1(std::string& REG8, std::string& IMMD8)
{
	//Case-1:MOV REG8, immd8
	//opcode(8Bit)=> B0 + reg_Code

	/*const std::string& OPCODE = Converter::DecToHex(0xB0 + REG_CODE.find(REG8)->second);*/
	Utility::Format16Bit(IMMD8);
	//OUT << OPCODE.substr(0, 2) << ' ' << IMMD8.substr(2, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xB0 + REG_CODE.find(REG8)->second);
	Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));
	return true;
}

bool ProgramLoader::MOV_CASE_2(std::string& REG16, std::string& IMMD)
{
	//Case-2:MOV REG16, immd16/immd8
	//OPCODE(8bit)=> B8 + reg_Code
	//const std::string& OPCODE = Converter::DecToHex(0xB8 + REG_CODE.find(REG16)->second);
	Utility::Format16Bit(IMMD);
	//OUT << OPCODE.substr(0, 2) << ' ' << IMMD.substr(2, 2) << ' ' << IMMD.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xB8 + REG_CODE.find(REG16)->second);
	Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD.substr(2, 2)));
	Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD.substr(0, 2)));
	return true;
}

bool ProgramLoader::MOV_CASE_3(std::string& MEM8, std::string& IMMD8)
{
	//Case-3:[], immd8
	//As there is no register so reg code will be 000
	//1st Byte wiil be C6
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | info.rm;	//Reg-Code is 000 already
		//std::string _2ndByteHex = Converter::DecToHex(B2);
		
		//OUT << "C6" << ' ' << _2ndByteHex.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0xC9);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2);
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//Next byte will contain immd
		Utility::Format16Bit(IMMD8);
		//OUT << ' ' << IMMD8.substr(2, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));

	}
	else
	{
		return Error::LOG("Invalid [EXP] @MOV_CASE_3\n");
	}
	return true;
}

bool ProgramLoader::MOV_CASE_4(std::string& MEM, std::string& IMMD16)
{
	//Case-4:[]/W[], immd16
	//As there is no register so reg code will be 000
	//1st Byte wiil C7
	const std::string& fExp = Utility::ExpressionForModRM(MEM);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

		Byte B2 = (info.mod << 6) | info.rm;//Reg-Code is 000 already
		//std::string _2ndByteHex = Converter::DecToHex(B2);
		
		//OUT << "C7" << ' ' << _2ndByteHex.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0xC7);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2);
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//Next byte will contain immd
		Utility::Format16Bit(IMMD16);
		//OUT << ' ' << IMMD16.substr(2, 2) << ' ' << IMMD16.substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD16.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD16.substr(0, 2)));
	}
	else
	{
		return Error::LOG("Invalid [EXP] @MOV_CASE_4\n");
	}
	return true;
}

bool ProgramLoader::MOV_CASE_5(std::string& MEM16, std::string& IMMD8)
{
	//Case-5:W[], immd8
	//As Destination is word so immd8 will move as immd16
	//As there is no register so reg code will be 000
	//1st Byte wiil C7
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | info.rm;
		//Reg-Code is 000 already
		//std::string _2ndByteHex = Converter::DecToHex(B2);
		
		//OUT << "C7" << ' ' << _2ndByteHex.substr(0, 2);

		Program[CurrInsIndex].MachineCode.push_back(0xC7);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2);
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//Next byte will contain immd
		Utility::Format16Bit(IMMD8);
		//OUT << ' ' << IMMD8.substr(2, 2) << ' ' << IMMD8.substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(0, 2)));
	}
	else
	{
		return Error::LOG("Invalid [EXP] @MOV_CASE_5\n");
	}
	return true;
}

bool ProgramLoader::MOV_CASE_6(std::string& REG8_D, std::string& REG8_S)
{
	//Case-6: REG8, REG8
	//[Byte-1]Opcde(6)-d(1)-w(1) => 100010-1-0 => 8A
	//[Byte-2]mod(2)-reg(3)-r/m(3) => 11-Reg_CODE(first)-Reg_Code(second)

	Byte B2 = 0b11000000 | (REG_CODE.find(REG8_D)->second << 3) | REG_CODE.find(REG8_S)->second;
	//const std::string& _2ndByteHex = Converter::DecToHex(B2);
	//OUT << "8A" << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0x8A);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::MOV_CASE_7(std::string& REG16_D, std::string& REG16_S)
{
	//Case-7: REG16, REG16
	//Opcode(6)-d(1)-w(1) => 100010-1-1 => 8B
	//mod(2)-reg(3)-r/m(3) => 11-Reg_CODE(first)-Reg_Code(second)

	Byte B2 = 0b11000000 | (REG_CODE.find(REG16_D)->second << 3) | REG_CODE.find(REG16_S)->second;
	//const std::string& _2ndByteHex = Converter::DecToHex(B2);
	//OUT << "8B" << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0x8B);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::MOV_CASE_8(std::string& REG8, std::string& MEM8)
{
	//Case-8: REG8, []

	/*
		For 8Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-1-0 => 8A
		[*]Special Case when reg is AL and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-0-0 => A0, Second byte of opcode will be data directly
	*/
	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);
	if (onlyDisp && REG8 == REGISTER::AL)
	{
		//Special Case
		Utility::Format16Bit(displacement);
		//OUT << "A0" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';

		Program[CurrInsIndex].MachineCode.push_back(0xA0);
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
	}
	else
	{
		const std::string& fExp = Utility::ExpressionForModRM(MEM8);
		if (MOD_RM.count(fExp))
		{
			//mod(2)-reg(3)-r/m(3) => mod-Reg_CODE(first)-r/m_code
			const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
			Byte B2 = (info.mod << 6) | (REG_CODE.find(REG8)->second << 3) | info.rm;
			//std::string HexB2 = Converter::DecToHex(B2);
			//OUT << "8A" << ' ' << HexB2.substr(0, 2);

			Program[CurrInsIndex].MachineCode.push_back(0x8A);
			Program[CurrInsIndex].MachineCode.push_back(B2);
			
			if(!displacement.empty())
			{
				Utility::Format16Bit(displacement);
				if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
				{
					//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
				}
				else
				{
					//OUT << ' ' << displacement.substr(2, 2) << '\n';
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				}
			}
			//else
			//{
			//	OUT << '\n';
			//}
		}
		else
		{
			return Error::LOG("Invalid [EXP] @MOV_CASE_8\n");
		}
	}

	return true;
}

bool ProgramLoader::MOV_CASE_9(std::string& REG16, std::string& MEM)
{
	//Case-9: REG16, []/W[]
	/*
		For 16Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-1-1 => 8B
		[*]Special Case when reg is AX and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-0-1 => A1, Second byte of opcode will be data directly
	*/
	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);

	if (onlyDisp && REG16 == REGISTER::AX)
	{
		//Special Cases
		Utility::Format16Bit(displacement);
		//OUT << "A1" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0xA1);
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
	}
	else
	{
		const std::string& fExp = Utility::ExpressionForModRM(MEM);
		if (MOD_RM.count(fExp))
		{
			//mod(2)-reg(3)-r/m(3) => mod-Reg_CODE(first)-r/m_code
			const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
			Byte B2 = (info.mod << 6) | (REG_CODE.find(REG16)->second << 3) | info.rm;
			//std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
			//OUT << "8B" << ' ' << _2ndByteHex.substr(0, 2);
			Program[CurrInsIndex].MachineCode.push_back(0x8B);

			if (!displacement.empty())
			{
				Utility::Format16Bit(displacement);
				if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
				{
					//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
				}
				else
				{
					//OUT << ' ' << displacement.substr(2, 2) << '\n';
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				}
			}
			/*else
			{
				OUT << '\n';
			}*/
		}
		else
		{
			return Error::LOG("Invalid [EXP] @MOV_CASE_9\n");
		}
	}

	return true;
}

bool ProgramLoader::MOV_CASE_10(std::string& MEM8, std::string& REG8)
{
	//Case-10: [], REG8
	//For 8Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-0-0 => 88
	//[*]Special Case when reg is AL and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-1-0 => A2, Second byte of opcode will be data directly
	
	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

	if (onlyDisp && REG8 == REGISTER::AL)
	{
		//Special Cases
		Utility::Format16Bit(displacement);
		//OUT << "A2" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0xA2);
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
	}
	else
	{
		const std::string& fExp = Utility::ExpressionForModRM(MEM8);
		if (MOD_RM.count(fExp))
		{
			//mod(2)-reg(3)-r/m(3) => mod-Reg_CODE(first)-r/m_code
			const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

			Byte B2 = (info.mod << 6) | (REG_CODE.find(REG8)->second << 3) | info.rm;

			//std::string _2ndByteHex = Converter::DecToHex(_2ndByte);

			//OUT << "88" << ' ' << _2ndByteHex.substr(0, 2);

			Program[CurrInsIndex].MachineCode.push_back(0x88);
			Program[CurrInsIndex].MachineCode.push_back(B2);

			
			if (!displacement.empty())
			{
				Utility::Format16Bit(displacement);
				if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
				{
					//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
				}
				else
				{
					//OUT << ' ' << displacement.substr(2, 2) << '\n';
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				}
			}
			/*else
			{
				OUT << '\n';
			}*/
		}
		else
		{
			return Error::LOG("Invalid [EXP] @MOV_CASE_10\n");
		}
	}
	return true;
}

bool ProgramLoader::MOV_CASE_11(std::string& MEM, std::string& REG16)
{
	//Case-11: []/W[], REG16
	//For 16Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-0-1 => 89
	//[*]Special Case when reg is AX and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-1-1 => A3, Second byte of opcode will be data directly

	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);

	if (onlyDisp && REG16 == REGISTER::AX)
	{
		//Special Cases
		Utility::Format16Bit(displacement);
		//OUT << "A3" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0xA3);
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
	}
	else
	{
		const std::string& fExp = Utility::ExpressionForModRM(MEM);
		if (MOD_RM.count(fExp))
		{
			//mod(2)-reg(3)-r/m(3) => mod-Reg_CODE(first)-r/m_code
			const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

			Byte B2 = (info.mod << 6) | (REG_CODE.find(REG16)->second << 3) | info.rm;

			//std::string _2ndByteHex = Converter::DecToHex(_2ndByte);

			//OUT << "89" << ' ' << _2ndByteHex.substr(0, 2);

			Program[CurrInsIndex].MachineCode.push_back(0x89);
			Program[CurrInsIndex].MachineCode.push_back(B2);

			if (!displacement.empty())
			{
				Utility::Format16Bit(displacement);
				if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
				{
					//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
				}
				else
				{
					//OUT << ' ' << displacement.substr(2, 2) << '\n';
					Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				}
			}
			/*else
			{
				OUT << '\n';
			}*/
		}
		else
		{
			return Error::LOG("Invalid [EXP] @MOV_CASE_11\n");
		}
	}

	return true;
}

bool ProgramLoader::MOV_CASE_12(std::string& SREG, std::string& REG16)
{
	//Case-12: SREG, REG16
	if (SREG == REGISTER::CS) { return Error::LOG("Cs can't be modified directly\n"); }
	//Second Byte => xx0sregxxx =>mod(2)-0-sreg(2)-rm(3)
	const MOD_RM_INFO& info = MOD_RM.find(REG16)->second;
	Byte B2 = (info.mod << 6) | (REG_CODE.find(SREG)->second << 3) | info.rm;

	//std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
	//OUT << "8E" << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0x8E);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::MOV_CASE_13(std::string& SREG, std::string& MEM)
{
	//Case-13: SREG, []/W[]

	if (SREG == REGISTER::CS) { return Error::LOG("Cs can't be modified directly\n"); }

	//Second Byte => xx0sregxxx =>mod(2)-0-sreg(2)-rm(3)
	const std::string& fExp = Utility::ExpressionForModRM(MEM);
	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | (REG_CODE.find(SREG)->second << 3) | info.rm;

		//std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
		//OUT << "8E" << ' ' << _2ndByteHex.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0x8E);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @MOV_CASE_13\n");
	}
	return true;
}

bool ProgramLoader::MOV_CASE_14(std::string& REG16, std::string& SREG)
{
	//Case-14: REG16, SREG
	//Second Byte => xx0sregxxx =>mod(2)-0-sreg(2)-rm(3)
	const MOD_RM_INFO& info = MOD_RM.find(REG16)->second;
	Byte B2 = (info.mod << 6) | (REG_CODE.find(SREG)->second << 3) | info.rm;
	//std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
	//OUT << "8C" << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0x8C);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::MOV_CASE_15(std::string& MEM, std::string& SREG)
{
	//Case-15: []/W[], SREG
	//Second Byte => xx0sregxxx =>mod(2)-0-sreg(2)-rm(3)

	const std::string& fExp = Utility::ExpressionForModRM(MEM);
	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | (REG_CODE.find(SREG)->second << 3) | info.rm;

		//std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
		//OUT << "8C" << ' ' << _2ndByteHex.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0x8C);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid[EXP] @MOV_CASE_15\n");
	}
	return true;

}

bool ProgramLoader::MOV(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 2))
	{
		return Error::LOG("Expected 2 Operands @MOV", Program[CurrInsIndex].LineNumber);
	}

	std::string OP1 = operand.first;
	std::string OP2 = operand.second;
	
	
	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-1:MOV REG8, immd8
		return MOV_CASE_1(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-2:MOV REG16, immd16/immd8
		return MOV_CASE_2(OP1, OP2);
	}
	else if(Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-3:[], immd8
		return MOV_CASE_3(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::WORD)
	{
		//Case-4:[]/W[], immd16
		return MOV_CASE_4(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-5:W[], immd8
		return MOV_CASE_5(OP1, OP2);
	}
	else if(Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
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
	return Error::LOG("Wrong Syntax @ MOV", Program[CurrInsIndex].LineNumber);
}

/*<------------------------XCHG------------------->*/

bool ProgramLoader::XCHG_CASE_1(std::string& REG8_D, std::string& REG8_S)
{
	//Case-1 REG8, REG8
	//86 / r	XCHG r8, r / m8
	const MOD_RM_INFO& info = MOD_RM.find(REG8_S)->second;
	Byte B2 = (info.mod << 6) | (REG_CODE.find(REG8_D)->second << 3) | info.rm;
	//const std::string HexB2 = Converter::DecToHex(B2).substr(0, 2);
	//OUT << "86 " << HexB2 << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0x86);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::XCHG_CASE_2(std::string& MEM8, std::string& REG8)
{
	//Case-2 [], REG8
	//86 /r	XCHG r/m8, r8

	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

	const std::string& fExp = Utility::ExpressionForModRM(MEM8);

	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG8)->second << 3) | info.rm;

		//std::string HexB2 = Converter::DecToHex(B2).substr(0, 2);

		//OUT << "86 " << HexB2;

		Program[CurrInsIndex].MachineCode.push_back(0x86);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @XCHG_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::XCHG_CASE_3(std::string& REG8, std::string& MEM8)
{
	//Case-3 REG8, []
	//86 / r	XCHG r8, r / m8

	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

	const std::string& fExp = Utility::ExpressionForModRM(MEM8);

	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG8)->second << 3) | info.rm;

		//std::string HexB2 = Converter::DecToHex(B2).substr(0, 2);

		//OUT << "86 " << HexB2;

		Program[CurrInsIndex].MachineCode.push_back(0x86);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @XCHG_CASE_3\n");
	}
	return true;
}

bool ProgramLoader::XCHG_CASE_4(std::string& REG16_D, std::string& REG16_S)
{
	//Case-4 REG16, REG16
	//SPECIAL CASE AX, REG16 OR REG16, AX => 0x80 + REG_CODE(REG)
	if (REG16_D == REGISTER::AX)
	{
		//Byte B = 0x90 + REG_CODE.find(REG16_S)->second;
		//OUT << Converter::DecToHex(B).substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0x90 + REG_CODE.find(REG16_S)->second);
	}
	else if (REG16_S == REGISTER::AX)
	{
		//Byte B = 0x90 + REG_CODE.find(REG16_D)->second;
		//OUT << Converter::DecToHex(B).substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0x90 + REG_CODE.find(REG16_D)->second);
	}
	else
	{
		//87 /r	XCHG r16, r/m16
		const MOD_RM_INFO& info = MOD_RM.find(REG16_S)->second;
		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG16_D)->second << 3) | info.rm;
		//const std::string HexB2 = Converter::DecToHex(B2).substr(0, 2);
		//OUT << "87 " << HexB2 << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0x87);
		Program[CurrInsIndex].MachineCode.push_back(B2);
	}
	return true;
}

bool ProgramLoader::XCHG_CASE_5(std::string& REG16, std::string& MEM)
{
	///Case-5 REG16, []/W[]
	//87 /r	XCHG r16, r/m16

	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);

	const std::string& fExp = Utility::ExpressionForModRM(MEM);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG16)->second << 3) | info.rm;

		//std::string HexB2 = Converter::DecToHex(B2).substr(0, 2);

		//OUT << "87 " << HexB2;

		Program[CurrInsIndex].MachineCode.push_back(0x87);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @XCHG_CASE_5\n");
	}
	return true;
}

bool ProgramLoader::XCHG_CASE_6(std::string& MEM, std::string& REG16)
{
	//Case-6 []/W[], REG16
	//87 /r	XCHG r/m16, r16
	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);

	const std::string& fExp = Utility::ExpressionForModRM(MEM);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG16)->second << 3) | info.rm;

		//std::string HexB2 = Converter::DecToHex(B2).substr(0, 2);

		//OUT << "87 " << HexB2;

		Program[CurrInsIndex].MachineCode.push_back(0x87);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @XCHG_CASE_6\n");
	}
	return true;
}

bool ProgramLoader::XCHG(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 2))
	{
		return Error::LOG("Expected No Operand @XCHG\n");
	}
	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1 REG8, REG8
		return XCHG_CASE_1(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-2 [], REG8
		if (Utility::IsByteMemory(OP1))
		{
			return XCHG_CASE_2(OP1, OP2);
		}
		else
		{
			return Error::LOG("Both operand must be of same size\n");
		}
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-3 REG8, []
		if (Utility::IsByteMemory(OP2))
		{
			return XCHG_CASE_3(OP1, OP2);
		}
		else
		{
			return Error::LOG("Both operand must be of same size\n");
		}
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4 REG16, REG16
		//SPECIAL CASE AX, REG16 OR REG16, AX
		return XCHG_CASE_4(OP1, OP2);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5 REG16, []/W[]
		return XCHG_CASE_5(OP1, OP2);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6 []/W[], REG16
		return XCHG_CASE_6(OP1, OP2);
	}

	return Error::LOG("Invalid Syntax @XCHG\n");
}
/*<-------------------------------------AAACOSSX-------------------------------------->*/

bool ProgramLoader::AAACOSSX_CASE_1(std::string& REG8_D, std::string& REG8_S, const Byte OFFSET, const Byte REG)
{	
	//Case-1: REG8, REG8
	//1st Byte => 02 + Offset (Depending upon Mnemonic)
	//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(OP1)]-[reg-code(OP2)]
	Byte B1 = 0x02 + OFFSET;
	Byte B2 = 0b11000000 | (REG_CODE.find(REG8_D)->second << 3) | REG_CODE.find(REG8_S)->second;
	//const std::string& hB1 = Converter::DecToHex(B1);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(B1);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_2(std::string& REG8, std::string& MEM8, const Byte OFFSET, const Byte REG)
{
	//Case-2: REG8, []
	//1st Byte => 02
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(OP1)]-[RM]
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B1 = 0x02 + OFFSET;
		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG8)->second << 3) | info.rm;

		//const std::string& hB1 = Converter::DecToHex(B1);
		//const std::string& hB2 = Converter::DecToHex(B2);

		//OUT << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(B1);
		Program[CurrInsIndex].MachineCode.push_back(B2);
		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_2\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_3(std::string& MEM8, std::string& REG8, const Byte OFFSET, const Byte REG)
{
	//Case-3: [], REG8
	//1st Byte => 00
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(OP2)]-[RM]
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B1 = 0x00 + OFFSET;
		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG8)->second << 3) | info.rm;

		//const std::string& hB1 = Converter::DecToHex(B1);
		//const std::string& hB2 = Converter::DecToHex(B2);

		Program[CurrInsIndex].MachineCode.push_back(B1);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//OUT << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_3\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_4(std::string& REG16_D, std::string& REG16_S, const Byte OFFSET, const Byte REG)
{
	//Case-4: REG16, REG16
	//1st Byte => 03
	//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(OP1)]-[reg-code(OP2)]
	Byte B1 = 0x03 + OFFSET;
	Byte B2 = 0b11000000 | (REG_CODE.find(REG16_D)->second << 3) | REG_CODE.find(REG16_S)->second;
	//const std::string& hB1 = Converter::DecToHex(B1);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(B1);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_5(std::string& REG16, std::string& MEM, const Byte OFFSET, const Byte REG)
{
	//Case-5: REG16, []/W[]
	//1st Byte => 03
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(OP1)]-[RM]
	const std::string& fExp = Utility::ExpressionForModRM(MEM);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B1 = 0x03 + OFFSET;
		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG16)->second << 3) | info.rm;

		/*const std::string& hB1 = Converter::DecToHex(B1);
		const std::string& hB2 = Converter::DecToHex(B2);*/

		Program[CurrInsIndex].MachineCode.push_back(B1);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);

		//OUT << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//else
		//{
		//	OUT << '\n';
		//}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_5\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_6(std::string& MEM, std::string& REG16, const Byte OFFSET, const Byte REG)
{
	//Case-6: []/W[], REG16
	//1st Byte => 01
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(OP2)]-[RM]
	const std::string& fExp = Utility::ExpressionForModRM(MEM);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B1 = 0x01 + OFFSET;
		Byte B2 = (info.mod << 6) | (REG_CODE.find(REG16)->second << 3) | info.rm;

		//const std::string& hB1 = Converter::DecToHex(B1);
		//const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);

		//OUT << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//else
		//{
		//	OUT << '\n';
		//}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_6\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_7(std::string& MEM8, std::string& IMMD8, const Byte OFFSET, const Byte REG)
{
	//Case-7: [], IMMD8
	//1st Byte => 80
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(000)]-[RM]
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | REG | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		Program[CurrInsIndex].MachineCode.push_back(0x80);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//OUT << "80" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}

		//Next byte will contain immd
		Utility::Format16Bit(IMMD8);
		/*OUT << ' ' << IMMD8.substr(2, 2) << '\n';*/
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));

	}
	else
	{
		return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_7\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_8(std::string& MEM, std::string& IMMD16, const Byte OFFSET, const Byte REG)
{
	//Case-8: []/W[], IMMD16
	//1st Byte => 81
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(000)]-[RM]
	const std::string& fExp = Utility::ExpressionForModRM(MEM);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | REG | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM, displacement);

		//OUT << "81" << ' ' << hB2.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0x81);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}

		//Next byte will contain immd
		Utility::Format16Bit(IMMD16);
		//OUT << ' ' << IMMD16.substr(2, 2) << ' ' << IMMD16.substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD16.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD16.substr(0, 2)));

	}
	else
	{
		return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_8\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_9(std::string& REG8, std::string& IMMD8, const Byte OFFSET, const Byte REG)
{
	//Case-9: REG8, IMMD8
	//[*] Special Case when reg is AL=> 1st Byte [04]   2nd Byte [immd8]
	if (REG8 == REGISTER::AL)
	{
		Byte B1 = 0x04 + OFFSET;
		//const std::string& hB1 = Converter::DecToHex(B1);
		Utility::Format16Bit(IMMD8);
		//OUT << hB1.substr(0, 2) << ' ' << IMMD8.substr(2, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(B1);
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));
	}
	else
	{
		//1st Byte => 80
		//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(000)]-[reg-code(OP1)] OR use MOD_RM
		if (MOD_RM.count(REG8))
		{
			const MOD_RM_INFO& info = MOD_RM.find(REG8)->second;
			Byte B2 = (info.mod << 6) | REG | info.rm;

			//const std::string& hB2 = Converter::DecToHex(B2);

			//OUT << "80" << ' ' << hB2.substr(0, 2);
			Program[CurrInsIndex].MachineCode.push_back(0x80);
			Program[CurrInsIndex].MachineCode.push_back(B2);

			//Next byte will contain immd
			Utility::Format16Bit(IMMD8);
			//OUT << ' ' << IMMD8.substr(2, 2) << '\n';
			Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));

		}
		else 
		{
			return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_9\n");
		}
	}
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_10(std::string& REG16, std::string& IMMD16, const Byte OFFSET, const Byte REG)
{
	///Case-10: REG16, IMMD16
	/*[*] Special Case when reg is AX=> 1st Byte [05]   2nd Byte [immd16] */
	if (REG16 == REGISTER::AX)
	{
		Byte B1 = 0x05 + OFFSET;
		//const std::string& hB1 = Converter::DecToHex(B1);
		Utility::Format16Bit(IMMD16);
		//OUT << hB1.substr(0, 2) << ' ' << IMMD16.substr(2, 2) << ' ' << IMMD16.substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(B1);
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD16.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD16.substr(0, 2)));
	}
	else
	{
		//1st Byte => 81
		//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(000)]-[reg-code(OP1)] OR use MOD_RM
		if (MOD_RM.count(REG16))
		{
			const MOD_RM_INFO& info = MOD_RM.find(REG16)->second;
			Byte B2 = (info.mod << 6) | REG | info.rm;

			//const std::string& hB2 = Converter::DecToHex(B2);

			//OUT << "81" << ' ' << hB2.substr(0, 2);
			Program[CurrInsIndex].MachineCode.push_back(0x81);
			Program[CurrInsIndex].MachineCode.push_back(B2);

			//Next byte will contain immd
			Utility::Format16Bit(IMMD16);
			//OUT << ' ' << IMMD16.substr(2, 2) << ' ' << IMMD16.substr(0, 2) << '\n';
			Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD16.substr(2, 2)));
			Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD16.substr(0, 2)));
		}
		else
		{
			return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_10\n");
		}
	}
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_11(std::string& REG16, std::string& IMMD8, const Byte OFFSET, const Byte REG)
{
	//Case-11: REG16, IMMD8
	//[*] Special Case when reg is AX=> 1st Byte [05]   2nd Byte [immd8 as immd16]
	if (REG16 == REGISTER::AX)
	{
		Byte B1 = 0x05 + OFFSET;
		//const std::string& hB1 = Converter::DecToHex(B1);
		Utility::Format16Bit(IMMD8);
		//OUT << hB1.substr(0, 2) << ' ' << IMMD8.substr(2, 2) << ' ' << IMMD8.substr(0, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(B1);
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(0, 2)));
	}
	else
	{
		//1st Byte => 83
		//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(000)]-[reg-code(OP1)] OR use MOD_RM
		if (MOD_RM.count(REG16))
		{
			const MOD_RM_INFO& info = MOD_RM.find(REG16)->second;
			Byte B2 = (info.mod << 6) | REG | info.rm;

			//const std::string& hB2 = Converter::DecToHex(B2);

			//OUT << "83" << ' ' << hB2.substr(0, 2);

			Program[CurrInsIndex].MachineCode.push_back(0x83);
			Program[CurrInsIndex].MachineCode.push_back(B2);

			//Next byte will contain immd
			Utility::Format16Bit(IMMD8);
			//OUT << ' ' << IMMD8.substr(2, 2) << '\n';
			Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));
		}
		else
		{
			return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_11\n");
		}
	}
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_12(std::string& MEM16, std::string& IMMD8, const Byte OFFSET, const Byte REG)
{
	//Case-12: W[], IMMD8
	//1st Byte => 83
	//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(000)]-[reg-code(OP1)] OR use MOD_RM
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | REG | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		//OUT << "83" << ' ' << hB2.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0x83);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}

		//Next byte will contain immd
		Utility::Format16Bit(IMMD8);
		//OUT << ' ' << IMMD8.substr(2, 2) << '\n';
		Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(IMMD8.substr(2, 2)));
	}
	else
	{
		return Error::LOG("Invalid [EXP] @ AAACOSSX_CASE_11\n");
	}
	return true;
}

bool ProgramLoader::AAACOSSX(const Operand& operand, const Byte OFFSET, const Byte REG)
{

	if (!Utility::IsValidOperandCount(operand, 2))
	{
		return Error::LOG("Expected 2 Operands @AAACOSSX", Program[CurrInsIndex].LineNumber);
	}

	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-1: REG8, REG8
		return AAACOSSX_CASE_1(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidMemory(OP2) && Utility::IsByteMemory(OP2))
	{
		//Case-2: REG8, []
		return AAACOSSX_CASE_2(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-3: [], REG8
		return AAACOSSX_CASE_3(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-4: REG16, REG16
		return AAACOSSX_CASE_4(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidMemory(OP2))
	{
		//Case-5: REG16, []/W[]
		return AAACOSSX_CASE_5(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		//Case-6: []/W[], REG16
		return AAACOSSX_CASE_6(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-7: [], IMMD8
		return AAACOSSX_CASE_7(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::WORD)
	{
		//Case-8: []/W[], IMMD16
		return AAACOSSX_CASE_8(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-9: REG8, IMMD8
		return AAACOSSX_CASE_9(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::WORD)
	{
		//Case-10: REG16, IMMD16
		return AAACOSSX_CASE_10(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-11: REG16, IMMD8
		return AAACOSSX_CASE_11(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == HEX_SIZE::BYTE)
	{
		//Case-12: W[], IMMD8
		return AAACOSSX_CASE_12(OP1, OP2, OFFSET, REG);
	}
	
	return Error::LOG("Wrong Syntax @ AAACOSSX\n");
}

bool ProgramLoader::ADD(const Operand& operand)
{
	return AAACOSSX(operand, 0x00, 0b00000000) ? true : Error::LOG("Execution Failed @ ADD\n");
}

bool ProgramLoader::ADC(const Operand& operand)
{
	return AAACOSSX(operand, 0x10, 0b00010000) ? true : Error::LOG("Execution Failed @ ADC\n");
}

bool ProgramLoader::AND(const Operand& operand)
{
	return AAACOSSX(operand, 0x20, 0b00100000) ? true : Error::LOG("Execution Failed @ AND\n");
}

bool ProgramLoader::CMP(const Operand& operand)
{
	return AAACOSSX(operand, 0x38, 0b00111000) ? true : Error::LOG("Execution Failed @ CMP\n");
}

bool ProgramLoader::OR(const Operand& operand)
{
	return AAACOSSX(operand, 0x08, 0b00001000) ? true : Error::LOG("Execution Failed @ OR\n");
}

bool ProgramLoader::SBB(const Operand& operand)
{
	return AAACOSSX(operand, 0x18, 0b00011000) ? true : Error::LOG("Execution Failed @ SBB\n");
}

bool ProgramLoader::SUB(const Operand& operand)
{
	return AAACOSSX(operand, 0x28, 0b00101000) ? true : Error::LOG("Execution Failed @ SUB\n");
}

bool ProgramLoader::XOR(const Operand& operand)
{
	return AAACOSSX(operand, 0x30, 0b00110000) ? true : Error::LOG("Execution Failed @ XOR\n");
}

/*<-------------------------------------MUL-------------------------------------->*/

bool ProgramLoader::MUL_CASE_1(std::string& MEM8)
{
	//Case-1: MUL []
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00100000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		//OUT << "F6" << ' ' << hB2.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0xF6);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @MUL_CASE_1\n");
	}
	return true;
}

bool ProgramLoader::MUL_CASE_2(std::string& MEM16)
{
	//Case-2: MUL W[]
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00100000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		//OUT << "F7" << ' ' << hB2.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0xF7);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @MUL_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::MUL_CASE_3(std::string& REG8)
{
	//Case-3: MUL REG8
	Byte B2 = 0b11100000 | REG_CODE.find(REG8)->second;
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF6);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::MUL_CASE_4(std::string& REG16)
{
	//Case-4: MUL REG16
	Byte B2 = 0b11100000 | REG_CODE.find(REG16)->second;
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF7);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::MUL(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand @MUL\n");
	}

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

	return Error::LOG("Syntax Error @MUL\n");
}


/*<-------------------------------------IMUL-------------------------------------->*/

bool ProgramLoader::IMUL_CASE_1(std::string& MEM8)
{
	//Case-1: IMUL []
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00101000 | info.rm;
		//const std::string& hB2 = Converter::DecToHex(B2);

		//OUT << "F6" << ' ' << hB2.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0xF6);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//else
		//{
		//	OUT << '\n';
		//}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @IMUL_CASE_1\n");
	}
	return true;
}

bool ProgramLoader::IMUL_CASE_2(std::string& MEM16)
{
	//Case-2: IMUL W[]
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00101000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		//OUT << "F7" << ' ' << hB2.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0xF7);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//else
		//{
		//	OUT << '\n';
		//}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @MUL_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::IMUL_CASE_3(std::string& REG8)
{
	//Case-3: IMUL REG8
	Byte B2 = 0b11101000 | REG_CODE.find(REG8)->second;
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF6);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::IMUL_CASE_4(std::string& REG16)
{
	//Case-4: IMUL REG16
	Byte B2 = 0b11101000 | REG_CODE.find(REG16)->second;
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF7);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::IMUL(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand @IMUL\n");
	}

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

	return Error::LOG("Syntax Error @IMUL\n");
}


/*<-------------------------------------DIV-------------------------------------->*/

bool ProgramLoader::DIV_CASE_1(std::string& MEM8)
{
	//Case-1: DIV []
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00110000 | info.rm;
		//const std::string& hB2 = Converter::DecToHex(B2);

		//OUT << "F6" << ' ' << hB2.substr(0, 2);
		Program[CurrInsIndex].MachineCode.push_back(0xF6);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @DIV_CASE_1\n");
	}
	return true;
}

bool ProgramLoader::DIV_CASE_2(std::string& MEM16)
{
	//Case-2: DIV W[]
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00110000 | info.rm;
		//const std::string& hB2 = Converter::DecToHex(B2);

		//OUT << "F7" << ' ' << hB2.substr(0, 2);

		Program[CurrInsIndex].MachineCode.push_back(0xF7);
		Program[CurrInsIndex].MachineCode.push_back(B2);
		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);


		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @DIV_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::DIV_CASE_3(std::string& REG8)
{
	//Case-3: DIV REG8
	Byte B2 = 0b11110000 | (REG_CODE.find(REG8)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF6);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::DIV_CASE_4(std::string& REG16)
{
	//Case-4: DIV REG16
	Byte B2 = 0b11110000 | (REG_CODE.find(REG16)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF7);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::DIV(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand @DIV\n");
	}

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

	return Error::LOG("Syntax Error @DIV\n");
}


/*<-------------------------------------IDIV-------------------------------------->*/

bool ProgramLoader::IDIV_CASE_1(std::string& MEM8)
{
	//Case-1: IDIV []
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00111000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		Program[CurrInsIndex].MachineCode.push_back(0xF6);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//OUT << "F6" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @IDIV_CASE_1\n");
	}
	return true;
}

bool ProgramLoader::IDIV_CASE_2(std::string& MEM16)
{
	//Case-2: IDIV W[]
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00111000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);
		Program[CurrInsIndex].MachineCode.push_back(0xF7);
		Program[CurrInsIndex].MachineCode.push_back(B2);
		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		//OUT << "F7" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @IDIV_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::IDIV_CASE_3(std::string& REG8)
{
	//Case-3: IDIV REG8
	Byte B2 = 0b11111000 | (REG_CODE.find(REG8)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF6);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::IDIV_CASE_4(std::string& REG16)
{
	//Case-4: IDIV REG16
	Byte B2 = 0b11111000 | (REG_CODE.find(REG16)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF7);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::IDIV(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand @IDIV\n");
	}

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

	return Error::LOG("Syntax Error @IDIV\n");
}

/*<------------------------------NEG---------------------------------------------------->*/

bool ProgramLoader::NEG_CASE_1(std::string& MEM8)
{
	//Case-1: NEG []
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00011000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);
		Program[CurrInsIndex].MachineCode.push_back(0xF6);
		Program[CurrInsIndex].MachineCode.push_back(B2);
		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//OUT << "F6" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//else
		//{
		//	OUT << '\n';
		//}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @NEG_CASE_1\n");
	}
	return true;

}

bool ProgramLoader::NEG_CASE_2(std::string& MEM16)
{
	//Case-2: NEG W[]
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6)| 0b00011000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);
		Program[CurrInsIndex].MachineCode.push_back(0xF7);
		Program[CurrInsIndex].MachineCode.push_back(B2);
		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		//OUT << "F7" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @NEG_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::NEG_CASE_3(std::string& REG8)
{
	//Case-3: NEG REG8
	Byte B2 = 0b11011000 | (REG_CODE.find(REG8)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF6);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::NEG_CASE_4(std::string& REG16)
{
	//Case-4: NEG REG16
	Byte B2 = 0b11011000 | (REG_CODE.find(REG16)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF7);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::NEG(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand @NEG\n");
	}

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

	return Error::LOG("Syntax Error @NEG\n");
}

/*<-------------------------------NOT-------------------------------------------------->*/

bool ProgramLoader::NOT_CASE_1(std::string& MEM8)
{
	//Case-1: NOT []
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00010000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		Program[CurrInsIndex].MachineCode.push_back(0xF6);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//OUT << "F6" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//else
		//{
		//	OUT << '\n';
		//}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @NEG_CASE_1\n");
	}
	return true;

}

bool ProgramLoader::NOT_CASE_2(std::string& MEM16)
{
	//Case-2: NOT W[]
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00010000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);
		Program[CurrInsIndex].MachineCode.push_back(0xF7);
		Program[CurrInsIndex].MachineCode.push_back(B2);
		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		//OUT << "F7" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @NEG_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::NOT_CASE_3(std::string& REG8)
{
	//Case-3: NOT REG8
	Byte B2 = 0b11010000 | (REG_CODE.find(REG8)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF6);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::NOT_CASE_4(std::string& REG16)
{
	//Case-4: NOT REG16
	Byte B2 = 0b11010000 | (REG_CODE.find(REG16)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xF7);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::NOT(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand @NOT\n");
	}

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

	return Error::LOG("Syntax Error @NOT\n");
}

/*<-------------------------------------------DEC------------------------------->*/

bool ProgramLoader::DEC_CASE_1(std::string& MEM8)
{
	//Case-1: DEC []
	//$FE, xx001xxx(ModR / M byte)
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00001000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		Program[CurrInsIndex].MachineCode.push_back(0xFE);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//OUT << "FE" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @NEG_CASE_1\n");
	}
	return true;

}

bool ProgramLoader::DEC_CASE_2(std::string& MEM16)
{
	//Case-2: DEC W[]
	//$FF, xx001xxx(ModR / M byte)
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | 0b00001000 | info.rm;

		//const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		//OUT << "FF" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @NEG_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::DEC_CASE_3(std::string& REG8)
{
	//Case-3: DEC REG8
	//$FE, xx001xxx(ModR / M byte)
	Byte B2 = 0b11001000 | (REG_CODE.find(REG8)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "FE" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xFE);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::DEC_CASE_4(std::string& REG16)
{
	//Case-4: DEC REG16
	//$48 + reg16 code
	Program[CurrInsIndex].MachineCode.push_back(0x48 + REG_CODE.find(REG16)->second);
	//const std::string& hB1 = Converter::DecToHex(B1);
	//OUT << hB1.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::DEC(const Operand& operand)
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

bool ProgramLoader::INC_CASE_1(std::string& MEM8)
{
	//Case-1: INC []
	//$FE, xx000xxx(ModR / M byte)
	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | info.rm;
		//const std::string& hB2 = Converter::DecToHex(B2);
		Program[CurrInsIndex].MachineCode.push_back(0xFE);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//OUT << "FE" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		/*else
		{
			OUT << '\n';
		}*/
	}
	else
	{
		return Error::LOG("Invalid [EXP] @NEG_CASE_1\n");
	}
	return true;

}

bool ProgramLoader::INC_CASE_2(std::string& MEM16)
{
	//Case-2: INC W[]
	//$FF, xx000xxx(ModR / M byte)
	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | info.rm;
		//const std::string& hB2 = Converter::DecToHex(B2);
		Program[CurrInsIndex].MachineCode.push_back(0xFF);
		Program[CurrInsIndex].MachineCode.push_back(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		//OUT << "FF" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
		//else
		//{
		//	OUT << '\n';
		//}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @NEG_CASE_2\n");
	}
	return true;
}

bool ProgramLoader::INC_CASE_3(std::string& REG8)
{
	//Case-3: INC REG8
	//$FE, xx000xxx(ModR / M byte)
	Byte B2 = 0b11000000 | (REG_CODE.find(REG8)->second);
	//const std::string& hB2 = Converter::DecToHex(B2);
	//OUT << "FE" << ' ' << hB2.substr(0, 2) << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xFE);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::INC_CASE_4(std::string& REG16)
{
	//Case-4: INC REG16
	//$40 + reg16 code
	Program[CurrInsIndex].MachineCode.push_back(0x40 + REG_CODE.find(REG16)->second);
	//const std::string& hB1 = Converter::DecToHex(B1);
	//OUT << hB1.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::INC(const Operand& operand)
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

/*<-------------------------DAA------------------------------->*/

bool ProgramLoader::DAA(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 0))
	{
		return Error::LOG("Expected 1 Operand @DAA\n");
	}
	//OUT << "27\n";
	Program[CurrInsIndex].MachineCode.push_back(0x27);
	return true;
}

/*<-----------------------------------SHL---------------------------->*/

bool ProgramLoader::ROTATE_SHIFT_CASE_1(std::string& REG8, std::string& IMMD8, Byte REG)
{
	//Case-1 REG8, IMMD8
	//D0, xxREGxxx => IMMD8 Time
	Byte B2 = 0b11000000 | REG | REG_CODE.find(REG8)->second;
	//const std::string& HexB2 = (Converter::DecToHex(B2)).substr(0, 2);
	int count = Converter::HexToDec(IMMD8);
	if (count == 0) { return Error::LOG("IMMD8 can't be 00H\n"); }
	while (count--)
	{
		//OUT << "D0 " << HexB2 << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0xD0);
		Program[CurrInsIndex].MachineCode.push_back(B2);
	}
	return true;
}

bool ProgramLoader::ROTATE_SHIFT_CASE_2(std::string& REG8, Byte REG)
{
	//Case-2 REG8, CL
	//D2, xxREGxxx
	Byte B2 = 0b11000000 | REG | REG_CODE.find(REG8)->second;
	//const std::string& HexB2 = (Converter::DecToHex(B2)).substr(0, 2);
	//OUT << "D2 " << HexB2 << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xD2);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::ROTATE_SHIFT_CASE_3(std::string& REG16, std::string& IMMD8, Byte REG)
{
	//Case-3 REG16, IMMD8
	//D1, xxREGxxx => IMMD8 Time
	Byte B2 = 0b11000000 | REG | REG_CODE.find(REG16)->second;
	//const std::string& HexB2 = (Converter::DecToHex(B2)).substr(0, 2);
	int count = Converter::HexToDec(IMMD8);
	if (count == 0) { return Error::LOG("IMMD8 can't be 00H\n"); }
	while (count--)
	{
		//OUT << "D1 " << HexB2 << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0xD1);
		Program[CurrInsIndex].MachineCode.push_back(B2);
	}
	return true;
}

bool ProgramLoader::ROTATE_SHIFT_CASE_4(std::string& REG16, Byte REG)
{
	//Case-4 REG16, CL
	//D2, xxREGxxx
	Byte B2 = 0b11000000 | REG | REG_CODE.find(REG16)->second;
	//const std::string& HexB2 = (Converter::DecToHex(B2)).substr(0, 2);
	//OUT << "D3 " << HexB2 << '\n';
	Program[CurrInsIndex].MachineCode.push_back(0xD3);
	Program[CurrInsIndex].MachineCode.push_back(B2);
	return true;
}

bool ProgramLoader::ROTATE_SHIFT_CASE_5(std::string& MEM8, std::string& IMMD8, Byte REG)
{
	//Case-5 [], IMMD8
	//D0, xxREGxxx, Disp(if any) => IMMD8 Time

	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

		Byte B2 = (info.mod << 6) | REG | info.rm;
		//const std::string& HexB2 = (Converter::DecToHex(B2)).substr(0, 2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//std::string Dis;

		//if (!displacement.empty())
		//{
		//	Utility::Format16Bit(displacement);
		//	if(onlyDisp || Utility::HexSize(displacement) == SIZE::WORD)
		//	{
		//		Dis = displacement.substr(2, 2) + ' ' + displacement.substr(0, 2);
		//	}
		//	else
		//	{
		//		Dis = displacement.substr(2, 2);
		//	}
		//}

		int count = Converter::HexToDec(IMMD8);
		if (count == 0) { return Error::LOG("IMMD8 can't be 00H\n"); }

		std::vector<Byte> Dis;
		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Dis.push_back(Converter::Dec(displacement.substr(2, 2)));
				Dis.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Dis.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}

		while (count--)
		{
			//OUT << "D0 " << HexB2 << ' ' << Dis << '\n';
			Program[CurrInsIndex].MachineCode.push_back(0xD0);
			Program[CurrInsIndex].MachineCode.push_back(B2);
			if (!Dis.empty())
			{
				for (const Byte x : Dis)
				{
					Program[CurrInsIndex].MachineCode.push_back(x);
				}
			}
		}

	}
	else
	{
		return Error::LOG("Invalid [EXP] @SHIFT_CASE_5\n");
	}
	return true;
}

bool ProgramLoader::ROTATE_SHIFT_CASE_6(std::string& MEM8, Byte REG)
{
	//Case-6 [], CL
	//D2, xxREGxxx, Disp(if any)

	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | REG | info.rm;
		//const std::string& HexB2 = (Converter::DecToHex(B2)).substr(0, 2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//std::string Dis;

		//if (!displacement.empty())
		//{
		//	Utility::Format16Bit(displacement);
		//	if (onlyDisp || Utility::HexSize(displacement) == SIZE::WORD)
		//	{
		//		Dis = displacement.substr(2, 2) + ' ' + displacement.substr(0, 2);
		//	}
		//	else
		//	{
		//		Dis = displacement.substr(2, 2);
		//	}
		//}
		//OUT << "D2 " << HexB2 << ' ' << Dis << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0xD2);
		Program[CurrInsIndex].MachineCode.push_back(B2);
		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @SHIFT_CASE_6\n");
	}
	return true;
}

bool ProgramLoader::ROTATE_SHIFT_CASE_7(std::string& MEM16, std::string& IMMD8, Byte REG)
{
	//Case-7 W[], IMMD8
	//D1, xxREGxxx, Disp(if any) => IMMD8 Time

	const std::string& fExp = Utility::ExpressionForModRM(MEM16);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

		Byte B2 = (info.mod << 6) | REG | info.rm;
		//const std::string& HexB2 = (Converter::DecToHex(B2)).substr(0, 2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM16, displacement);

		//std::string Dis;

		/*if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == SIZE::WORD)
			{
				Dis = displacement.substr(2, 2) + ' ' + displacement.substr(0, 2);
			}
			else
			{
				Dis = displacement.substr(2, 2);
			}
		}*/

		int count = Converter::HexToDec(IMMD8);
		if (count == 0) { return Error::LOG("IMMD8 can't be 00H\n"); }

		std::vector<Byte> Dis;
		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Dis.push_back(Converter::Dec(displacement.substr(2, 2)));
				Dis.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Dis.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}

		while (count--)
		{
			//OUT << "D1 " << HexB2 << ' ' << Dis << '\n';
			Program[CurrInsIndex].MachineCode.push_back(0xD1);
			Program[CurrInsIndex].MachineCode.push_back(B2);
			if (!Dis.empty())
			{
				for (const Byte x : Dis)
				{
					Program[CurrInsIndex].MachineCode.push_back(x);
				}
			}
		}

	}
	else
	{
		return Error::LOG("Invalid [EXP] @SHIFT_CASE_5\n");
	}
	return true;
}

bool ProgramLoader::ROTATE_SHIFT_CASE_8(std::string& MEM8, Byte REG)
{
	//Case-8 W[], CL
	//D3, xxREGxxx, Disp(if any)

	const std::string& fExp = Utility::ExpressionForModRM(MEM8);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = (info.mod << 6) | REG | info.rm;
		//const std::string& HexB2 = (Converter::DecToHex(B2)).substr(0, 2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(MEM8, displacement);

		//std::string Dis;

		/*if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == SIZE::WORD)
			{
				Dis = displacement.substr(2, 2) + ' ' + displacement.substr(0, 2);
			}
			else
			{
				Dis = displacement.substr(2, 2);
			}
		}*/
		//OUT << "D3 " << HexB2 << ' ' << Dis << '\n';
		Program[CurrInsIndex].MachineCode.push_back(0xD3);
		Program[CurrInsIndex].MachineCode.push_back(B2);
		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp || Utility::HexSize(displacement) == HEX_SIZE::WORD)
			{
				//OUT << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(0, 2)));
			}
			else
			{
				//OUT << ' ' << displacement.substr(2, 2) << '\n';
				Program[CurrInsIndex].MachineCode.push_back(Converter::Dec(displacement.substr(2, 2)));
			}
		}
	}
	else
	{
		return Error::LOG("Invalid [EXP] @SHIFT_CASE_6\n");
	}
	return true;
}

bool ProgramLoader::ROTATE_SHIFT(const Operand& operand, Byte REG)
{
	if (!Utility::IsValidOperandCount(operand, 2))
	{
		return Error::LOG("Expected 1 Operand @Roation/Shift\n");
	}

	std::string OP1 = operand.first;
	std::string OP2 = operand.second;
	
	if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-1 REG8, IMMD8
		if (Utility::HexSize(OP2) == HEX_SIZE::BYTE)
		{
			return ROTATE_SHIFT_CASE_1(OP1, OP2, REG);
		}
		else
		{
			return Error::LOG("Only 8 Bit data allowed!\n");
		}
	}
	else if(Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-2 REG8, CL
		if (OP2 == REGISTER::CL)
		{
			return ROTATE_SHIFT_CASE_2(OP1, REG);
		}
		else
		{
			return Error::LOG("Only CL is allowed!\n");
		}
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-3 REG16, IMMD8
		if (Utility::HexSize(OP2) == HEX_SIZE::BYTE)
		{
			return ROTATE_SHIFT_CASE_3(OP1, OP2, REG);
		}
		else
		{
			return Error::LOG("Only 8 Bit data allowed!\n");
		}
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-4 REG16, CL
		if (OP2 == REGISTER::CL)
		{
			return ROTATE_SHIFT_CASE_4(OP1, REG);
		}
		else
		{
			return Error::LOG("Only CL is allowed!\n");
		}
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-5 [], IMMD8
		if (Utility::HexSize(OP2) == HEX_SIZE::BYTE)
		{
			return ROTATE_SHIFT_CASE_5(OP1, OP2, REG);
		}
		else
		{
			return Error::LOG("Only 8 Bit data allowed!\n");
		}
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsByteMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-6 [], CL
		if (OP2 == REGISTER::CL)
		{
			return ROTATE_SHIFT_CASE_6(OP1, REG);
		}
		else
		{
			return Error::LOG("Only CL is allowed!\n");
		}
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::IsValidHex(OP2))
	{
		//Case-7 W[], IMMD8
		if (Utility::HexSize(OP2) == HEX_SIZE::BYTE)
		{
			return ROTATE_SHIFT_CASE_7(OP1, OP2, REG);
		}
		else
		{
			return Error::LOG("Only 8 Bit data allowed!\n");
		}
	}
	else if (Utility::IsValidMemory(OP1) && Utility::IsWordMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		//Case-8 W[], CL
		if (OP2 == REGISTER::CL)
		{
			return ROTATE_SHIFT_CASE_8(OP1, REG);
		}
		else
		{
			return Error::LOG("Only CL is allowed!\n");
		}
	}
	return false;
}

bool ProgramLoader::SHL(const Operand& operand)
{
	return ROTATE_SHIFT(operand, 0b00100000) ? true : Error::LOG("Wrong Syntax @SHL\n");
}
bool ProgramLoader::SAL(const Operand& operand)
{
	return ROTATE_SHIFT(operand, 0b00100000) ? true : Error::LOG("Wrong Syntax @SAL\n");
}
bool ProgramLoader::SHR(const Operand& operand)
{
	return ROTATE_SHIFT(operand, 0b00101000) ? true : Error::LOG("Wrong Syntax @SHR\n");
}
bool ProgramLoader::SAR(const Operand& operand)
{
	return ROTATE_SHIFT(operand, 0b00111000) ? true : Error::LOG("Wrong Syntax @SAR\n");
}

bool ProgramLoader::RCL(const Operand& operand)
{
	return ROTATE_SHIFT(operand, 0b00010000) ? true : Error::LOG("Wrong Syntax @RCL\n");
}
bool ProgramLoader::RCR(const Operand& operand)
{
	return ROTATE_SHIFT(operand, 0b00011000) ? true : Error::LOG("Wrong Syntax @RCR\n");
}
bool ProgramLoader::ROL(const Operand& operand)
{
	return ROTATE_SHIFT(operand, 0b00000000) ? true : Error::LOG("Wrong Syntax @ROL\n");
}
bool ProgramLoader::ROR(const Operand& operand)
{
	return ROTATE_SHIFT(operand, 0b00001000) ? true : Error::LOG("Wrong Syntax @ROR\n");
}

/*<------------------------Carry Flag Manuplators------------------------------->*/
bool ProgramLoader::STC(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 0))
	{
		return Error::LOG("Expected No Operand @STC\n");
	}
	//OUT << "F9\n";
	Program[CurrInsIndex].MachineCode.push_back(0xF9);
	return true;
}

bool ProgramLoader::CLC(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 0))
	{
		return Error::LOG("Expected No Operand CLC\n");
	}
	//OUT << "F8\n";
	Program[CurrInsIndex].MachineCode.push_back(0xF8);
	return true;
}

bool ProgramLoader::CMC(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 0))
	{
		return Error::LOG("Expected No Operand @CMC\n");
	}
	//OUT << "F5\n";
	Program[CurrInsIndex].MachineCode.push_back(0xF5);
	return true;
}

/*<----------------------------JMP------------------------------------------>*/
bool ProgramLoader::JMP(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JMP\n");
	}
	//Machine code will be produce later(When forward referencing will be handled)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JC(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JC\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x72);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JNC(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JNC\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x73);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JZ_JE(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JZ/JE\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x74);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JNZ_JNE(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JNZ/JNE\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x75);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}

}

bool ProgramLoader::JPE_JP(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JPE/JP\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x7A);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JPO_JNP(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JPO/JNP\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x7B);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JS(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JS\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x78);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JNS(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JNS\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x79);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JO(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JO\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x70);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

bool ProgramLoader::JNO(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @JNO\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0x71);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}
/*<--------------------------CALL-------------------------->*/

bool ProgramLoader::CALL(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected No Operand @CALL\n");
	}
	//Machine code will be produce later(When handling forward referencing)
	if (Label::IsValidLabel(operand.first) && (Label::IndexOf(operand.first) < (int)Program.size()))
	{
		Program[CurrInsIndex].MachineCode.push_back(0xE8);
		//Just Adding 1st Byte of Machine code (Rest will be produced when forward referencing will be handled)
		return true;
	}
	else
	{
		return Error::LOG("Invalid Label OR Label with no definition.", Program[CurrInsIndex].LineNumber);
	}
}

/*<----------------------RET------------------------------>*/
bool ProgramLoader::RET(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 0))
	{
		return Error::LOG("Expected No Operand @RET\n");
	}
	Program[CurrInsIndex].MachineCode.push_back(0xC3);
	return true;
}

/*<-----------------------HLT----------------------------->*/
bool ProgramLoader::HLT(const Operand& operand)
{
	if (!Utility::IsValidOperandCount(operand, 0))
	{
		return Error::LOG("Expected No Operand @HLT\n");
	}
	Program[CurrInsIndex].MachineCode.push_back(0xF4);
	return true;
}