#include "parcer.h"

static tokenHandler stringHandler = stringCallback;
static tokenNumberHandler numberHandler = numberCallback;
static tokenHandler endHandler = endCallback;
static tokenHandler startHandler = startCallback;

void stringParcer(char* str) {
	char *token = str, c;
	int j = 0;
	bool is_number = 1;

	if (str && str[0])
		startHandler(token);
	else
		return;

	for (int i = 0; str[i]; ++i) {
		c = str[i];

		if (c == ' ' || c == '\t' || c == '\n') {
			if (j > 0) {
				str[i] = 0;
				if (is_number)
					numberHandler(atoi(token));
				else
					stringHandler(token);
				str[i] = c;
			}

			j = 0, is_number = 1;
			continue;
		}

		if (j == 0)
			token = str + i;
		if (!isdigit(c))
			is_number = 0;
		++j;
	}

	endHandler(token);
}

void stringCallback(const char* token) {
	std::cout << "S: " << token << '\n';
}

void numberCallback(int token) {
	std::cout << "N: " << token << '\n';
}

void startCallback(const char* token) {
	std::cout << "Begin\n";
}

void endCallback(const char* token) {
	std::cout << "End\n";
}