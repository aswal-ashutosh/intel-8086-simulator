#pragma once
#include"operands.h"
#include"utility.h"
#include"error_handler.h"
#include<fstream>
#include"converter.h"
#include<iostream>
#include<unordered_map>
#include"instruction.h"


std::fstream out("machine_code.txt", std::ios::out);


class ProgramLoader
{
	static std::unordered_map<std::string, bool (*)(const Operand&)> CallBacks;
	static bool MOV_CASE_1(std::string&, std::string&);
	static bool MOV_CASE_2(std::string&, std::string&);
	static bool MOV_CASE_3(std::string&, std::string&);
	static bool MOV_CASE_4(std::string&, std::string&);
	static bool MOV_CASE_5(std::string&, std::string&);
	static bool MOV_CASE_6(std::string&, std::string&);
	static bool MOV_CASE_7(std::string&, std::string&);
	static bool MOV_CASE_8(std::string&, std::string&);

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
	//AAACOSSX generate machine code for => ADD, ADC, AND, CMP, OR, SUB, SBB, XOR
	static bool AAACOSSX(const Operand&, const Byte, const Byte);

	static bool MUL_CASE_1(std::string&);
	static bool MUL_CASE_2(std::string&);
	static bool MUL_CASE_3(std::string&);
	
	static bool IMUL_CASE_1(std::string&);
	static bool IMUL_CASE_2(std::string&);
	static bool IMUL_CASE_3(std::string&);

	static bool DIV_CASE_1(std::string&);
	static bool DIV_CASE_2(std::string&);
	static bool DIV_CASE_3(std::string&);

	static bool IDIV_CASE_1(std::string&);
	static bool IDIV_CASE_2(std::string&);
	static bool IDIV_CASE_3(std::string&);

public:
	static void LoadCallBacks();
	static bool Load(const std::vector<Instruction>&);


	static bool MOV(const Operand&);
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
};

std::unordered_map<std::string, bool (*)(const Operand&)> ProgramLoader::CallBacks;

void ProgramLoader::LoadCallBacks()
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
}

bool ProgramLoader::Load(const std::vector<Instruction>& Program)
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
			return Error::LOG(I.Mnemonic + " is not implemented yet! @ Load\n");
		}
	}
	return true;
}

bool ProgramLoader::MOV_CASE_1(std::string& OP1, std::string& OP2)
{
	if (Utility::Is8BitRegister(OP1))//REG8, 8-BIT-DATA
	{
		//If the OP2 is in 8bit range or not
		if (Utility::HexSize(OP2) != "8")
		{
			Error::LOG("Expected 8Bit data. @MOV\n");
		}

		//opcode(8Bit)=> B0 + reg_Code
		const std::string& opcode = Converter::DecToHex(0xB0 + REG_CODE.find(OP1)->second);
		Utility::Format16Bit(OP2);
		out << opcode.substr(0, 2) << ' ' << OP2.substr(2, 2) << '\n';
	}
	else if (Utility::Is16BitRegister(OP1))//REG16, 16-BIT-DATA
	{
		//If the OP2 is in 16bit range or not
		if (OP2.length() > 5) { return Error::LOG("Expected 16-Bit data. @MOV\n"); }

		//OPCODE(8bit)=> B8 + reg_Code
		const std::string& opcode = Converter::DecToHex(0xB8 + REG_CODE.find(OP1)->second);
		Utility::Format16Bit(OP2);
		const std::string& lowerData = OP2.substr(2, 2);
		const std::string& higherData = OP2.substr(0, 2);
		out << opcode.substr(0, 2) << ' ' << lowerData << ' ' << higherData << '\n';
	}
	else
	{
		//error
		return Error::LOG("Expected MOV reg8/16, 8/16-Bit-DATA\n");
	}

	return true;
}

