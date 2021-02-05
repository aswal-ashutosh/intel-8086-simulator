#pragma once
#include"typedef.h"
class Register
{
public:
	/*
	<<<<<<<<<<<<<<CS REGISTER>>>>>>>>>>>>>>>>>>>>>
	[1]CS holds the base address for the Code Segment.
	[2]All Programs are stored in the Code Segment.
	[3]It is multiplied by 10H, to give the 20-bit physical address of Code Segment.
	Eg: If CS = 4321H then CS x 10H = 43210H will the starting address of Code Segment.
	*/
	static _16Bit CS;

	/*
	<<<<<<<<<<<<<<<<<DS REGISTER>>>>>>>>>>>>>>>>>>>>>
	[x]DS holds the base Address for the Data Segment.
	[x]It is multiplid by 10H, to give the 20-bit physical address of the Data Segment.
	Eg: If DS = 4321H then DS × 10H = 43210H è Starting address of Data Segment.
	*/
	static _16Bit DS;

	/*
	<<<<<<<<<<<<<<<<<<<SS REGISTER>>>>>>>>>>>>>>>>>>>
	[1]SS holds the base (Segment) address for the Stack Segment.
	[2]It is multiplied by 10H (16d), to give the 20-bit physical address of the Stack Segment.
	Eg: If SS = 4321H then SS × 10H = 43210H è Starting address of Stack Segment.
	*/
	static _16Bit SS;

	/*
	<<<<<<<<<<<<<<<<<<ES REGISTER>>>>>>>>>>>>>>>>>>>>
	[1]ES holds the base (Segment) address for the Extra Segment.
	[2]It is multiplied by 10H (16d), to give the 20-bit physical address of the Extra Segment.
	Eg: If ES = 4321H then ES × 10H = 43210H è Starting address of Extra Segment.
	*/
	static _16Bit ES;

	/*
	<<<<<<<<<<<<<<<<<<INSTRUCTION POINTER>>>>>>>>>>>>>>>>
	[1]It is a 16Bit Register.
	[2]It holds offest to the next permutation in the Code Segment.
	[3][IMPORTANT] Address of the next instruction is calculated as CS x 10H + IP.
	[4]IP is incrementd after every instruction byte is fetched.
	*/
	static _16Bit IP;

	static _16Bit AX; //AX Register(16-Bits)
	static _16Bit BX; //BX Register(16-Bits)
	static _16Bit CX; //CX Register(16-Bits)
	static _16Bit DX; //DX Register(16-Bits)


	static _16Bit SP;//Stack Pointer(16-Bits)
	static _16Bit BP;//Base Pointer(16-Bits)
	static _16Bit SI;//Source Index(16-Bits)
	static _16Bit DI;//Destination Index(16Bits)

	//Flag Registers
	class Flag
	{
		static bool OF;//Overflow Flag
		static bool DF;//Direction Flag
		static bool IF;//Interrupt Flag
		static bool TF;//Trap Flag
		static bool SF;//Sign Flag
		static bool ZF;//Zero Flag
		static bool AF;//Auxilary Carry Flag
		static bool PF;//Parity Flag
		static bool CF;//Carry Flag
	};
};