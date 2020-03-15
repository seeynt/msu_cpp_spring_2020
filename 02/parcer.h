#include <iostream>
#include <functional>

#define LEN 256

using tokenHandler = void(*)(const char* token);

void setTokenHandler(tokenHandler handler);
void stringParcer(const char* str);

void tokenStringHandler(const char* token);
void tokenNumberHandler(const char* token);
//more tokens handlers
void startHandler(const char* token);
void endHandler(const char* token);