bool ProgramLoader::MOV_CASE_2(std::string& OP1, std::string& OP2)
{
	/*
		As there is no register so reg code will be 000
		If immd8 1st Byte wiil be C6 else if immd16 then 1st Byte wiil be C7
	*/
	const std::string& mem = OP1;
	std::string immd = OP2;
	const std::string& fExp = Converter::ExpressionForModRM(mem);

	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte _2ndByte = info.mod << 6;
		//Reg-Code is 000 already
		_2ndByte |= info.rm;

		std::string _2ndByteHex = Converter::DecToHex(_2ndByte);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		if (Utility::HexSize(immd) == "8")//immd8
		{
			out << "C6" << ' ' << _2ndByteHex.substr(0, 2);
		}
		else//immd16
		{
			out << "C7" << ' ' << _2ndByteHex.substr(0, 2);
		}

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2);
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
				}
			}
		}

		//Next byte will contain immd
		Utility::Format16Bit(immd);

		if (Utility::HexSize(immd) == "8")
		{
			out << ' ' << immd.substr(2, 2) << '\n';
		}
		else
		{
			out << ' ' << immd.substr(2, 2) << ' ' << immd.substr(0, 2) << '\n';
		}

	}
	else
	{
		return Error::LOG("Invalid [EXP][CASE:2]\n");
	}
	
	return true;
}

bool ProgramLoader::MOV_CASE_3(std::string& OP1, std::string& OP2)
{
	//Opcde(6)-d(1)-w(1) => 100010-1-0 => 8A
	const std::string& opcode = "8A";

	//mod(2)-reg(3)-r/m(3) => 11-Reg_CODE(first)-Reg_Code(second)
	Byte _2ndByte = 0b11000000;						//mod = 11
	_2ndByte |= REG_CODE.find(OP1)->second << 3;	//reg-code(first)
	_2ndByte |= REG_CODE.find(OP2)->second;			//reg-code/(r/m)

	const std::string& _2ndByteHex = Converter::DecToHex(_2ndByte);

	out << opcode << ' ' << _2ndByteHex.substr(0, 2) << '\n';

	return true;
}

