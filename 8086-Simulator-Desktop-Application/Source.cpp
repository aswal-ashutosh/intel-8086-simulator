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
	/*ProgramExecutor::Execute(Parser::GetProgram());*/

	/*std::cout << "\n.....................................\n\n";
	Memory::DebugMem(0x1000, 0x3333, 2);
	Register::PrintAll();*/
	return 0;
}