#pragma once
#include"typedef.h"
#include<unordered_map>
#include"converter.h"

class Register
{
	static _16Bit _IP;

	static std::unordered_map<std::string, Byte> _REG8;		//For 8-Bit Parts of 16-Bit Registers
	static std::unordered_map<std::string, _16Bit> _REG16;	//For 16-Bit Registers

	/*<<<<<<<<<<<<<<HELPER FUNCTIONS>>>>>>>>>>>>>>>>*/

	//Function to Sync 8 Bit Register with 16Bit Register and vice-e-versa
	static void Sync16BitWith8Bit(_16Bit&, const Byte&, const bool);	//When 8-Bit Get Changed, bool = true -> R8 are Higer 8-Bit else Lower 8-Bit
	static void Sync8BitWith16Bit(const _16Bit&, Byte&, Byte&);			//When 16-Bit Get Changed

	//Return true if register is a 16Bit General Purposer Register
	static bool IsGenReg16(const std::string&);
	//Function to get parent(Register to which they belong) registers of 8-Bit registers
	static std::string ParentRegister(const std::string&);
	//Function to get Lower Child of a 16-Bit register
	static std::string LowerChild(const std::string&);
	//Function to get Higher Child of a 16-Bit register
	static std::string HigherChild(const std::string&);
	//Function to check whether the 8-Bit register Higher or Lower
	static bool Order(const std::string&); // true => Hihger, false => Lower


	/*<<<<<<<<<<<<<<<<<<<<<<<<<<FLAG REGISTER>>>>>>>>>>>>>>>>>>>>>>>>>*/
	/*
		Flag Register Structure
		[][][][][OF][DF][IF][TF][SF][ZF][][AF][][PF][][CF]
	*/
	
	static _16Bit Flag;

public:

	/*GETTERS*/
	static Byte REG8(const std::string&);
	static _16Bit REG16(const std::string&);

	/*SETTERS*/
	static void REG8(const std::string&, const Byte);
	static void REG16(const std::string&, const _16Bit);

	static void IP_INC(const _16Bit&); /*Function to increment IP*/
	static void IP(const _16Bit&);

	//Testing Functions
	static void PrintAll();

	/*<<<<<<<<<<<<<<<<<<<<<<<<<<FLAG REGISTER>>>>>>>>>>>>>>>>>>>>>>>>>*/

	enum class FLAG
	{
		CF = 1 << 0,
		PF = 1 << 2,
		AF = 1 << 4,
		ZF = 1 << 6,
		SF = 1 << 7,
		DF = 1 << 10,
		OF = 1 << 11,
	};
	
	static void SetFlag(const FLAG&, const bool&);
	static bool GetFlag(const FLAG&);

	static void UpdateFlags8Bit(const Byte, const Byte, const _16Bit, const bool);
	static void UpdateFlags16Bit(const _16Bit, const _16Bit, const int, const bool);

};

_16Bit Register::_IP;
_16Bit Register::Flag;

std::unordered_map<std::string, Byte> Register::_REG8 =
{
	{REGISTER::AL, 0},
	{REGISTER::BL, 0},
	{REGISTER::CL, 0},
	{REGISTER::DL, 0},
	{REGISTER::AH, 0},
	{REGISTER::BH, 0},
	{REGISTER::CH, 0},
	{REGISTER::DH, 0},
};

std::unordered_map<std::string, _16Bit> Register::_REG16 =
{
	{REGISTER::CS, 0},
	{REGISTER::DS, 0},
	{REGISTER::SS, 0},
	{REGISTER::ES, 0},

	{REGISTER::AX, 0},
	{REGISTER::BX, 0},
	{REGISTER::CX, 0},
	{REGISTER::DX, 0},

	{REGISTER::SP, 0},
	{REGISTER::BP, 0},
	{REGISTER::DI, 0},
	{REGISTER::SI, 0},
};

//Flag Register//
void Register::SetFlag(const FLAG& X, const bool& state)
{
	if (state)
	{
		Flag |= _16Bit(X);
	}
	else
	{
		Flag &= ~_16Bit(X);
	}
}

bool Register::GetFlag(const FLAG& X)
{
	return Flag & _16Bit(X);
}