bool ProgramLoader::MOV_CASE_4(std::string& OP1, std::string& OP2)
{
	//Opcode(6)-d(1)-w(1) => 100010-1-1 => 8B
	const std::string& opcode = "8B";

	//mod(2)-reg(3)-r/m(3) => 11-Reg_CODE(first)-Reg_Code(second)
	Byte _2ndByte = 0b11000000;						//mod = 11
	_2ndByte |= REG_CODE.find(OP1)->second << 3;	//reg-code(first)
	_2ndByte |= REG_CODE.find(OP2)->second;			//reg-code/(r/m)

	const std::string& _2ndByteHex = Converter::DecToHex(_2ndByte);

	out << opcode << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::MOV_CASE_5(std::string& OP1, std::string& OP2)
{
	const std::string &reg = OP1;
	const std::string &mem = OP2;
	/*
		For 8Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-1-0 => 8A
		For 16Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-1-1 => 8B
		[*]Special Case when reg is AL and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-0-0 => A0, Second byte of opcode will be data directly
		[*]Special Case when reg is AX and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-0-1 => A1, Second byte of opcode will be data directly
	*/

	const std::string& fExp = Converter::ExpressionForModRM(mem);

	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

	//Checking for Special Case
	if (onlyDisp && (reg == REGISTER::AL || reg == REGISTER::AX))
	{
		//Special Cases
		Utility::Format16Bit(displacement);
		if (reg == REGISTER::AL)
		{
			out << "A0" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
		}
		else if (reg == REGISTER::AX)
		{
			out << "A1" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
		}
	}
	else
	{
		const std::string& opcode = Utility::Is8BitRegister(reg) ? "8A" : "8B";
		if (MOD_RM.count(fExp))
		{
			//mod(2)-reg(3)-r/m(3) => mod-Reg_CODE(first)-r/m_code
			const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

			Byte _2ndByte = info.mod << 6; //mod
			_2ndByte |= REG_CODE.find(reg)->second << 3; // reg
			_2ndByte |= info.rm;

			std::string _2ndByteHex = Converter::DecToHex(_2ndByte);

			out << opcode
				<< ' ' << _2ndByteHex.substr(0, 2);

			//there may be displacement data/Disp in expersion
			if (displacement.empty())
			{
				out << '\n';
			}
			else
			{
				Utility::Format16Bit(displacement);
				if (onlyDisp) //It will considered in 16 bit
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
				else
				{
					if (Utility::HexSize(displacement) == "8")
					{
						out << ' ' << displacement.substr(2, 2) << '\n';
					}
					else
					{
						out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
					}
				}
			}
		}
		else
		{
			return Error::LOG("Invalid [EXP][CASE:5]\n");
		}
	}

	return true;
}

bool ProgramLoader::MOV_CASE_6(std::string& OP1, std::string& OP2)
{
	const std::string& mem = OP1;
	const std::string& reg = OP2;

	/*
		For 8Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-0-0 => 88
		For 16Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-0-1 => 89
		[*]Special Case when reg is AL and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-1-0 => A2, Second byte of opcode will be data directly
		[*]Special Case when reg is AX and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-1-1 => A3, Second byte of opcode will be data directly
	*/
	const std::string& fExp = Converter::ExpressionForModRM(mem);

	std::string displacement = "";
	bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);


	//Checking for Special Case
	if (onlyDisp && (reg == REGISTER::AL || reg == REGISTER::AX))
	{
		//Special Cases
		Utility::Format16Bit(displacement);
		if (reg == REGISTER::AL)
		{
			out << "A2" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
		}
		else if (reg == REGISTER::AX)
		{
			out << "A3" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
		}
	}
	else
	{
		const std::string& opcode = Utility::Is8BitRegister(reg) ? "88" : "89";
		if (MOD_RM.count(fExp))
		{
			//mod(2)-reg(3)-r/m(3) => mod-Reg_CODE(first)-r/m_code
			const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

			Byte _2ndByte = info.mod << 6; //mod
			_2ndByte |= REG_CODE.find(reg)->second << 3; // reg
			_2ndByte |= info.rm;

			std::string _2ndByteHex = Converter::DecToHex(_2ndByte);

			out << opcode << ' ' << _2ndByteHex.substr(0, 2);

			//there may be displacement data/Disp in expersion
			if (displacement.empty())
			{
				out << '\n';
			}
			else
			{
				Utility::Format16Bit(displacement);
				if (onlyDisp) //It will considered in 16 bit
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
				else
				{
					if (Utility::HexSize(displacement) == "8")
					{
						out << ' ' << displacement.substr(2, 2) << '\n';
					}
					else
					{
						out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
					}
				}
			}
		}
		else
		{
			return Error::LOG("Invalid [EXP][CASE:6]\n");
		}
	}

	return true;
}

bool ProgramLoader::MOV_CASE_7(std::string& OP1, std::string& OP2)
{
	if (Utility::IsSegmentRegister(OP2)){ return Error::LOG("mov sreg, sreg is not allowed\n"); }
	else if (OP1 == REGISTER::CS){ return Error::LOG("Cs can't be modified directly\n"); }

	const std::string& sreg = OP1;
	const std::string& rm16 = OP2;
	const std::string& opcode = "8E";

	//Second Byte => xx0sregxxx =>mod(2)-0-sreg(2)-rm(3)
	if (Utility::Is16BitRegister(rm16))
	{
		const MOD_RM_INFO& info = MOD_RM.find(rm16)->second;
		Byte _2ndByte = info.mod << 6;
		_2ndByte |= REG_CODE.find(sreg)->second << 3;
		_2ndByte |= info.rm;

		std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
		out << opcode << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	}
	else if (Utility::IsMemory(rm16))
	{

		const std::string& fExp = Converter::ExpressionForModRM(rm16);
		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(rm16, displacement);
		if (MOD_RM.count(fExp))
		{
			const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
			Byte _2ndByte = info.mod << 6;
			_2ndByte |= REG_CODE.find(sreg)->second << 3;
			_2ndByte |= info.rm;

			std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
			out << opcode << ' ' << _2ndByteHex.substr(0, 2);

			if (displacement.empty())
			{
				out << '\n';
			}
			else
			{
				Utility::Format16Bit(displacement);
				if (onlyDisp) //It will considered in 16 bit
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
				else
				{
					if (Utility::HexSize(displacement) == "8")
					{
						out << ' ' << displacement.substr(2, 2) << '\n';
					}
					else
					{
						out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
					}
				}
			}
		}
		else
		{
			return Error::LOG("Invalid [EXP][CASE:7]\n");
		}
	}
	else
	{
		//error
		return Error::LOG("Expected MOV sreg, r/m16\n");
	}

	return true;
}

