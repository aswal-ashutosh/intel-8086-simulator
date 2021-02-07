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
public:
	static bool MOV(Operand&);
};

bool ProgramManager::MOV(Operand& operand)
{
	//TODO:: Check Whether we have two operands or not

	/*
		The operands will be of form: 
			[OK]1)MOV reg8/reg16, immd8/immd16 || MOV mem, immd8/immd16
			[OK]2)MOV reg8/reg16, reg8/reg16
			[OK]3)MOV reg8/reg16, mem
			[OK]4)MOV mem, reg8/reg16
			[x]5)MOV sreg, reg16
			[x]6)MOV reg16, sreg
			
	*/

	if (Utility::Is8BitRegister(operand.first) && Utility::Is8BitRegister(operand.second))
	{
		//Case 2 reg8, reg8

		//Opcde(6)-d(1)-w(1) => 100010-1-0 => 8A
		const std::string &opcode = "8A";

		//mod(2)-reg(3)-r/m(3) => 11-Reg_CODE(first)-Reg_Code(second)
		Byte _2ndByte = 0b11000000;//mod = 11
		_2ndByte |= REG_CODE.find(operand.first)->second << 3;//reg-code(first)
		_2ndByte |= REG_CODE.find(operand.second)->second;//reg-code/(r/m)

		const std::string &_2ndByteHex = Converter::DecToHex(_2ndByte);

		out << opcode << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	}
	else if (Utility::Is16BitRegister(operand.first) && Utility::Is16BitRegister(operand.second))
	{
		//Case 2 reg16, reg16

		//Opcode(6)-d(1)-w(1) => 100010-1-1 => 8B

		const std::string &opcode = "8B";

		//mod(2)-reg(3)-r/m(3) => 11-Reg_CODE(first)-Reg_Code(second)
		Byte _2ndByte = 0b11000000;//mod = 11
		_2ndByte |= REG_CODE.find(operand.first)->second << 3;//reg-code(first)
		_2ndByte |= REG_CODE.find(operand.second)->second;//reg-code/(r/m)

		const std::string &_2ndByteHex = Converter::DecToHex(_2ndByte);

		out << opcode << ' ' << _2ndByteHex.substr(0, 2) << '\n';
	}
	else if (Utility::IsValidHex(operand.second))//Considering form 1
	{

		if (Utility::IsMemory(operand.first)) //Case 1 Part 2
		{
			//mem, immd8/16

			/*
				As there is no register so reg code will be 000
				If immd8 => 1st Byte C6 else if immd16 then C7
			*/
			const std::string& mem = operand.first;
			std::string immd = operand.second;
			const std::string& exp = mem.substr(1, mem.length() - 2); //[] removed
			const std::string& fExp = Converter::ExpressionForModRM(exp); 
			
			if (MOD_RM.count(fExp))
			{
				const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;
				Byte _2ndByte = info.mod << 6;
				//Reg-Code is 000 already
				_2ndByte |= info.rm;

				std::string _2ndByteHex = Converter::DecToHex(_2ndByte);

				std::string displacement = "";
				bool onlyDisp = Utility::ExtractHexFromMemExp(exp, displacement);

				if (Utility::HexSize(immd) == "8")//immd8
				{
					out << "C6" << ' ' << _2ndByteHex.substr(0, 2);
				}
				else//immd16
				{
					out << "C7" << ' ' << _2ndByteHex.substr(0, 2);
				}

				if(!displacement.empty())
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
				Error::LOG("Invalid mem exp r/m, immd @ Mov");
			}
		}
		else if (Utility::IsSegmentRegister(operand.first))
		{
			//error
			Error::LOG("Segment register can't be assigned with immediate data\n");
		}
		else if(Utility::Is8BitRegister(operand.first)) //Case 1 with 8-bit reg
		{
			//reg8, 8-Bit data

			//If the operand.second is in 8bit range or not

			if (Utility::HexSize(operand.second) != "8")
			{
				Error::LOG("Expected 8Bit data. @MOV\n");
			}
			else
			{
				//may be data is represented using redundatn hex digit eg: 001Ah, 010H
				Utility::Format16Bit(operand.second);
				operand.second = operand.second.substr(2); // Truncating redundant digits
			}

			//opcode(8Bit)=> B0 + reg_Code
			const std::string &opcode = Converter::DecToHex(0xB0 + REG_CODE.find(operand.first)->second);
			Utility::Format8Bit(operand.second);
			const std::string &data = operand.second.substr(0, 2);
			out << opcode.substr(0, 2) << ' ' << data << '\n';
		}
		else if (Utility::Is16BitRegister(operand.first)) //Case 1 with 16-bit reg
		{
			//reg16, 16-Bit data
			

			//If the operand.second is in 16bit range or not
			if (operand.second.length() > 5)
			{
				Error::LOG("Expected 16-Bit data. @MOV\n");
			}

			//opcode(8bit)=> B8 + reg_Code
			const std::string &opcode = Converter::DecToHex(0xB8 + REG_CODE.find(operand.first)->second);
			Utility::Format16Bit(operand.second);
			const std::string &lowerData = operand.second.substr(2, 2);
			const std::string &higherData = operand.second.substr(0, 2);
			out << opcode.substr(0, 2) << ' ' << lowerData << ' ' << higherData << '\n';
		}
		else
		{
			//error
			Error::LOG("Expected MOV reg/mem, immd\n");
		}
	}
	else if (Utility::IsMemory(operand.second))
	{
		if (Utility::Is8BitRegister(operand.first) || Utility::Is16BitRegister(operand.first))
		{
			//case 3 reg8/reg16, mem
			const std::string reg = operand.first;
			const std::string mem = operand.second;
			/*
				For 8Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-1-0 => 8A
				For 16Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-1-1 => 8B
				[*]Special Case when reg is AL and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-0-0 => A0, Second byte of opcode will be data directly 
				[*]Special Case when reg is AX and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-0-1 => A1, Second byte of opcode will be data directly 
			*/

			const std::string& exp = mem.substr(1, mem.length() - 2);//[] removed
			const std::string& fExp = Converter::ExpressionForModRM(exp); 
			
			std::string displacement = ""; 
			bool onlyDisp = Utility::ExtractHexFromMemExp(exp, displacement);
			
			//Checking for Special Case
			if (onlyDisp && (reg == REGISTER::AL || reg == REGISTER::AX))
			{
				//Special Cases
				Utility::Format16Bit(displacement);
				if (reg == REGISTER::AL)
				{
					out << "A0" << ' ' << displacement.substr(2, 2) << ' ' << displacement.substr(0, 2) << '\n';
				}
				else if(reg == REGISTER::AX)
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
					Error::LOG("Unexpected expression in []\n");
				}
			}
		}
		else
		{
			//error
			Error::LOG("Expected MOV reg8/reg16, mem\n");
		}
	}
	else if (Utility::IsMemory(operand.first))
	{
		if (Utility::Is8BitRegister(operand.second) || Utility::Is16BitRegister(operand.second))
		{
			//Case 4: mem, reg8/reg16
			const std::string& mem = operand.first;
			const std::string& reg = operand.second;

			/*
				For 8Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-0-0 => 88
				For 16Bit Register	=> Opcode(6)-d(1)-w(1) => 100010-0-1 => 89
				[*]Special Case when reg is AL and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-1-0 => A2, Second byte of opcode will be data directly
				[*]Special Case when reg is AX and mem exp is contaning displacement only i.e., [DATA]=> Opcode(6)-d(1)-w(1) => 101000-1-1 => A3, Second byte of opcode will be data directly
			*/
			const std::string& exp = mem.substr(1, mem.length() - 2);//[] removed
			const std::string& fExp = Converter::ExpressionForModRM(exp); 

			std::string displacement = "";
			bool onlyDisp = Utility::ExtractHexFromMemExp(exp, displacement);


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
					Error::LOG("Unexpected expression in []\n");
				}
			}
		}
		else
		{
			//error
			Error::LOG("Expected MOV mem, reg8/reg16\n");
		}
	}
	else if (Utility::IsSegmentRegister(operand.first))
	{
		//Case 5
		if (Utility::Is16BitRegister(operand.second))
		{

		}
		else
		{
			//error
			Error::LOG("Expected MOV sreg, reg16\n");
		}
	}
	else if (Utility::IsSegmentRegister(operand.second))
	{
		//Case 6
		if (Utility::Is16BitRegister(operand.first))
		{

		}
		else
		{
			//error
			Error::LOG("Expected MOV reg16, sreg\n");
		}
	}
	return true;
}