﻿#include "pch.h"
#include <string>

extern "C" __declspec(dllexport) bool containsAllCharacters(const char* str, const char* chars) {
    std::string s(str);
    std::string c(chars);

    for (char ch : c) {
        if (s.find(ch) == std::string::npos) {
            return false;
        }
    }
    return true;
}