bool ProgramLoader::MOV_CASE_8(std::string& OP1, std::string& OP2)
{
	if (Utility::IsSegmentRegister(OP1))
	{
		return Error::LOG("mov sreg, sreg is not allowed\n");
	}

	const std::string& sreg = OP2;
	const std::string& rm16 = OP1;
	const std::string& opcode = "8C";

	//Second Byte => xx0sregxxx =>mod(2)-0-sreg(2)-rm(3)
	if (Utility::Is16BitRegister(rm16))
	{
		const MOD_RM_INFO& info = MOD_RM.find(rm16)->second;
		Byte _2ndByte = info.mod << 6;
		_2ndByte |= REG_CODE.find(sreg)->second << 3;
		_2ndByte |= info.rm;

		std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
		out << opcode << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	}
	else if (Utility::IsMemory(rm16))
	{

		const std::string& fExp = Converter::ExpressionForModRM(rm16);
		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(rm16, displacement);
		if (MOD_RM.count(fExp))
		{
			const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
			Byte _2ndByte = info.mod << 6;
			_2ndByte |= REG_CODE.find(sreg)->second << 3;
			_2ndByte |= info.rm;

			std::string _2ndByteHex = Converter::DecToHex(_2ndByte);
			out << opcode << ' ' << _2ndByteHex.substr(0, 2);

			if (displacement.empty())
			{
				out << '\n';
			}
			else
			{
				Utility::Format16Bit(displacement);
				if (onlyDisp) //It will considered in 16 bit
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
				else
				{
					if (Utility::HexSize(displacement) == "8")
					{
						out << ' ' << displacement.substr(2, 2) << '\n';
					}
					else
					{
						out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
					}
				}
			}
		}
		else
		{
			return Error::LOG("Invalid[EXP]\n");
		}
	}
	else
	{
		//error
		return Error::LOG("Expected MOV r/m16, sreg\n");
	}

	return true;
}

bool ProgramLoader::MOV(const Operand& operand)
{
	//TODO:: Check Whether we have two operands or not
	if (!Utility::IsValidOperandCount(operand, 2))
	{
		return Error::LOG("Expected 2 Operands @MOV\n");
	}

	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	if ((Utility::Is16BitRegister(OP1) || Utility::Is8BitRegister(OP1)) && Utility::IsValidHex(OP2))
	{
		/*[CASE:1] MOV reg8/reg16, immd8/immd16*/
		return MOV_CASE_1(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2))
	{
		/*[CASE:2] MOV mem, immd8/immd16*/
		return MOV_CASE_2(OP1, OP2);
	}
	else if ((Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2)))
	{
		/*[CASE:3]MOV reg8, reg8*/
		return MOV_CASE_3(OP1, OP2);

	}
	else if ((Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2)))
	{
		/*[CASE:4]MOV reg16, reg16*/
		return MOV_CASE_4(OP1, OP2);
	}
	else if ((Utility::Is8BitRegister(OP1) || Utility::Is16BitRegister(OP1)) && Utility::IsMemory(OP2))
	{
		/*[CASE:5]MOV reg8/reg16, mem*/
		return MOV_CASE_5(OP1, OP2);
	}
	else if (Utility::IsMemory(OP1) && (Utility::Is8BitRegister(OP2) || Utility::Is16BitRegister(OP2)))
	{
		/*[CASE:6]MOV mem, reg8/reg16*/
		return MOV_CASE_6(OP1, OP2);
	}
	else if (Utility::IsSegmentRegister(OP1))
	{
		/*[CASE:7]MOV sreg, r/m16*/
		return MOV_CASE_7(OP1, OP2);
	}
	else if (Utility::IsSegmentRegister(OP2))
	{
		/*[CASE:8]MOV r/m16, sreg*/
		return MOV_CASE_8(OP1, OP2);
	}

	return Error::LOG("Syntax Error @ MOV\n");
}

