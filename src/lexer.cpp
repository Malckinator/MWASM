#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

#include "../include/lexer.hpp"

MWASM::Token::Token(TokenType type, std::string value, int start, int length) {
	this->type = type;
	this->value = value;
	this->start = start;
	this->length = length;
}

MWASM::Token MakeNumber(std::string source, int* position) {
	int start = *position;
	std::string strnum = std::string();
	char c = source[*position];

	while (isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
		strnum.append(1, c);
		(*position)++;
		c = source[*position];
	}

	return MWASM::Token(MWASM::TokenType::INT, strnum, start, *position - 1 - start);
}

MWASM::Token MakeString(std::string source, int* position) {
	int start = *position;
	std::string str = std::string();
	bool b = false;
	(*position)++;
	char c = source[*position];

	while (true) {
		if (c == '\\') {
			b = !b;
			if (b)
				continue;
		}
		if (!b && c == '"') {
			return MWASM::Token(MWASM::TokenType::STRING, str, start, *position - start);
		}
		str.append(1, c);
		(*position)++;
		char c = source[*position];
	}
}

MWASM::Token MakeChar(std::string source, int* position) {
	int start = *position;
	std::string str = std::string();
	bool b = false;
	(*position)++;
	char c = source[*position];

	while (true) {
		if (c == '\\') {
			b = !b;
			if (b)
				continue;
		}
		if (!b && c == '\'') {
			if (str.length() == 1)
				return MWASM::Token(MWASM::TokenType::STRING, str, start, *position - start);
			else
				return MWASM::Token(MWASM::TokenType::ERROR, "Characters cannot have multiple chatacters in them.", start, *position);
		}
		str.append(1, c);
		(*position)++;
		char c = source[*position];
	}
}

MWASM::Token MakeIdentifier(std::string source, int* position) {
	int start = *position;
	std::string str = std::string();
	(*position)++;
	char c = source[*position];

	while (isalnum(c)) {
		str.append(1, c);
		(*position)++;
		c = source[*position];
	}

	return MWASM::Token(MWASM::TokenType::IDENTIFIER, str, start, *position - 1);
}

std::vector<MWASM::Token> MWASM::MakeTokens(std::string source) {
	std::vector<Token> tokens = std::vector<Token>();
	int i = 0;

	while (true) {
		if (isdigit(source[i])) {
			tokens.push_back(MakeNumber(source, &i));
			continue;
		}
		else if (source[i] == '"') {
			Token token = MakeString(source, &i);
			if (token.type == TokenType::ERROR) {
				tokens.clear();
				tokens.push_back(token);
				return tokens;
			}
			tokens.push_back(token);
		}
		else if (source[i] == '\'')
			tokens.push_back(MakeChar(source, &i));
		else if (isalpha(source[i])) {
			tokens.push_back(MakeIdentifier(source, &i));
			continue;
		}
		else if (source[i] == ':')
			tokens.push_back(Token(TokenType::COLON, "", i, 1));
		else if (source[i] == ',')
			tokens.push_back(Token(TokenType::COMMA, "", i, 1));
		else if (source[i] == '*')
			tokens.push_back(Token(TokenType::ASTERISK, "", i, 1));
		else if (source[i] == '\n')
			tokens.push_back(Token(TokenType::NEWLINE, "", i, 1));
		else if (!isspace(source[i])) {
			tokens.clear();
			tokens.push_back(Token(TokenType::ERROR, "Unknown character", i, 1));
			return tokens;
		}

		i++;
	}

	return tokens;
}