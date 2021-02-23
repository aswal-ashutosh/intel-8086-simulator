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
	/*ProgramExecutor::Execute(ProgramLoader::GetProgram());
	Register::PrintAll();*/
	//Memory::DebugMem(0x0000, 0x1234, 2);
	return 0;
}