void Register::UpdateFlags8Bit(const Byte OP1, const Byte OP2, const _16Bit Result, const bool WithCarry = false)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Register::SetFlag(FLAG::CF, Result > 0x00ff); //Carry Flag
	Register::SetFlag(FLAG::AF, (OP1 & 0x0f) + (OP2 & 0x0f) > 0x0f); //Auxillary Carry Flag
	Byte Result8Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
	if (WithCarry)
	{
		_16Bit ResOP2_CF = _16Bit(OP2) + _16Bit(oldCF);
		bool OF = false;
		if ((OP2 & (1 << 7)) ^ (Byte(oldCF) & (1 << 7)))
		{
			OF = false;
		}
		else
		{
			OF = (ResOP2_CF & (1 << 7)) ^ (OP2 & (1 << 7));
		}

		ResOP2_CF = Byte(ResOP2_CF); //Truncating Extra Bits

		_16Bit ResFinal = OP1 + ResOP2_CF;

		if ((OP1 & (1 << 7)) ^ (ResOP2_CF & (1 << 7)))
		{
			//Different Sign
			Register::SetFlag(FLAG::OF, OF);
		}
		else
		{
			//Same Sign
			Register::SetFlag(FLAG::OF, OF | ((ResFinal & (1 << 7)) ^ (OP1 & (1 << 7))));
		}
	}
	else
	{
		if ((OP1 & (1 << 7)) ^ (OP2 & (1 << 7)))
		{
			//Different Sign
			Register::SetFlag(FLAG::OF, false);
		}
		else
		{
			//Same Sign
			Register::SetFlag(FLAG::OF, (Result8Bit & (1 << 7)) ^ (OP1 & (1 << 7)));
		}
	}
	
	Register::SetFlag(FLAG::PF, !(Utility::SetBitCount(Result8Bit) & 1)); //Parity Flag

	Register::SetFlag(FLAG::SF, Result8Bit & (1 << 7)); //Sign Flag

	Register::SetFlag(FLAG::ZF, Result8Bit == 0x00);

	/*[TODO][DF]*/
}

void Register::UpdateFlags16Bit(const _16Bit OP1, const _16Bit OP2, const int Result, const bool WithCarry = false)
{
	bool oldCF = Register::GetFlag(Register::FLAG::CF);
	Register::SetFlag(FLAG::CF, Result > 0xffff); //Carry Flag
	_16Bit Result16Bit = Result; //Truncating Extra Bits

	//Over Flow Flag
	if (WithCarry)
	{
		int ResOP2_CF = int(OP2) + int(oldCF);
		bool OF = false;

		if ((OP2 & (1 << 15)) ^ (_16Bit(oldCF) & (1 << 15)))
		{
			OF = false;
		}
		else
		{
			OF = (ResOP2_CF & (1 << 15)) ^ (OP2 & (1 << 15));
		}

		ResOP2_CF = _16Bit(ResOP2_CF); //Truncating Extra Bits

		int ResFinal = OP1 + ResOP2_CF;

		if ((OP1 & (1 << 15)) ^ (ResOP2_CF & (1 << 15)))
		{
			//Different Sign
			Register::SetFlag(FLAG::OF, OF);
		}
		else
		{
			//Same Sign
			Register::SetFlag(FLAG::OF, OF | ((ResFinal & (1 << 15)) ^ (OP1 & (1 << 15))));
		}
	}
	else
	{
		if ((OP1 & (1 << 15)) ^ (OP2 & (1 << 15)))
		{
			//Different Sign
			Register::SetFlag(FLAG::OF, false);
		}
		else
		{
			//Same Sign
			Register::SetFlag(FLAG::OF, (Result16Bit & (1 << 15)) ^ (OP1 & (1 << 15)));
		}
	}
	


	Register::SetFlag(FLAG::PF, !(Utility::SetBitCount(Result16Bit) & 1)); //Parity Flag

	Register::SetFlag(FLAG::SF, Result16Bit & (1 << 15)); //Sign Flag

	Register::SetFlag(FLAG::ZF, Result16Bit == 0x0000);

	/*[TODO][DF]*/
}

