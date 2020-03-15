#include <iostream>
#include "parcer.h"
#define INPUT_LEN 256
using namespace std;

int main() {
	char input[INPUT_LEN];
	int n = 0;

	if (scanf("%d", &n) != 1) {
		printf("Wrong input\n");
		return 1;
	}

	for (int i = 0; i < n; ++i) {
		fgets(input, INPUT_LEN, stdin);
		stringParcer(input);
	}

	return 0;
}