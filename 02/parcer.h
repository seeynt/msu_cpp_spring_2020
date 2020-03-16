#include <iostream>
#include <functional>

#define LEN 256

using tokenHandler = void(*)(const char* token);

void setTokenHandler(tokenHandler handler);
void stringParcer(const char* str);

void stringCallback(const char* token);
void numberCallback(const char* token);
void startCallback(const char* token);
void endCallback(const char* token);