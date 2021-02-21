#pragma once
#include"8086.h"

bool ProgramExecutor::STC(const Operand& operand)
{
	Register::SetFlag(Register::FLAG::CF, true);
	return true;
}

bool ProgramExecutor::CLC(const Operand& operand)
{
	Register::SetFlag(Register::FLAG::CF, false);
	return true;
}

bool ProgramExecutor::CMC(const Operand& operand)
{
	Register::SetFlag(Register::FLAG::CF, !Register::GetFlag(Register::FLAG::CF));
	return true;
}