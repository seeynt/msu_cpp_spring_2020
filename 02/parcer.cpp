#include "parcer.h"

void stringParcer(const char* str) {
	char token[LEN];
	int tmp;
	token[0] = 0;

	if (str && str[0])
		tokenRegistered(startHandler);
	else
		return;

	while (sscanf(str, "%s", token) == 1) {
		if (sscanf(token, "%d", &tmp) == 1)
			tokenRegistered(tokenNumberHandler);
		//other types of tokens
		else
			tokenRegistered(tokenStringHandler);
	}

	token[0] = 0;
	tokenRegistered(endHandler);
}

void tokenStringHandler(const char* token) {
	std::cout << "S: " << token << '\n';
}

void tokenNumberHandler(const char* token) {
	std::cout << "N: " << token << '\n';
}

void startHandler(const char* token) {
	std::cout << "Begin " << token << '\n';
}

void endHandler(const char* token) {
	std::cout << "End " << token << '\n';
}