bool ProgramLoader::AAACOSSX_CASE_1(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{	
	//REG8, R/M8
	//[CASE-1]REG8, REG8 
	//1st Byte => 02 + Offset (Depending upon Mnemonic)
	//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(OP1)]-[reg-code(OP2)]
	Byte B1 = 0x02 + OFFSET;
	Byte B2 = 0b11000000;
	B2 |= REG_CODE.find(OP1)->second << 3;
	B2 |= REG_CODE.find(OP2)->second;
	const std::string& hB1 = Converter::DecToHex(B1);
	const std::string& hB2 = Converter::DecToHex(B2);
	out << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_2(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	//[CASE-2]REG8, [MEM]
	//1st Byte => 02
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(OP1)]-[RM]
	const std::string& mem = OP2;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B1 = 0x02 + OFFSET;
		Byte B2 = info.mod << 6;
		B2 |= REG_CODE.find(OP1)->second << 3;
		B2 |= info.rm;
		const std::string& hB1 = Converter::DecToHex(B1);
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2) << '\n';
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
			}
		}
		else
		{
			out << '\n';
		}
	}
	else
	{
		return Error::LOG("Invalid R/M [CASE:2]\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_3(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	/*[CASE-3] MEM, REG8*/
	//1st Byte => 00
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(OP2)]-[RM]
	const std::string& mem = OP1;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B1 = 0x00 + OFFSET;
		Byte B2 = info.mod << 6;
		B2 |= REG_CODE.find(OP2)->second << 3;
		B2 |= info.rm;
		const std::string& hB1 = Converter::DecToHex(B1);
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2) << '\n';
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
			}
		}
		else
		{
			out << '\n';
		}
	}
	else
	{
		return Error::LOG("Invalid R/M [CASE:3]\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_4(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	//REG16, R/M16
	/*[CASE-4] REG16, REG16*/
	//1st Byte => 03
	//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(OP1)]-[reg-code(OP2)]
	Byte B1 = 0x03 + OFFSET;
	Byte B2 = 0b11000000;
	B2 |= REG_CODE.find(OP1)->second << 3;
	B2 |= REG_CODE.find(OP2)->second;
	const std::string& hB1 = Converter::DecToHex(B1);
	const std::string& hB2 = Converter::DecToHex(B2);
	out << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_5(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	/*[CASE-5] REG16, MEM*/
	//1st Byte => 03
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(OP1)]-[RM]
	const std::string& mem = OP2;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B1 = 0x03 + OFFSET;
		Byte B2 = info.mod << 6;
		B2 |= REG_CODE.find(OP1)->second << 3;
		B2 |= info.rm;
		const std::string& hB1 = Converter::DecToHex(B1);
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2) << '\n';
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
			}
		}
		else
		{
			out << '\n';
		}
	}
	else
	{
		return Error::LOG("Invalid R/M [CASE:5]\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_6(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	/*[CASE-6] MEM, REG16*/
	//1st Byte => 01
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(OP2)]-[RM]
	const std::string& mem = OP1;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B1 = 0x01 + OFFSET;
		Byte B2 = info.mod << 6;
		B2 |= REG_CODE.find(OP2)->second << 3;
		B2 |= info.rm;
		const std::string& hB1 = Converter::DecToHex(B1);
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << hB1.substr(0, 2) << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2) << '\n';
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
			}
		}
		else
		{
			out << '\n';
		}
	}
	else
	{
		return Error::LOG("Invalid R/M [CASE:6]\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_7(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	/*[CASE-7] MEM, IMMD8*/
	//1st Byte => 80
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(000)]-[RM]
	const std::string& mem = OP1;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = info.mod << 6;
		B2 |= REG;
		B2 |= info.rm;
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << "80" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2);
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
				}
			}
		}

		//Next byte will contain immd
		Utility::Format16Bit(OP2);
		out << ' ' << OP2.substr(2, 2) << '\n';

	}
	else
	{
		return Error::LOG("Invalid R/M [CASE:7]\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_8(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	/*[CASE-8] MEM, IMMD16*/
	//1st Byte => 81
	//2nd Byte => mod(2)-reg(3)-m(3) => [mod]-[reg-code(000)]-[RM]
	const std::string& mem = OP1;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = info.mod << 6;
		B2 |= REG;
		B2 |= info.rm;
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << "81" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2);
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2);
				}
			}
		}

		//Next byte will contain immd
		Utility::Format16Bit(OP2);
		out << ' ' << OP2.substr(2, 2) << ' ' << OP2.substr(0, 2) << '\n';

	}
	else
	{
		return Error::LOG("Invalid R/M [CASE:8]\n");
	}

	return true;
}

