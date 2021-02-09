#pragma once
#include"typedef.h"
#include<unordered_map>

class Register
{
	static _16Bit _IP;

	static std::unordered_map<std::string, Byte> REG8;		//For 8-Bit Parts of 16-Bit Registers
	static std::unordered_map<std::string, _16Bit> REG16;	//For 16-Bit Registers

	//Function to Sync 8 Bit Register with 16Bit Register
	static void Sync16BitWith8Bit(_16Bit&, const Byte&, const bool);	//When 8-Bit Get Changed, bool = true -> R8 are Higer 8-Bit else Lower 8-Bit
	static void Sync8BitWith16Bit(const _16Bit&, Byte&, Byte&);			//When 16-Bit Get Changed

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
	_16Bit CS();
	_16Bit DS();
	_16Bit SS();
	_16Bit ES();
	_16Bit IP();

	_16Bit AX();
	_16Bit BX();
	_16Bit CX();
	_16Bit DX();

	_16Bit SP();
	_16Bit BP();
	_16Bit SI();
	_16Bit DI();

	Byte AL();
	Byte BL();
	Byte CL();
	Byte DL();

	Byte AH();
	Byte BH();
	Byte CH();
	Byte DH();

	/*SETTERS*/
	void CS(const _16Bit&);
	void DS(const _16Bit&);
	void SS(const _16Bit&);
	void ES(const _16Bit&);

	void IP_INC(const _16Bit&); /*Function to increment IP*/
	void IP(const _16Bit&);

	void SP(const _16Bit&);
	void BP(const _16Bit&);
	void SI(const _16Bit&);
	void DI(const _16Bit&);

	void AX(const _16Bit&);
	void BX(const _16Bit&);
	void CX(const _16Bit&);
	void DX(const _16Bit&);

	void AL(const Byte&);
	void BL(const Byte&);
	void CL(const Byte&);
	void DL(const Byte&);

	void AH(const Byte&);
	void BH(const Byte&);
	void CH(const Byte&);
	void DH(const Byte&);
};

std::unordered_map<std::string, Byte> Register::REG8 =
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

std::unordered_map<std::string, _16Bit> Register::REG16 =
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

	for (int i = 8; i < 15; ++i)
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

/*GETTERS*/
_16Bit Register::CS() { return REG16[REGISTER::CS]; }
_16Bit Register::DS() { return REG16[REGISTER::DS]; }
_16Bit Register::SS() { return REG16[REGISTER::SS]; }
_16Bit Register::ES() { return REG16[REGISTER::ES]; }

_16Bit Register::IP() { return _IP; }

_16Bit Register::SP() { return REG16[REGISTER::SP]; }
_16Bit Register::BP() { return REG16[REGISTER::BP]; }
_16Bit Register::SI() { return REG16[REGISTER::SI]; }
_16Bit Register::DI() { return REG16[REGISTER::DI]; }

_16Bit Register::AX() { return REG16[REGISTER::AX]; }
_16Bit Register::BX() { return REG16[REGISTER::BX]; }
_16Bit Register::CX() { return REG16[REGISTER::CX]; }
_16Bit Register::DX() { return REG16[REGISTER::DX]; }

Byte Register::AL() { return REG8[REGISTER::AL]; }
Byte Register::BL() { return REG8[REGISTER::BL]; }
Byte Register::CL() { return REG8[REGISTER::CL]; }
Byte Register::DL() { return REG8[REGISTER::DL]; }

Byte Register::AH() { return REG8[REGISTER::AH]; }
Byte Register::BH() { return REG8[REGISTER::BH]; }
Byte Register::CH() { return REG8[REGISTER::CH]; }
Byte Register::DH() { return REG8[REGISTER::DH]; }

/*SETTERS*/
void Register::CS(const _16Bit& data) { REG16[REGISTER::CS] = data; }
void Register::DS(const _16Bit& data) { REG16[REGISTER::DS] = data; }
void Register::SS(const _16Bit& data) { REG16[REGISTER::SS] = data; }
void Register::ES(const _16Bit& data) { REG16[REGISTER::ES] = data; }

//[TODO]::OVERFLOW CHECKER[May be required]
void Register::IP_INC(const _16Bit& data) { _IP += data; }/*Function to increment IP*/
void Register::IP(const _16Bit& data) { _IP = data; }

void Register::SP(const _16Bit& data) { REG16[REGISTER::SP] = data; }
void Register::BP(const _16Bit& data) { REG16[REGISTER::BP] = data; }
void Register::SI(const _16Bit& data) { REG16[REGISTER::SI] = data; }
void Register::DI(const _16Bit& data) { REG16[REGISTER::DI] = data; }

//[TODO]::Sync 16Bit with 8Bit

void Register::AX(const _16Bit& data) { REG16[REGISTER::AX] = data; Sync8BitWith16Bit(REG16[REGISTER::AX], REG8[REGISTER::AH], REG8[REGISTER::AL]); };
void Register::BX(const _16Bit& data) { REG16[REGISTER::BX] = data; Sync8BitWith16Bit(REG16[REGISTER::BX], REG8[REGISTER::BH], REG8[REGISTER::BL]); };
void Register::CX(const _16Bit& data) { REG16[REGISTER::CX] = data; Sync8BitWith16Bit(REG16[REGISTER::CX], REG8[REGISTER::CH], REG8[REGISTER::CL]); };
void Register::DX(const _16Bit& data) { REG16[REGISTER::DX] = data; Sync8BitWith16Bit(REG16[REGISTER::DX], REG8[REGISTER::DH], REG8[REGISTER::DL]); };

void Register::AL(const Byte& data) { REG8[REGISTER::AL] = data; Sync16BitWith8Bit(REG16[REGISTER::AX], REG8[REGISTER::AL], false); }
void Register::BL(const Byte& data) { REG8[REGISTER::BL] = data; Sync16BitWith8Bit(REG16[REGISTER::BX], REG8[REGISTER::BL], false); }
void Register::CL(const Byte& data) { REG8[REGISTER::CL] = data; Sync16BitWith8Bit(REG16[REGISTER::CX], REG8[REGISTER::CL], false); }
void Register::DL(const Byte& data) { REG8[REGISTER::DL] = data; Sync16BitWith8Bit(REG16[REGISTER::DX], REG8[REGISTER::DL], false); }

void Register::AH(const Byte& data) { REG8[REGISTER::AH] = data; Sync16BitWith8Bit(REG16[REGISTER::AX], REG8[REGISTER::AH], true); }
void Register::BH(const Byte& data) { REG8[REGISTER::BH] = data; Sync16BitWith8Bit(REG16[REGISTER::BX], REG8[REGISTER::BH], true); }
void Register::CH(const Byte& data) { REG8[REGISTER::CH] = data; Sync16BitWith8Bit(REG16[REGISTER::CX], REG8[REGISTER::CH], true); }
void Register::DH(const Byte& data) { REG8[REGISTER::DH] = data; Sync16BitWith8Bit(REG16[REGISTER::DX], REG8[REGISTER::DH], true); }
