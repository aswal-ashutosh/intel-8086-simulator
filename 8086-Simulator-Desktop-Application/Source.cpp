#include"parser.h"
#include"program_loader.h"
#include<iostream>
#include"instruction_set.h"

int main()
{
	ProgramLoader::LoadCallBacks();
	ProgramExecutor::LoadCallBacks();
	Parser::Read("test.txt");
	ProgramLoader::Load();

	//
	Memory::Set8Bit(0x00500, 0x04);
	Memory::Set8Bit(0x00501, 0xF9);
	Memory::Set8Bit(0x00502, 0xF2);
	Memory::Set8Bit(0x00503, 0x39);
	Memory::Set8Bit(0x00504, 0x05);
	//


	ProgramExecutor::Execute();
	Register::PrintAll();
	Memory::DebugMem(0x4000, 0xFFFD, 1);
	Memory::DebugMem(0x4000, 0xFFFE, 1);
	return 0;
}