bool ProgramLoader::AAACOSSX_CASE_9(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	//R/M8, IMMD8
	/*[CASE-9] REG8, IMMD8*/
	/*[*] Special Case when reg is AL=> 1st Byte [04]   2nd Byte [immd8] */
	if (OP1 == REGISTER::AL)
	{
		Byte B1 = 0x04 + OFFSET;
		const std::string& hB1 = Converter::DecToHex(B1);
		Utility::Format16Bit(OP2);
		out << hB1.substr(0, 2) << ' ' << OP2.substr(2, 2) << '\n';
	}
	else
	{
		//1st Byte => 80
		//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(000)]-[reg-code(OP1)] OR use MOD_RM
		if (MOD_RM.count(OP1))
		{
			const MOD_RM_INFO& info = MOD_RM.find(OP1)->second;
			Byte B2 = info.mod << 6;
			B2 |= REG;
			B2 |= info.rm;
			const std::string& hB2 = Converter::DecToHex(B2);

			out << "80" << ' ' << hB2.substr(0, 2);

			//Next byte will contain immd
			Utility::Format16Bit(OP2);
			out << ' ' << OP2.substr(2, 2) << '\n';

		}
		else 
		{
			return Error::LOG("Invalid R/M [CASE:9]\n");
		}
	}
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_10(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	//R/M16, IMMD16
	/*CASE-10] REG16, IMMD16*/
	/*[*] Special Case when reg is AX=> 1st Byte [05]   2nd Byte [immd16] */
	if (OP1 == REGISTER::AX)
	{
		Byte B1 = 0x05 + OFFSET;
		const std::string& hB1 = Converter::DecToHex(B1);
		Utility::Format16Bit(OP2);
		out << hB1.substr(0, 2) << ' ' << OP2.substr(2, 2) << ' ' << OP2.substr(0, 2) << '\n';
	}
	else
	{
		//1st Byte => 81
		//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(000)]-[reg-code(OP1)] OR use MOD_RM
		if (MOD_RM.count(OP1))
		{
			const MOD_RM_INFO& info = MOD_RM.find(OP1)->second;
			Byte B2 = info.mod << 6;
			B2 |= REG;
			B2 |= info.rm;
			const std::string& hB2 = Converter::DecToHex(B2);

			out << "81" << ' ' << hB2.substr(0, 2);

			//Next byte will contain immd
			Utility::Format16Bit(OP2);
			out << ' ' << OP2.substr(2, 2) << ' ' << OP2.substr(0, 2) << '\n';
		}
		else
		{
			return Error::LOG("Invalid R/M [CASE:10]\n");
		}
	}
	return true;
}

bool ProgramLoader::AAACOSSX_CASE_11(std::string& OP1, std::string& OP2, const Byte OFFSET, const Byte REG)
{
	//REG16, Immd8
	/*[*] Special Case when reg is AX=> 1st Byte [05]   2nd Byte [immd8 as immd16] */
	if (OP1 == REGISTER::AX)
	{
		Byte B1 = 0x05 + OFFSET;
		const std::string& hB1 = Converter::DecToHex(B1);
		Utility::Format16Bit(OP2);
		out << hB1.substr(0, 2) << ' ' << OP2.substr(2, 2) << ' ' << OP2.substr(0, 2) << '\n';
	}
	else
	{
		//1st Byte => 83
		//2nd Byte => mod(2)-reg(3)-m(3) => [11]-[reg-code(000)]-[reg-code(OP1)] OR use MOD_RM
		if (MOD_RM.count(OP1))
		{
			const MOD_RM_INFO& info = MOD_RM.find(OP1)->second;
			Byte B2 = info.mod << 6;
			B2 |= REG;
			B2 |= info.rm;
			const std::string& hB2 = Converter::DecToHex(B2);

			out << "83" << ' ' << hB2.substr(0, 2);

			//Next byte will contain immd
			Utility::Format16Bit(OP2);
			out << ' ' << OP2.substr(2, 2) << '\n';
		}
		else
		{
			return Error::LOG("Invalid R/M [CASE:11]\n");
		}
	}
	return true;
}

bool ProgramLoader::AAACOSSX(const Operand& operand, const Byte OFFSET, const Byte REG)
{
	if (!Utility::IsValidOperandCount(operand, 2))
	{
		return Error::LOG("Expected 2 Operands @MOV\n");
	}

	std::string OP1 = operand.first;
	std::string OP2 = operand.second;

	if (Utility::Is8BitRegister(OP1) && Utility::Is8BitRegister(OP2))
	{	/*[CASE-1] REG8, REG8*/
		return AAACOSSX_CASE_1(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-2] REG8, MEM*/
		return AAACOSSX_CASE_2(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is8BitRegister(OP2))
	{
		/*[CASE-3] MEM, REG8*/
		return AAACOSSX_CASE_3(OP1, OP2, OFFSET, REG);

	}
	else if (Utility::Is16BitRegister(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-4] REG16, REG16*/
		return AAACOSSX_CASE_4(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsMemory(OP2))
	{
		/*[CASE-5] REG16, MEM*/
		return AAACOSSX_CASE_5(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::IsMemory(OP1) && Utility::Is16BitRegister(OP2))
	{
		/*[CASE-6] MEM, REG16*/
		return AAACOSSX_CASE_6(OP1, OP2, OFFSET, REG);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-7] MEM, IMMD8*/
		return AAACOSSX_CASE_7(OP1, OP2, OFFSET, REG);

	}
	else if (Utility::IsMemory(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*[CASE-8] MEM, IMMD16*/
		return AAACOSSX_CASE_8(OP1, OP2, OFFSET, REG);

	}
	else if (Utility::Is8BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-9] REG8, IMMD8*/
		return AAACOSSX_CASE_9(OP1, OP2, OFFSET, REG);
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "16")
	{
		/*CASE-10] REG16, IMMD16*/
		return AAACOSSX_CASE_10(OP1, OP2, OFFSET, REG);
		
	}
	else if (Utility::Is16BitRegister(OP1) && Utility::IsValidHex(OP2) && Utility::HexSize(OP2) == "8")
	{
		/*[CASE-11] REG16, IMMD8*/
		return AAACOSSX_CASE_11(OP1, OP2, OFFSET, REG);
	}

	return Error::LOG("Syntax error @ AAACOSSX\n");
}

bool ProgramLoader::MUL_CASE_1(std::string& OP)
{
	//Memory
	const std::string& mem = OP;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = info.mod << 6;
		B2 |= 0b00100000;
		B2 |= info.rm;
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << "F6" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2) << '\n';
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
			}
		}
		else
		{
			out << '\n';
		}
	}
	else
	{
		return Error::LOG("Invalid Memory Exp @MUL_CASE_1\n");
	}
	return true;
}

