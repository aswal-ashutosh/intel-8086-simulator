#pragma once
#include"8086.h"

bool ProgramExecutor::CALL(const Operand& operand)
{
	CallStack.push_back(CurrInsIndex);

	Word ReturnAddress = Program[CurrInsIndex].Offset;
	int CurrentStackTop = Register::REG16(REGISTER::SS) * 0x10 + Register::REG16(REGISTER::SP);
	Memory::Set16Bit(CurrentStackTop - 2, ReturnAddress);
	Register::REG16(REGISTER::SP, Register::REG16(REGISTER::SP) - 2);

	CurrInsIndex = Label::IndexOf(operand.first);
	return NextInstructionExist();
}

bool ProgramExecutor::RET(const Operand& operand)
{
	if (CallStack.empty())
	{
		return Error::LOG("Return Without Call", Program[CurrInsIndex].LineNumber);
	}
	Register::REG16(REGISTER::SP, Register::REG16(REGISTER::SP) + 2);
	CurrInsIndex = CallStack.back();//Returning to the instruction from where a subroutine is called
	CallStack.pop_back();
	++CurrInsIndex;//Moving to next instruction
	return NextInstructionExist();
}