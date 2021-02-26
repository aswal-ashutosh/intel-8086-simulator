#pragma once
#include"parser.h"
#include"program_loader.h"
#include"8086.h"

bool LOAD_PROGRAM(const std::string &FILE_PATH)
{
	//Clear Registers + Labels + Prev Program
	Register::Clear();
	Label::Clear();
	ProgramLoader::ClearProgram();
	ProgramExecutor::ClearProgram();

	if (!Parser::Read(FILE_PATH))
	{
		return false;
	}

	if (!ProgramLoader::Load())
	{
		return false;
	}

	ProgramExecutor::GetProgramFromLoader();//Will Fetch the Program from Loader

	return true;
}