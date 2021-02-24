#pragma once
#include"8086.h"

bool ProgramExecutor::DAA(const Operand& operand)
{
	Word AL = Register::REG8(REGISTER::AL);
	if ((AL & 0xf) > 9 || Register::GetFlag(Register::FLAG::AF))
	{
		AL += 0x06;
		Register::SetFlag(Register::FLAG::AF, true);
	}

	//If carry is already set than don't change it, else check for its status(May be it become set after adding 0x06 in LSN).
	Register::SetFlag(Register::FLAG::CF, Register::GetFlag(Register::FLAG::CF) | (bool)(AL > 0xff));

	if (((AL & 0xf0) >> 4) > 9 || Register::GetFlag(Register::FLAG::CF))
	{
		AL += 0x60;
		Register::SetFlag(Register::FLAG::CF, true);
	}

	AL = (Byte)AL;

	Register::REG8(REGISTER::AL, (Byte)AL);
	Register::SetFlag(Register::FLAG::PF, !(Utility::SetBitCount(AL) & 1)); //Parity Flag
	Register::SetFlag(Register::FLAG::SF, AL & (1 << 7)); //Sign Flag
	Register::SetFlag(Register::FLAG::ZF, AL == 0x00); //Zero Flag
	//Overflow Flag is undefined

	++CurrInsIndex;
	return NextInstructionExist();
}
