#pragma once
#include"typedef.h"
#include"converter.h"
#include"utility.h"
#include"error_handler.h"
#include"hex_size.h"


class Memory
{
	static Byte mem[1 << 20];
public:

	//Setters
	static void Set8Bit(const int, const Byte);
	static void Set16Bit(const int, const _16Bit);

	//Getters
	static Byte Get8Bit(const int);
	static _16Bit Get16Bit(const int);
	
	static void DebugMem(int s, int offset, int cnt)
	{
		std::string address = Converter::DecToHex(s, HexSize::_16Bit);

		for (int i = 0; i < cnt; ++i)
		{
			int physcialAddress = s * 0x10 + (offset + i);
			std::string off = Converter::DecToHex(offset + i, HexSize::_16Bit);
			std::cout << address << '-' << off << ":[" << "\x1B[32m" + Converter::DecToHex(mem[physcialAddress]) + "\x1B[0m]" << '\n';
		}
	}

	//Function to get physical address from [exp]
	static int PhysicalAddress(const std::string&);
};

Byte Memory::mem[1 << 20] = { 0 };

void Memory::Set8Bit(const int loc, const Byte data)
{
	if (loc < 0x00000 || loc > 0xfffff){ Error::Debug("Address out of range @Set8Bit\n"); }
	mem[loc] = data;
}

void Memory::Set16Bit(const int loc, const _16Bit data)
{
	if (loc < 0x00000 || loc > 0xfffff) { Error::Debug("Address out of range @Set16Bit\n"); }
	Byte Lbyte = data & 0x00ff;
	Byte Hbyte = (data & 0xff00) >> 8;
	int pAddressL = loc;
	int pAddressH = loc + 1 > 0xfffff ? 0x00000 : loc + 1;	//Address should be in range[00000H-FFFFFH]
	mem[pAddressL] = Lbyte;
	mem[pAddressH] = Hbyte;
}

Byte Memory::Get8Bit(const int loc)
{
	if (loc < 0x00000 || loc > 0xfffff) { Error::Debug("Address out of range @Get8Bit\n"); }
	return mem[loc];
}

_16Bit Memory::Get16Bit(const int loc)
{
	if (loc < 0x00000 || loc > 0xfffff) { Error::Debug("Address out of range @Get8Bit\n"); }
	int pAddressL = loc;
	int pAddressH = loc + 1 > 0xfffff ? 0x00000 : loc + 1;	//Address should be in range[00000H-FFFFFH]
	_16Bit HigherData = mem[pAddressH];
	_16Bit LowerData = mem[pAddressL];
	return (HigherData << 8) | LowerData;
}

int Memory::PhysicalAddress(const std::string& mem)
{
	const std::string& exp = mem.substr(1, mem.length() - 2);//Removing []
	std::vector<std::string> afterSplit = Utility::SplitBy(exp, '+');
	int physicalAddress = 0;
	const std::string& first = afterSplit.front();

	if (first == REGISTER::BP)
	{
		physicalAddress = Register::REG16(REGISTER::SS) * 0x10;
	}
	else//Either BX or something else
	{
		physicalAddress = Register::REG16(REGISTER::DS) * 0x10;
	}

	for (const std::string& x : afterSplit)
	{
		if (Utility::IsValidHex(x))
		{
			physicalAddress += Converter::HexToDec(x);
		}
		else
		{
			physicalAddress += Register::REG16(x);
		}
	}

	return physicalAddress;
}
