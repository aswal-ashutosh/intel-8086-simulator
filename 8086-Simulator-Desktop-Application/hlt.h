#pragma once
#include"8086.h"

bool ProgramExecutor::HLT(const Operand& operand)
{
	ProgramExecutor::HLT_STATE_REACHED = true;
	return true;
}