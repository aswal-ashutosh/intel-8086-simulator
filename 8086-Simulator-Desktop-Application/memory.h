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
	static void Set16Bit(const int, const Word);

	//Getters
	static Byte Get8Bit(const int);
	static Word Get16Bit(const int);
	
	//Function to get physical address from [exp]
	static int PhysicalAddress(const std::string&);

	//Whenever the provided location is greater than fffff it will truncate all the extra bits
	static int NormalizeLocation(int loc);
};

Byte Memory::mem[1 << 20] = { 0 };

int Memory::NormalizeLocation(int loc)
{
	for (int i = 20; i < 32; ++i)
	{
		loc &= ~(1 << i);
	}
	return loc;
}

void Memory::Set8Bit(const int loc, const Byte data)
{
	mem[NormalizeLocation(loc)] = data;
}

void Memory::Set16Bit(const int loc, const Word data)
{
	Byte Lbyte = data & 0x00ff;
	Byte Hbyte = (data & 0xff00) >> 8;
	int pAddressL = NormalizeLocation(loc);
	int pAddressH = pAddressL + 1 > 0xfffff ? 0x00000 : pAddressL + 1;	//Address should be in range[00000H-FFFFFH]
	mem[pAddressL] = Lbyte;
	mem[pAddressH] = Hbyte;
}

Byte Memory::Get8Bit(const int loc)
{
	return mem[NormalizeLocation(loc)];
}

Word Memory::Get16Bit(const int loc)
{
	int pAddressL = NormalizeLocation(loc);
	int pAddressH = pAddressL + 1 > 0xfffff ? 0x00000 : pAddressL + 1;	//Address should be in range[00000H-FFFFFH]
	Word HigherData = mem[pAddressH];
	Word LowerData = mem[pAddressL];
	return (HigherData << 8) | LowerData;
}

int Memory::PhysicalAddress(const std::string& mem)
{
	const std::string& exp = Utility::IsByteMemory(mem) ? mem.substr(1, mem.length() - 2) : mem.substr(2, mem.length() - 3);//Removing []/W[]
	std::vector<std::string> afterSplit = Utility::SplitBy(exp, '+');
	int physicalAddress = 0;
	const std::string& first = afterSplit.front();

	if (first == REGISTER::BP)
	{
		physicalAddress = (int)Register::REG16(REGISTER::SS) * 0x10;
	}
	else//Either BX or something else
	{
		physicalAddress = (int)Register::REG16(REGISTER::DS) * 0x10;
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

	return NormalizeLocation(physicalAddress);
}
