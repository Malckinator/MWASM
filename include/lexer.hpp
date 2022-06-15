#ifndef LEXER_HPP
#define LEXER_HPP

#include <stdint.h>
#include <string>
#include <vector>

#include "../include/lexer.hpp"

namespace MWASM {
	typedef uint8_t byte;
	typedef uint16_t word;
	typedef uint32_t dword;

	enum class TokenType {
		ERROR,
		EOS,
		INT,
		STRING,
		IDENTIFIER,
		COLON,
		COMMA,
		ASTERISK,
		NEWLINE
	};

	struct Token {
		TokenType type;
		std::string value;
		int start;
		int length;

		Token(TokenType type, std::string value, int start, int length);
	};

	std::vector<Token> MakeTokens(std::string source);
}

#endif