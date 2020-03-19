#include "parcer.h"

static tokenHandler stringHandler = stringCallback;
static tokenNumberHandler numberHandler = numberCallback;
static tokenHandler endHandler = endCallback;
static tokenHandler startHandler = startCallback;

void stringParcer(const char* str) {
	char c;
	int j = 0, st = 0, n;
	bool is_number = 1;

	if (str && str[0])
		startHandler(std::string_view(str, 0));
	else
		return;

	for (int i = 0; str[i]; ++i) {
		c = str[i];

		if (c == ' ' || c == '\t' || c == '\n') {
			if (j > 0) {
				if (is_number) {
					std::from_chars(str + st, str + i, n);
					numberHandler(n);
				}
				else
					stringHandler(std::string_view(str + st, j));
			}

			j = 0, is_number = 1;
			continue;
		}

		if (j == 0)
			st = i;
		if (!isdigit(c))
			is_number = 0;
		++j;
	}

	endHandler(std::string_view(str, 0));
}

void stringCallback(std::string_view token) {
	std::cout << "S: " << token << '\n';
}

void numberCallback(int token) {
	std::cout << "N: " << token << '\n';
}

void startCallback(std::string_view token) {
	std::cout << "Begin\n";
}

void endCallback(std::string_view token) {
	std::cout << "End\n";
}