#pragma once
#include"typedef.h"
#include<unordered_map>
#include"converter.h"

class Register
{
	static Word _IP;

	static std::unordered_map<std::string, Byte> _REG8;		//For 8-Bit Parts of 16-Bit Registers
	static std::unordered_map<std::string, Word> _REG16;	//For 16-Bit Registers

	/*<<<<<<<<<<<<<<HELPER FUNCTIONS>>>>>>>>>>>>>>>>*/

	//Function to Sync 8 Bit Register with 16Bit Register and vice-e-versa
	static void Sync16BitWith8Bit(Word&, const Byte&, const bool);	//When 8-Bit Get Changed, bool = true -> R8 are Higer 8-Bit else Lower 8-Bit
	static void Sync8BitWith16Bit(const Word&, Byte&, Byte&);			//When 16-Bit Get Changed

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
	
	static Word Flag;

public:

	/*GETTERS*/
	static Byte REG8(const std::string&);
	static Word REG16(const std::string&);

	/*SETTERS*/
	static void REG8(const std::string&, const Byte);
	static void REG16(const std::string&, const Word);

	//static void IP_INC(const Word&); /*Function to increment IP*/
	static void IP(const Word&);

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
};

Word Register::_IP;
Word Register::Flag;

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

std::unordered_map<std::string, Word> Register::_REG16 =
{
	{REGISTER::CS, 0x0000},
	{REGISTER::SS, 0x4000},
	{REGISTER::DS, 0x8000},
	{REGISTER::ES, 0xC000},

	{REGISTER::AX, 0},
	{REGISTER::BX, 0},
	{REGISTER::CX, 0},
	{REGISTER::DX, 0},

	{REGISTER::SP, 0xFFFF},
	{REGISTER::BP, 0},
	{REGISTER::DI, 0},
	{REGISTER::SI, 0},
};

//Flag Register//
void Register::SetFlag(const FLAG& X, const bool& state)
{
	if (state)
	{
		Flag |= Word(X);
	}
	else
	{
		Flag &= ~Word(X);
	}
}

bool Register::GetFlag(const FLAG& X)
{
	return Flag & Word(X);
}

void Register::PrintAll()
{
	std::cout << "\n.....................................\n\n";
	for (const std::pair<const std::string, Byte>& R : _REG8)
	{
		const std::string& data = Converter::DecToHex(R.second);
		std::cout << R.first << ":[" << "\x1B[32m" + data + "\x1B[0m" << "]\n";
	}

	for (const std::pair<const std::string, Word>& R : _REG16)
	{
		const std::string& data = Converter::DecToHex(R.second, SIZE::WORD);
		std::cout << R.first << ":[" << "\x1B[32m" + data + "\x1B[0m" << "]\n";
	}

	std::cout << "IP:[\x1B[32m" << Converter::DecToHex(_IP, SIZE::WORD) << "\x1b[0m]\n";

	std::cout << "OF:[" << (GetFlag(FLAG::OF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "DF:[" << (GetFlag(FLAG::DF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "SF:[" << (GetFlag(FLAG::SF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "ZF:[" << (GetFlag(FLAG::ZF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "AF:[" << (GetFlag(FLAG::AF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "PF:[" << (GetFlag(FLAG::PF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "] ";
	std::cout << "CF:[" << (GetFlag(FLAG::CF)? "\x1B[31m1\x1B[0m" : "\x1B[32m0\x1B[0m") << "]\n";
}

void Register::Sync16BitWith8Bit(Word& R16, const Byte& R8, const bool high)
{
	for (int i = 0, k = high ? 8 : 0; i < 8; ++i, ++k)
	{
		if (R8 & (1 << i))
		{
			//i-th bit is set
			R16 |= Word(1) << k;
		}
		else
		{
			//i-th bit is reset
			R16 &= ~(Word(1) << k);
		}
	}
}

void Register::Sync8BitWith16Bit(const Word& R16, Byte& R8H, Byte& R8L)
{
	//Lower
	for (int i = 0; i < 8; ++i)
	{
		if (R16 & (1 << i))
		{
			//i-th bit is set
			R8L |= Word(1) << i;
		}
		else
		{
			//i-th bit is reset
			R8L &= ~(Word(1) << i);
		}
	}

	for (int i = 8; i < 16; ++i)
	{
		if (R16 & (1 << i))
		{
			//i-th bit is set
			R8H |= Word(1) << (i - 8);
		}
		else
		{
			//i-th bit is reset
			R8H &= ~(Word(1) << (i - 8));
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
		//[TODO]::REMOVE DEBUG In final version
		Error::Debug(R + " is not 8-Bit Register @ Getter\n");
		return -1;
	}
}

Word Register::REG16(const std::string& R)
{
	if (_REG16.count(R))
	{
		return _REG16[R];
	}
	else
	{
		//[TODO]::REMOVE DEBUG In final version
		Error::Debug(R + " is not 16-Bit Register @ Getter\n");
		return -1;
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


void Register::REG16(const std::string& R, const Word data)
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
//void Register::IP_INC(const Word& data) { _IP += data; }/*Function to increment IP*/
void Register::IP(const Word& data) { _IP = data; }