bool ProgramLoader::MUL_CASE_2(std::string& OP)
{
	//REG8
	Byte B2 = 0b11100000;
	B2 |= REG_CODE.find(OP)->second;
	const std::string& hB2 = Converter::DecToHex(B2);
	out << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::MUL_CASE_3(std::string& OP)
{
	//REG16
	Byte B2 = 0b11100000;
	B2 |= REG_CODE.find(OP)->second;
	const std::string& hB2 = Converter::DecToHex(B2);
	out << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::IMUL_CASE_1(std::string& OP)
{
	//Memory
	const std::string& mem = OP;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = info.mod << 6;
		B2 |= 0b00101000;
		B2 |= info.rm;
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << "F6" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2) << '\n';
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
			}
		}
		else
		{
			out << '\n';
		}
	}
	else
	{
		return Error::LOG("Invalid Memory Exp @MUL_CASE_1\n");
	}
	return true;
}

bool ProgramLoader::IMUL_CASE_2(std::string& OP)
{
	//REG8
	Byte B2 = 0b11101000;
	B2 |= REG_CODE.find(OP)->second;
	const std::string& hB2 = Converter::DecToHex(B2);
	out << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::IMUL_CASE_3(std::string& OP)
{
	//REG16
	Byte B2 = 0b11101000;
	B2 |= REG_CODE.find(OP)->second;
	const std::string& hB2 = Converter::DecToHex(B2);
	out << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::DIV_CASE_1(std::string& OP)
{
	//Memory
	const std::string& mem = OP;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = info.mod << 6;
		B2 |= 0b00110000;
		B2 |= info.rm;
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << "F6" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2) << '\n';
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
			}
		}
		else
		{
			out << '\n';
		}
	}
	else
	{
		return Error::LOG("Invalid Memory Exp @DIV_CASE_1\n");
	}
	return true;
}

