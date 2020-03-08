#include "mem.h"

static size_t curr = 0;
static size_t maxSize = 0;
static char* ptr = nullptr;

void makeAllocator(size_t m) {
	maxSize = m;
	if (maxSize > 0)
		ptr = (char*)malloc(maxSize);
	return;
}

char* alloc(size_t size) {
	if (size > maxSize - curr || !ptr)
		return nullptr;
	else {
		curr += size;
		return ptr + curr - size;
	}
}

void free_ptr() {
	if (ptr)
		free(ptr);
	ptr = nullptr, curr = 0;
}

void reset() {
	curr = 0;
}