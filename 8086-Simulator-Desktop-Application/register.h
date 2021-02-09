#pragma once
#include"typedef.h"
class Register
{
	/*
	<<<<<<<<<<<<<<CS REGISTER>>>>>>>>>>>>>>>>>>>>>
	[1]CS holds the base address for the Code Segment.
	[2]All Programs are stored in the Code Segment.
	[3]It is multiplied by 10H, to give the 20-bit physical address of Code Segment.
	Eg: If CS = 4321H then CS x 10H = 43210H will the starting address of Code Segment.
	*/
	static _16Bit _CS;

	/*
	<<<<<<<<<<<<<<<<<DS REGISTER>>>>>>>>>>>>>>>>>>>>>
	[x]DS holds the base Address for the Data Segment.
	[x]It is multiplid by 10H, to give the 20-bit physical address of the Data Segment.
	Eg: If DS = 4321H then DS × 10H = 43210H è Starting address of Data Segment.
	*/
	static _16Bit _DS;

	/*
	<<<<<<<<<<<<<<<<<<<SS REGISTER>>>>>>>>>>>>>>>>>>>
	[1]SS holds the base (Segment) address for the Stack Segment.
	[2]It is multiplied by 10H (16d), to give the 20-bit physical address of the Stack Segment.
	Eg: If SS = 4321H then SS × 10H = 43210H è Starting address of Stack Segment.
	*/
	static _16Bit _SS;

	/*
	<<<<<<<<<<<<<<<<<<ES REGISTER>>>>>>>>>>>>>>>>>>>>
	[1]ES holds the base (Segment) address for the Extra Segment.
	[2]It is multiplied by 10H (16d), to give the 20-bit physical address of the Extra Segment.
	Eg: If ES = 4321H then ES × 10H = 43210H è Starting address of Extra Segment.
	*/
	static _16Bit _ES;

	/*
	<<<<<<<<<<<<<<<<<<INSTRUCTION POINTER>>>>>>>>>>>>>>>>
	[1]It is a 16Bit Register.
	[2]It holds offest to the next permutation in the Code Segment.
	[3][IMPORTANT] Address of the next instruction is calculated as CS x 10H + IP.
	[4]IP is incrementd after every instruction byte is fetched.
	*/
	static _16Bit _IP;

	static _16Bit _AX; //AX Register(16-Bits)
	static _16Bit _BX; //BX Register(16-Bits)
	static _16Bit _CX; //CX Register(16-Bits)
	static _16Bit _DX; //DX Register(16-Bits)

	static Byte _AL, _AH; //AX Register as 2 8-Bit Registers
	static Byte _BL, _BH; //BX Register as 2 8-Bit Registers
	static Byte _CL, _CH; //CX Register as 2 8-Bit Registers
	static Byte _DL, _DH; //DX Register as 2 8-Bit Registers


	static _16Bit SP_;//Stack Pointer(16-Bits)
	static _16Bit BP_;//Base Pointer(16-Bits)
	static _16Bit SI_;//Source Index(16-Bits)
	static _16Bit DI_;//Destination Index(16Bits)

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

_16Bit Register::_CS;
_16Bit Register::_DS;
_16Bit Register::_SS;
_16Bit Register::_ES;


_16Bit Register::_IP;

_16Bit Register::_AX;
_16Bit Register::_BX;
_16Bit Register::_CX;
_16Bit Register::_DX;

_16Bit Register::SP_;
_16Bit Register::BP_;
_16Bit Register::SI_;
_16Bit Register::DI_;

Byte Register::_AL;
Byte Register::_BL;
Byte Register::_CL;
Byte Register::_DL;
Byte Register::_AH;
Byte Register::_BH;
Byte Register::_CH;
Byte Register::_DH;

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
_16Bit Register::CS() { return _CS; }
_16Bit Register::DS() { return _DS; }
_16Bit Register::SS() { return _SS; }
_16Bit Register::ES() { return _ES; }

_16Bit Register::IP() { return _IP; }

_16Bit Register::SP() { return SP_; }
_16Bit Register::BP() { return BP_; }
_16Bit Register::SI() { return SI_; }
_16Bit Register::DI() { return DI_; }

_16Bit Register::AX() { return _AX; }
_16Bit Register::BX() { return _BX; }
_16Bit Register::CX() { return _CX; }
_16Bit Register::DX() { return _DX; }

Byte Register::AL() { return _AL; }
Byte Register::BL() { return _BL; }
Byte Register::CL() { return _CL; }
Byte Register::DL() { return _DL; }

Byte Register::AH() { return _AH; }
Byte Register::BH() { return _BH; }
Byte Register::CH() { return _CH; }
Byte Register::DH() { return _DH; }

/*SETTERS*/
void Register::CS(const _16Bit& data) { _CS = data; }
void Register::DS(const _16Bit& data) { _DS = data; }
void Register::SS(const _16Bit& data) { _SS = data; }
void Register::ES(const _16Bit& data) { _ES = data; }

//[TODO]::OVERFLOW CHECKER[May be required]
void Register::IP_INC(const _16Bit& data) { _IP += data; }/*Function to increment IP*/
void Register::IP(const _16Bit& data) { _IP = data; }

void Register::SP(const _16Bit& data) { SP_ = data; }
void Register::BP(const _16Bit& data) { BP_ = data; }
void Register::SI(const _16Bit& data) { SI_ = data; }
void Register::DI(const _16Bit& data) { DI_ = data; }

//[TODO]::Sync 16Bit with 8Bit

void Register::AX(const _16Bit& data) { _AX = data; Sync8BitWith16Bit(_AX, _AH, _AL); };
void Register::BX(const _16Bit& data) { _BX = data; Sync8BitWith16Bit(_BX, _BH, _BL); };
void Register::CX(const _16Bit& data) { _CX = data; Sync8BitWith16Bit(_CX, _CH, _CL); };
void Register::DX(const _16Bit& data) { _DX = data; Sync8BitWith16Bit(_DX, _DH, _DL); };

void Register::AL(const Byte& data) { _AL = data; Sync16BitWith8Bit(_AX, _AL, false); }
void Register::BL(const Byte& data) { _BL = data; Sync16BitWith8Bit(_BX, _BL, false); }
void Register::CL(const Byte& data) { _CL = data; Sync16BitWith8Bit(_CX, _CL, false); }
void Register::DL(const Byte& data) { _DL = data; Sync16BitWith8Bit(_DX, _DL, false); }

void Register::AH(const Byte& data) { _AH = data; Sync16BitWith8Bit(_AX, _AH, true); }
void Register::BH(const Byte& data) { _BH = data; Sync16BitWith8Bit(_BX, _BH, true); }
void Register::CH(const Byte& data) { _CH = data; Sync16BitWith8Bit(_CX, _CH, true); }
void Register::DH(const Byte& data) { _DH = data; Sync16BitWith8Bit(_DX, _DH, true); }