bool ProgramLoader::DIV_CASE_2(std::string& OP)
{
	//REG8
	Byte B2 = 0b11110000;
	B2 |= REG_CODE.find(OP)->second;
	const std::string& hB2 = Converter::DecToHex(B2);
	out << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::DIV_CASE_3(std::string& OP)
{
	//REG16
	Byte B2 = 0b11110000;
	B2 |= REG_CODE.find(OP)->second;
	const std::string& hB2 = Converter::DecToHex(B2);
	out << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::IDIV_CASE_1(std::string& OP)
{
	//Memory
	const std::string& mem = OP;
	const std::string& fExp = Converter::ExpressionForModRM(mem);
	if (MOD_RM.count(fExp))
	{
		const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
		Byte B2 = info.mod << 6;
		B2 |= 0b00111000;
		B2 |= info.rm;
		const std::string& hB2 = Converter::DecToHex(B2);

		std::string displacement = "";
		bool onlyDisp = Utility::ExtractHexFromMemExp(mem, displacement);

		out << "F6" << ' ' << hB2.substr(0, 2);

		if (!displacement.empty())
		{
			Utility::Format16Bit(displacement);
			if (onlyDisp)
			{
				out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
			}
			else
			{
				if (Utility::HexSize(displacement) == "8")
				{
					out << ' ' << displacement.substr(2, 2) << '\n';
				}
				else
				{
					out << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
			}
		}
		else
		{
			out << '\n';
		}
	}
	else
	{
		return Error::LOG("Invalid Memory Exp @DIV_CASE_1\n");
	}
	return true;
}

bool ProgramLoader::IDIV_CASE_2(std::string& OP)
{
	//REG8
	Byte B2 = 0b11111000;
	B2 |= REG_CODE.find(OP)->second;
	const std::string& hB2 = Converter::DecToHex(B2);
	out << "F6" << ' ' << hB2.substr(0, 2) << '\n';
	return true;
}

bool ProgramLoader::IDIV_CASE_3(std::string& OP)
{
	//REG16
	Byte B2 = 0b11111000;
	B2 |= REG_CODE.find(OP)->second;
	const std::string& hB2 = Converter::DecToHex(B2);
	out << "F7" << ' ' << hB2.substr(0, 2) << '\n';
	return true;
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

bool ProgramLoader::MUL(const Operand& operand)
{
	//REG8, REG16, []
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand1 @MUL\n");
	}

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

	return Error::LOG("Syntax Error @MUL\n");
}

bool ProgramLoader::IMUL(const Operand& operand)
{
	//REG8, REG16, []
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand1 @IMUL\n");
	}

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

	return Error::LOG("Syntax Error @IMUL\n");
}

bool ProgramLoader::DIV(const Operand& operand)
{
	//REG8, REG16, []
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand1 @DIV\n");
	}

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

	return Error::LOG("Syntax Error @DIV\n");
}

bool ProgramLoader::IDIV(const Operand& operand)
{
	//REG8, REG16, []
	if (!Utility::IsValidOperandCount(operand, 1))
	{
		return Error::LOG("Expected 1 Operand1 @IDIV\n");
	}

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

	return Error::LOG("Syntax Error @IDIV\n");
}