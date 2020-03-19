#include <iostream>
#include <functional>
#include <string_view>
#include <charconv>

using tokenHandler = void(*)(std::string_view token);
using tokenNumberHandler = void(*)(int token);

void stringParcer(const char* str);

void stringCallback(std::string_view token);
void numberCallback(int token);
void startCallback(std::string_view token);
void endCallback(std::string_view token);