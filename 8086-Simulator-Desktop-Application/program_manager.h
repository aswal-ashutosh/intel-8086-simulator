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
			[x]1)MOV reg8/reg16, immd8/immd16 || MOV m, immd8/immd16
			[OK]2)MOV reg8/reg16, reg8/reg16
			3)MOV reg8/reg16, mem
			4)MOV mem, reg8/reg16
			5)MOV sreg, reg16
			6)MOV reg16, sreg
			
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
		//case 3 reg8/reg16, mem

		if (Utility::Is8BitRegister(operand.first))
		{
			//reg8, mem
			const std::string reg8 = operand.first;
			const std::string mem = operand.second;
			//Opcode(6)-d(1)-w(1) => 100010-1-0 => 8A
			const std::string &opcode = "8A";
			const std::string& exp = mem.substr(1, mem.length() - 2);
			const std::string& fExp = Converter::ExpressionForModRM(exp); //[] removed
			if (MOD_RM.count(fExp))
			{
				//mod(2)-reg(3)-r/m(3) => mod-Reg_CODE(first)-r/m_code
				const MOD_RM_INFO &info = MOD_RM.find(fExp)->second;

				Byte _2ndByte = info.mod << 6; //mod
				_2ndByte |= REG_CODE.find(reg8)->second << 3; // reg
				_2ndByte |= info.rm;

				std::string _2ndByteHex = Converter::DecToHex(_2ndByte);

				out << opcode << ' ' << _2ndByteHex.substr(0, 2);
				
				//there may be displacement data in expersion
				const std::vector<std::string> &afterSplit = Utility::SplitBy(exp, '+');//memory exp without []
				bool found = false;
				for (const std::string& s : afterSplit)
				{
					if (Utility::IsValidHex(s))
					{
						
						found = true;
						if (Utility::HexSize(s) == "8")
						{
							
							std::string data = s;
							//may be data is represented using redundatn hex digit eg: 001Ah, 010H
							Utility::Format16Bit(data);
							data = data.substr(2); // Truncating redundant digits and formatting it in 8-bit form

							//if mem exp is just containing dispacemnt then it will be considered as 16-bit data
							if (afterSplit.size() == 1)
							{
								out << ' ' << data.substr(0, 2) << ' ' << "00\n";
							}
							else
							{
								out << ' ' << data.substr(0, 2) << '\n';
							}
						}
						else
						{
							std::string data = s;
							Utility::Format16Bit(data);
							out << ' ' << data.substr(2, 2) << ' ' << data.substr(0, 2) << '\n';
						}
						break;
					}
				}

				if (!found) { out << '\n'; }
				
			}
			else
			{
				Error::LOG("Unexpected expression in []\n");
			}
		}
		else if (Utility::Is16BitRegister(operand.first))
		{

		}
		else
		{
			//error
			Error::LOG("Expected MOV reg8/reg16, mem\n");
		}
	}
	else if (Utility::IsMemory(operand.first))
	{
		//mem, reg8/reg16

		//Case 4
		if (Utility::Is8BitRegister(operand.second))
		{
			//mem, reg8

			const std::string& mem = operand.first;
			const std::string& reg8 = operand.second;
			//Opcode(6)-d(1)-w(1) => 100010-0-0 => 88
			const std::string& opcode = "88";
			const std::string& exp = mem.substr(1, mem.length() - 2);
			const std::string& fExp = Converter::ExpressionForModRM(exp); //[] removed
			Error::Debug(exp);
			if (MOD_RM.count(fExp))
			{
				//mod(2)-reg(3)-r/m(3) => mod-Reg_CODE(first)-r/m_code
				const MOD_RM_INFO& info = MOD_RM.find(fExp)->second;

				Byte _2ndByte = info.mod << 6; //mod
				_2ndByte |= REG_CODE.find(reg8)->second << 3; // reg
				_2ndByte |= info.rm;

				std::string _2ndByteHex = Converter::DecToHex(_2ndByte);

				out << opcode << ' ' << _2ndByteHex.substr(0, 2);

				//there may be displacement data in expersion
				const std::vector<std::string>& afterSplit = Utility::SplitBy(exp, '+');//memory exp without []
				bool found = false;
				for (const std::string& s : afterSplit)
				{
					if (Utility::IsValidHex(s))
					{

						found = true;
						if (Utility::HexSize(s) == "8")
						{

							std::string data = s;
							//may be data is represented using redundatn hex digit eg: 001Ah, 010H
							Utility::Format16Bit(data);
							data = data.substr(2); // Truncating redundant digits and formatting it in 8-bit form

							//if mem exp is just containing dispacemnt then it will be considered as 16-bit data
							if (afterSplit.size() == 1)
							{
								out << ' ' << data.substr(0, 2) << ' ' << "00\n";
							}
							else
							{
								out << ' ' << data.substr(0, 2) << '\n';
							}
						}
						else
						{
							std::string data = s;
							Utility::Format16Bit(data);
							out << ' ' << data.substr(2, 2) << ' ' << data.substr(0, 2) << '\n';
						}
						break;
					}
				}

				if (!found) { out << '\n'; }

			}
			else
			{
				Error::LOG("Unexpected expression in []\n");
			}

		}
		else if (Utility::Is16BitRegister(operand.second))
		{

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