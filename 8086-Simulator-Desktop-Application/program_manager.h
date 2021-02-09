#pragma once
#include"operands.h"
#include"utility.h"
#include"error_handler.h"
#include<fstream>
#include"converter.h"
#include<iostream>


std::fstream out("machine_code.txt", std::ios::out);


class ProgramManager
{
	static bool MOV_CASE_1(std::string&, std::string&);
	static bool MOV_CASE_2(std::string&, std::string&);
	static bool MOV_CASE_3(std::string&, std::string&);
	static bool MOV_CASE_4(std::string&, std::string&);
	static bool MOV_CASE_5(std::string&, std::string&);
	static bool MOV_CASE_6(std::string&, std::string&);
	static bool MOV_CASE_7(std::string&, std::string&);
	static bool MOV_CASE_8(std::string&, std::string&);
public:
	static bool MOV(const Operand&);
};

bool ProgramManager::MOV_CASE_1(std::string& OP1, std::string& OP2)
{
	if (Utility::Is8BitRegister(OP1))//REG8, 8-BIT-DATA
	{
		//If the OP2 is in 8bit range or not
		if (Utility::HexSize(OP2) != "8")
		{
			Error::LOG("Expected 8Bit data. @MOV\n");
		}
		else
		{
			//may be data is represented using redundatn hex digit eg: 001Ah, 010H
			Utility::Format16Bit(OP2);
			OP2 = OP2.substr(2); // Truncating redundant digits
		}

		//opcode(8Bit)=> B0 + reg_Code
		const std::string& opcode = Converter::DecToHex(0xB0 + REG_CODE.find(OP1)->second);
		Utility::Format8Bit(OP2);
		const std::string& data = OP2.substr(0, 2);
		out << opcode.substr(0, 2) << ' ' << data << '\n';
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

bool ProgramManager::MOV_CASE_2(std::string& OP1, std::string& OP2)
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

bool ProgramManager::MOV_CASE_3(std::string& OP1, std::string& OP2)
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

bool ProgramManager::MOV_CASE_4(std::string& OP1, std::string& OP2)
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

bool ProgramManager::MOV_CASE_5(std::string& OP1, std::string& OP2)
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

bool ProgramManager::MOV_CASE_6(std::string& OP1, std::string& OP2)
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

bool ProgramManager::MOV_CASE_7(std::string& OP1, std::string& OP2)
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

bool ProgramManager::MOV_CASE_8(std::string& OP1, std::string& OP2)
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

bool ProgramManager::MOV(const Operand& operand)
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