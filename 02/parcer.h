#include <iostream>
#include <functional>

using tokenHandler = void(*)(const char* token);
using tokenNumberHandler = void(*)(int token);

void stringParcer(char* str);

void stringCallback(const char* token);
void numberCallback(int token);
void startCallback(const char* token);
void endCallback(const char* token);