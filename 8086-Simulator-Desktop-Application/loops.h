#pragma once
#include"8086.h"

bool ProgramExecutor::LOOP(const Operand& operand)
{
	Register::REG16(REGISTER::CX, Register::REG16(REGISTER::CX) - 1);
	if (Register::REG16(REGISTER::CX) == 0)
	{
		++CurrInsIndex;
	}
	else
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	return NextInstructionExist();
}

bool ProgramExecutor::LOOPE_LOOPZ(const Operand& operand)
{
	Register::REG16(REGISTER::CX, Register::REG16(REGISTER::CX) - 1);
	if (Register::GetFlag(Register::FLAG::ZF) && Register::REG16(REGISTER::CX) == 0)
	{
		++CurrInsIndex;
	}
	else
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	return NextInstructionExist();
}


bool ProgramExecutor::LOOPNE_LOOPNZ(const Operand& operand)
{
	Register::REG16(REGISTER::CX, Register::REG16(REGISTER::CX) - 1);
	if (!Register::GetFlag(Register::FLAG::ZF) && Register::REG16(REGISTER::CX) == 0)
	{
		++CurrInsIndex;
	}
	else
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	return NextInstructionExist();
}