void Register::PrintAll()
{
	for (const std::pair<const std::string, Byte>& R : _REG8)
	{
		const std::string& data = Converter::DecToHex(R.second);
		std::cout << R.first << ":[" << "\x1B[32m" + data + "\x1B[0m" << "]\n";
	}

	for (const std::pair<const std::string, _16Bit>& R : _REG16)
	{
		const std::string& data = Converter::DecToHex(R.second, HexSize::_16Bit);
		std::cout << R.first << ":[" << "\x1B[32m" + data + "\x1B[0m" << "]\n";
	}

	std::cout << "OF:[" << (GetFlag(FLAG::OF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "DF:[" << (GetFlag(FLAG::DF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "SF:[" << (GetFlag(FLAG::SF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "ZF:[" << (GetFlag(FLAG::ZF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "AF:[" << (GetFlag(FLAG::AF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "PF:[" << (GetFlag(FLAG::PF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "CF:[" << (GetFlag(FLAG::CF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "]\n";
}

void Register::Sync16BitWith8Bit(_16Bit& R16, const Byte& R8, const bool high)
{
	for (int i = 0, k = high ? 8 : 0; i < 8; ++i, ++k)
	{
		if (R8 & (1 << i))
		{
			//i-th bit is set
			R16 |= _16Bit(1) << k;
		}
		else
		{
			//i-th bit is reset
			R16 &= ~(_16Bit(1) << k);
		}
	}
}

void Register::Sync8BitWith16Bit(const _16Bit& R16, Byte& R8H, Byte& R8L)
{
	//Lower
	for (int i = 0; i < 8; ++i)
	{
		if (R16 & (1 << i))
		{
			//i-th bit is set
			R8L |= _16Bit(1) << i;
		}
		else
		{
			//i-th bit is reset
			R8L &= ~(_16Bit(1) << i);
		}
	}

	for (int i = 8; i < 16; ++i)
	{
		if (R16 & (1 << i))
		{
			//i-th bit is set
			R8H |= _16Bit(1) << (i - 8);
		}
		else
		{
			//i-th bit is reset
			R8H &= ~(_16Bit(1) << (i - 8));
		}
	}
}

bool Register::IsGenReg16(const std::string& R)
{
	bool OK = false;
	OK |= R == REGISTER::AX;
	OK |= R == REGISTER::BX;
	OK |= R == REGISTER::CX;
	OK |= R == REGISTER::DX;
	return OK;
}


std::string Register::ParentRegister(const std::string& R)
{
	//Replace last character with 'X' 
	return R.substr(0, 1) + 'X';
}

std::string Register::LowerChild(const std::string& R)
{
	//Replace last character with 'L'
	return R.substr(0, 1) + 'L';
}

std::string Register::HigherChild(const std::string& R)
{
	//Replace last character with 'H'
	return R.substr(0, 1) + 'H';
}

bool Register::Order(const std::string& R)
{
	return R.back() == 'H';
}

//[TODO]::REMOVE DEBUG In final version

/*GETTERS*/
Byte Register::REG8(const std::string& R)
{
	if (_REG8.count(R))
	{
		return _REG8[R];
	}
	else
	{
		Error::Debug(R + " is not 8-Bit Register @ Getter\n");
	}
}

_16Bit Register::REG16(const std::string& R)
{
	if (_REG16.count(R))
	{
		return _REG16[R];
	}
	else
	{
		Error::Debug(R + " is not 16-Bit Register @ Getter\n");
	}
}

/*SETTERS*/
void Register::REG8(const std::string& R, const Byte data)
{
	if (_REG8.count(R))
	{
		_REG8[R] = data;
		Sync16BitWith8Bit(_REG16[ParentRegister(R)], _REG8[R], Order(R));
	}
	else
	{
		Error::Debug(R + "is not 8-Bit Register @ Setter\n");
	}
}


void Register::REG16(const std::string& R, const _16Bit data)
{
	if (_REG16.count(R))
	{
		_REG16[R] = data;
		if (IsGenReg16(R))
		{
			Sync8BitWith16Bit(_REG16[R], _REG8[HigherChild(R)], _REG8[LowerChild(R)]);
		}
	}
	else
	{
		Error::Debug(R + "is not 16-Bit Register @ Setter\n");
	}
}

//[TODO]::OVERFLOW CHECKER[May be required]
void Register::IP_INC(const _16Bit& data) { _IP += data; }/*Function to increment IP*/
void Register::IP(const _16Bit& data) { _IP = data; }

