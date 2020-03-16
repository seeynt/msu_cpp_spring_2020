#include "parcer.h"

static tokenHandler currTokenHandler;

void stringParcer(const char* str) {
	char token[LEN], c;
	token[0] = 0;
	int j = 0;

	if (str && str[0])
		setTokenHandler(startHandler);
	else
		return;

	currTokenHandler(token);
	setTokenHandler(tokenNumberHandler);

	for (int i = 0; str[i]; ++i) {
		c = str[i];

		if (c == ' ' || c == '\t' || c == '\n') {
			if (token[0]) {
				token[j] = 0;
				currTokenHandler(token);
			}
			j = 0;
			token[0] = 0;
			setTokenHandler(tokenNumberHandler);
			continue;
		}

		if (!isdigit(c))
			setTokenHandler(tokenStringHandler);

		token[j] = c, ++j;
	}

	token[0] = 0;
	setTokenHandler(endHandler);
	currTokenHandler(token);
}

void setTokenHandler(tokenHandler handler) {
	currTokenHandler = handler;
}

void tokenStringHandler(const char* token) {
	std::cout << "S: " << token << '\n';
}

void tokenNumberHandler(const char* token) {
	std::cout << "N: " << token << '\n';
}

void startHandler(const char* token) {
	std::cout << "Begin" << token << '\n';
}

void endHandler(const char* token) {
	std::cout << "End" << token << '\n';
}