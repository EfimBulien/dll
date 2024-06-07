#include "pch.h"
#include <string>

extern "C" __declspec(dllexport) bool containsAllCharacters(const char* str, const char* chars) {
    const std::string s(str);
    const std::string c(chars);

    for (const char ch : c) {
        if (s.find(ch) == std::string::npos) {
            return false;
        }
    }
    return true;
}
