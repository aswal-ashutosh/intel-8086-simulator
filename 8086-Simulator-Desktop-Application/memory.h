#pragma once
#include"typedef.h"
#include"converter.h"

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

	static void Set(int loc, int val)
	{
		mem[loc] = val;
	}

	static void DebugMem(int s, int e)
	{
		for (int i = s; i <= e; ++i)
		{
			std::cout << Converter::MemLocHex(i) << ": " << Converter::DecToHex(mem[i]) << '\n';
		}
	}
};

Byte Memory::mem[1 << 20] = { 0 };