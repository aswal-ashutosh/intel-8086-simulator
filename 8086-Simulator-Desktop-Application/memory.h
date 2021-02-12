#pragma once
#include"typedef.h"
#include"converter.h"
#include"utility.h"
#include"error_handler.h"

struct MemData
{
	int loc;
	int val;
	MemData(int _loc, int _val) :loc(_loc), val(_val)
	{

	}
};

class Memory
{
	static Byte mem[1 << 20];
public:
	static void SetData()
	{

	}

	template<typename HEAD, typename... TAIL>
	static void SetData(HEAD H, TAIL... T)
	{
		mem[H.loc] = H.val;
		SetData(T...);
	}

	static void Set(int loc, Byte val)
	{
		mem[loc] = val;
	}

	static Byte Get(int physicalAddress)
	{
		return mem[physicalAddress];
	}


	static Byte Get(int address, int offset)
	{
		if (address * 0x10 + offset > 0xfffff)
		{
			Error::Debug("Note valid Address+offset\n");
		}
		return mem[address * 0x10 + offset];
	}

	static void DebugMem(int s, int offset, int cnt)
	{
		std::string address = Converter::DecToHex(s, Type::_16);

		for (int i = 0; i < cnt; ++i)
		{
			int physcialAddress = s * 0x10 + (offset + i);
			std::string off = Converter::DecToHex(offset + i, Type::_16);
			std::cout << address << '-' << off << ": " << Converter::DecToHex(mem[physcialAddress]) << '\n';
		}
	}

	//Function to get physical address from [exp]
	static int PhysicalAddress(const std::string&);
};

Byte Memory::mem[1 << 20] = { 0 };

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
