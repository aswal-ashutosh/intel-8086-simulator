#pragma once
#include"typedef.h"
#include<unordered_map>

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

	//Flag Registers
	class Flag
	{
		static bool _OF;//Overflow Flag
		static bool _DF;//Direction Flag
		static bool _IF;//Interrupt Flag
		static bool _TF;//Trap Flag
		static bool _SF;//Sign Flag
		static bool _ZF;//Zero Flag
		static bool _AF;//Auxilary Carry Flag
		static bool _PF;//Parity Flag
		static bool _CF;//Carry Flag
	public:
	};

public:

	/*GETTERS*/
	static Byte REG8(const std::string&);
	static _16Bit REG16(const std::string&);

	/*SETTERS*/
	static void REG8(const std::string&, const Byte&);
	static void REG16(const std::string&, const _16Bit&);

	static void IP_INC(const _16Bit&); /*Function to increment IP*/
	static void IP(const _16Bit&);

};

_16Bit Register::_IP;

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
		Error::Debug(R + "is not 8-Bit Register @ Getter\n");
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
		Error::Debug(R + "is not 16-Bit Register @ Getter\n");
	}
}

/*SETTERS*/
void Register::REG8(const std::string& R, const Byte& data)
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


void Register::REG16(const std::string& R, const _16Bit& data)
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

