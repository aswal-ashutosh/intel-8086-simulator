#pragma once
#include<unordered_map>
#include"mod_rm.h"

const std::unordered_map<std::string, MOD_RM_INFO>  MOD_RM =
{
	{"[BX+SI]",		{0b00, 0b000}},
	{"[BX+DI]",		{0b00, 0b001}},
	{"[BP+SI]",		{0b00, 0b010}},
	{"[BP+DI]",		{0b00, 0b011}},
	{"[SI]",			{0b00, 0b100}},
	{"[DI]",			{0b00, 0b101}},
	{"[d16]",			{0b00, 0b110}},
	{"[BX]",			{0b00, 0b111}},

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
	{"[SI+d16]",		{0b10, 0b100}},
	{"[DI+d16]",		{0b10, 0b101}},
	{"[BP+d16]",		{0b10, 0b110}},
	{"[BX+d16]",		{0b10, 0b111}},
						   
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

const std::unordered_map<std::string, Byte> MNEMONIC =
{
	{"MOV", 0b100010}
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