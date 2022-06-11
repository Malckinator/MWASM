#ifndef LEXER_H
#define LEXER_H

typedef enum TokenTypeEnum {
	TTERROR,
	TTEOS,
	TTIDENTIFIER,
	TTINT,
	TTFLOAT,
	TTSTRING,
	TTCOLON,
	TTNEWLINE
} TokenType;

typedef struct TokenStruct {
	TokenType type;
	char* value;
	int position;
	int length;
} Token;

Token* CreateToken(TokenType type, char* value, int position, int length);
Token* MakeNumber(char* source, int* size);
Token* MakeIdentifier(char* source, int* size);
Token* MakeString(char* source, int* size);
Token* MakeTokens(char* source);

#endif