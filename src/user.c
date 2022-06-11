#include <stdio.h>

#include "../include/lexer.h"

int main() {
	Token* tokens = MakeTokens("JMP 0");
	int i = 0;
	Token token = tokens[i];
	do {
		printf("%u: %s", token.type, token.value);
		i++;
		token = tokens[i];
	} while (token.type != TTEOS);

	return 0;
}