#include"parser.h"
#include"8086.h"
#include"program_loader.h"
#include<iostream>

int main()
{
	ProgramLoader::LoadCallBacks();
	ProgramExecutor::LoadCallBacks();
	Parser::Read("test.txt");
	ProgramLoader::Load(Parser::GetProgram());
	ProgramExecutor::Execute(Parser::GetProgram());

	std::cout << "\n.....................................\n\n";
	Register::PrintAll();
	//Memory::DebugMem(0x0000, 0x1234, 2);
	return 0;
}