#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/lexer.h"

Token* CreateToken(TokenType type, char* value, int position, int length) {
	Token* result = malloc(sizeof(Token));
	result->type = type;
	result->value = value;
	result->position = position;
	result->length = length;
	return result;
}

void AddTokenToList(Token** list, int* size, Token* item) {
	*list = (Token*) realloc(*list, sizeof(*size + 1));
	(*list)[*size] = *item;
	(*size)++;
}

Token* MakeNumber(char* source, int* size) {
	int start = *size;
	char* strnum = malloc(1);
	int strSize = 1;
	char c = strnum[*size];
	bool f = false;

	do {
		strnum = (char*) realloc(strnum, sizeof(char) * (strSize + 1));
		strnum[strSize - 1] = c;
		strnum[strSize] = '\0';
		strSize++;
		if (c == '.')
			f = true;
		(*size)++;
		c = source[*size];
	} while (isdigit(c) || tolower(c) == 'a' || tolower(c) == 'b' || tolower(c) == 'c' || tolower(c) == 'd' || tolower(c) == 'e' || tolower(c) == 'f' || tolower(c) == 'x' || c == '.');

	if (f)
		return CreateToken(TTFLOAT, strnum, start, strSize - 1);
	return CreateToken(TTINT, strnum, start, strSize - 1);
}

Token* MakeIdentifier(char* source, int* size) {
	int start = *size;
	char* str = malloc(1);
	int strSize = 1;
	char c = str[*size];

	do {
		str = (char*)realloc(str, sizeof(char) * (strSize + 1));
		str[strSize - 1] = c;
		str[strSize] = '\0';
		strSize++;
		(*size)++;
		c = source[*size];
	} while (isalnum(c) || c == '.' || c == ',');

	return CreateToken(TTIDENTIFIER, str, start, strSize - 1);
}

Token* MakeString(char* source, int* size) {
	int start = *size;
	char* str = malloc(1);
	int strSize = 1;
	char c = source[*size];
	bool b = false;
	(*size)++;

	while (true) {
		if (c == '\\') {
			b = !b;
			if (b)
				break;
		}
		if (c == '"' && !b)
			break;
		str = (char*)realloc(str, sizeof(char) * (strSize + 1));
		str[strSize - 1] = c;
		str[strSize] = '\0';
		strSize++;
		(*size)++;
		c = source[*size];
	};

	return CreateToken(TTSTRING, str, start, strSize - 1);
}

Token* MakeTokens(char* source) {
	Token* list = malloc(0);
	int size = 0;
	bool isComment = false;

	for (int i = 0; i <= strlen(source); i++) {
		if (isdigit(source[i]))
			AddTokenToList(&list, &size, MakeNumber(source, &i));
		else if (isalpha(source[i]))
			AddTokenToList(&list, &size, MakeIdentifier(source, &i));
		else if (source[i] == '"')
			AddTokenToList(&list, &size, MakeString(source, &i));
		else if (source[i] == '$') {
			char buffer[5] = "";
			_itoa_s(source[i + 1], buffer, 5, 10);
			AddTokenToList(&list, &size, CreateToken(TTINT, buffer, i, 2));
			i++;
		} else if (source[i] == ':')
			AddTokenToList(&list, &size, CreateToken(TTCOLON, "", i, 1));
		else if (source[i] == '\n') {
			AddTokenToList(&list, &size, CreateToken(TTNEWLINE, "", i, 1));
			isComment = false;
		} else if (source[i] == '#')
			isComment = true;
	}

	AddTokenToList(&list, &size, CreateToken(TTEOS, "", strlen(source), 1));
	return list;
}