#pragma once
#include<unordered_map>
#include"mod_rm.h"

namespace MNEMONIC
{
	const std::string MOV = "MOV";
	const std::string ADD = "ADD";
	const std::string ADC = "ADC";
	const std::string AND = "AND";
	const std::string CMP = "CMP";
	const std::string OR = "OR";
	const std::string SUB = "SUB";
	const std::string SBB = "SBB";
	const std::string XOR = "XOR";
	const std::string MUL = "MUL";
	const std::string IMUL = "IMUL";
	const std::string DIV = "DIV";
	const std::string IDIV = "IDIV";
	const std::string NEG = "NEG";
	const std::string NOT = "NOT";
	const std::string DEC = "DEC";
	const std::string INC = "INC";
	const std::string DAA = "DAA";
	const std::string SHL = "SHL";
	const std::string SAL = "SAL";
	const std::string SHR = "SHR";
	const std::string SAR = "SAR";
	const std::string RCL = "RCL";
	const std::string RCR = "RCR";
	const std::string ROL = "ROL";
	const std::string ROR = "ROR";
	const std::string STC = "STC";
	const std::string CLC = "CLC";
	const std::string CMC = "CMC";
	const std::string XCHG = "XCHG";
}

const std::unordered_map<std::string, MOD_RM_INFO>  MOD_RM =
{
	{"[BX+SI]",		{0b00, 0b000}},
	{"[BX+DI]",		{0b00, 0b001}},
	{"[BP+SI]",		{0b00, 0b010}},
	{"[BP+DI]",		{0b00, 0b011}},
	{"[SI]",		{0b00, 0b100}},
	{"[DI]",		{0b00, 0b101}},
	{"[d16]",		{0b00, 0b110}},
	{"[BX]",		{0b00, 0b111}},

	{"[BX+SI+d8]",	{0b01, 0b000}},
	{"[BX+DI+d8]",	{0b01, 0b001}},
	{"[BP+SI+d8]",	{0b01, 0b010}},
	{"[BP+DI+d8]",	{0b01, 0b011}},
	{"[SI+d8]",		{0b01, 0b100}},
	{"[DI+d8]",		{0b01, 0b101}},
	{"[BP+d8]",		{0b01, 0b110}},
	{"[BX+d8]",		{0b01, 0b111}},
						   
	{"[BX+SI+d16]",	{0b10, 0b000}},
	{"[BX+DI+d16]",	{0b10, 0b001}},
	{"[BP+SI+d16]",	{0b10, 0b010}},
	{"[BP+DI+d16]",	{0b10, 0b011}},
	{"[SI+d16]",	{0b10, 0b100}},
	{"[DI+d16]",	{0b10, 0b101}},
	{"[BP+d16]",	{0b10, 0b110}},
	{"[BX+d16]",	{0b10, 0b111}},
						   
	{"AL",			{0b11, 0b000}},
	{"CL",			{0b11, 0b001}},
	{"DL",			{0b11, 0b010}},
	{"BL",			{0b11, 0b011}},
	{"AH",			{0b11, 0b100}},
	{"CH",			{0b11, 0b101}},
	{"DH",			{0b11, 0b110}},
	{"BH",			{0b11, 0b111}},
						   
	{"AX",			{0b11, 0b000}},
	{"CX",			{0b11, 0b001}},
	{"DX",			{0b11, 0b010}},
	{"BX",			{0b11, 0b011}},
	{"SP",			{0b11, 0b100}},
	{"BP",			{0b11, 0b101}},
	{"SI",			{0b11, 0b110}},
	{"DI",			{0b11, 0b111}},
};						   

const std::unordered_map<std::string, Byte> REG_CODE =
{
	{"AL",	0b000},
	{"CL",	0b001},
	{"DL",	0b010},
	{"BL",	0b011},
	{"AH",	0b100},
	{"CH",	0b101},
	{"DH",	0b110},
	{"BH",	0b111},

	{"AX",	0b000},
	{"CX",	0b001},
	{"DX",	0b010},
	{"BX",	0b011},
	{"SP",	0b100},
	{"BP",	0b101},
	{"SI",	0b110},
	{"DI",	0b111},

	{"ES", 0b00},
	{"SS", 0b10},
	{"CS", 0b01},
	{"DS", 0b11},
};

namespace REGISTER
{
	//Segment Registers
	const std::string CS = "CS";
	const std::string DS = "DS";
	const std::string SS = "SS";
	const std::string ES = "ES";
	
	//General Purpose Registers
	const std::string AX = "AX";
	const std::string BX = "BX";
	const std::string CX = "CX";
	const std::string DX = "DX";
	const std::string AL = "AL";
	const std::string BL = "BL";
	const std::string CL = "CL";
	const std::string DL = "DL";
	const std::string AH = "AH";
	const std::string BH = "BH";
	const std::string CH = "CH";
	const std::string DH = "DH";

	//Sepecial Purpose Registers
	const std::string SP = "SP";
	const std::string BP = "BP";
	const std::string SI = "SI";
	const std::string DI = "DI";
};