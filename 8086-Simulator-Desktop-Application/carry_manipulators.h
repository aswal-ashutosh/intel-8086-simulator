#pragma once
#include"8086.h"

bool ProgramExecutor::STC(const Operand& operand)
{
	Register::SetFlag(Register::FLAG::CF, true);
	++CurrInsIndex;
	return NextInstructionExist();
}

bool ProgramExecutor::CLC(const Operand& operand)
{
	Register::SetFlag(Register::FLAG::CF, false);
	++CurrInsIndex;
	return NextInstructionExist();
}

bool ProgramExecutor::CMC(const Operand& operand)
{
	Register::SetFlag(Register::FLAG::CF, !Register::GetFlag(Register::FLAG::CF));
	++CurrInsIndex;
	return NextInstructionExist();
}