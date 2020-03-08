#include <iostream>
#include "mem.h"
using namespace std;

int main() {
	string input;
	int tmp;

	while (cin >> input) {
		if (input == "makeAllocator") {
			cin >> tmp;
			makeAllocator(tmp);
			printf("Start.\n");
		}
		else if (input == "alloc") {
			cin >> tmp;
			printf("%p\n", alloc(tmp));
		}
		else if (input == "reset") {
			reset();
			printf("Reseted.\n");
		}
		else if (input == "exit")
			printf("End.\n");
		else
			break;
	}

	free_ptr();
	return 0;
}