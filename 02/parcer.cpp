#include "parcer.h"

static tokenHandler currTokenHandler;
static tokenHandler stringHandler = stringCallback;
static tokenHandler numberHandler = numberCallback;
static tokenHandler endHandler = endCallback;
static tokenHandler startHandler = startCallback;

void stringParcer(const char* str) {
	char token[LEN], c;
	token[0] = 0;
	int j = 0;

	if (str && str[0])
		setTokenHandler(startHandler);
	else
		return;

	currTokenHandler(token);
	setTokenHandler(numberHandler);

	for (int i = 0; str[i]; ++i) {
		c = str[i];

		if (c == ' ' || c == '\t' || c == '\n') {
			if (token[0]) {
				token[j] = 0;
				currTokenHandler(token);
			}
			j = 0;
			token[0] = 0;
			setTokenHandler(numberHandler);
			continue;
		}

		if (!isdigit(c))
			setTokenHandler(stringHandler);

		token[j] = c, ++j;
	}

	token[0] = 0;
	setTokenHandler(endHandler);
	currTokenHandler(token);
}

void setTokenHandler(tokenHandler handler) {
	currTokenHandler = handler;
}

void stringCallback(const char* token) {
	std::cout << "S: " << token << '\n';
}

void numberCallback(const char* token) {
	std::cout << "N: " << token << '\n';
}

void startCallback(const char* token) {
	std::cout << "Begin" << token << '\n';
}

void endCallback(const char* token) {
	std::cout << "End" << token << '\n';
}