#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

namespace MWASM {
	enum class ParameterType {
		STRING,
		INT,
		REG,
		MEMADDR,
		FLAG
	};

	struct Parameter {
		ParameterType type;
		std::string value;

		Parameter(ParameterType type, std::string value);
	};

	enum class InstructionType {
		HLT, DAT, INTR, RET, IRET,
		JMP, JPZ, JNZ, JL, JE, JG,
		CALL, CALLZ, CALLNZ, CALLL, CALLE, CALLG,
		MOV, IN, OUT, STP, LDP,
		STPP, STPS, STPL,
		INC, DEC, ADD, SUB, ADDC, SUBB, MUL, DIV, POW,
		SHL, SHR, ROTL, ROTR, AND, NAND, OR, NOR, XOR, COMP
	};

	struct Instruction {
		InstructionType type;
		std::vector<Parameter> params;

		Instruction(InstructionType type, std::vector<Parameter> params);
	};
}

#endif