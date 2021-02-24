#pragma once
#include"8086.h"

bool ProgramExecutor::JMP(const Operand& operand)
{
	CurrInsIndex = Label::IndexOf(operand.first);
	return NextInstructionExist();
}

bool ProgramExecutor::JC(const Operand& operand)
{
	if (Register::GetFlag(Register::FLAG::CF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JNC(const Operand& operand)
{
	if (!Register::GetFlag(Register::FLAG::CF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JZ_JE(const Operand& operand)
{
	if (Register::GetFlag(Register::FLAG::ZF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JNZ_JNE(const Operand& operand)
{
	if (!Register::GetFlag(Register::FLAG::ZF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JPE_JP(const Operand& operand)
{
	if (Register::GetFlag(Register::FLAG::PF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JPO_JNP(const Operand& operand)
{
	if (!Register::GetFlag(Register::FLAG::PF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JS(const Operand& operand)
{
	if (Register::GetFlag(Register::FLAG::SF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JNS(const Operand& operand)
{
	if (!Register::GetFlag(Register::FLAG::SF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JO(const Operand& operand)
{
	if (Register::GetFlag(Register::FLAG::OF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}

bool ProgramExecutor::JNO(const Operand& operand)
{
	if (!Register::GetFlag(Register::FLAG::OF))
	{
		CurrInsIndex = Label::IndexOf(operand.first);
	}
	else
	{
		++CurrInsIndex;
	}
	return NextInstructionExist();
}
