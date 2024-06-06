#include <iostream>
#include <windows.h>
#include <string>

typedef bool (*ContainsAllCharactersFunc)(const char*, const char*);

int main() {
    std::string inputStr, searchChars;
    std::cout << "Enter a string: ";
    std::getline(std::cin, inputStr);
    std::cout << "Enter characters to search for: ";
    std::getline(std::cin, searchChars);

    HMODULE hModule = LoadLibrary(TEXT("StringChecker.dll"));
    if (hModule == NULL) {
        std::cerr << "Could not load the dynamic library." << std::endl;
        return 1;
    }

    ContainsAllCharactersFunc containsAllCharacters =
        (ContainsAllCharactersFunc)GetProcAddress(hModule, "containsAllCharacters");
    if (!containsAllCharacters) {
        std::cerr << "Could not locate the function." << std::endl;
        FreeLibrary(hModule);
        return 1;
    }

    bool result = containsAllCharacters(inputStr.c_str(), searchChars.c_str());
    int foundCount = 0;
    for (char ch : searchChars) {
        if (inputStr.find(ch) != std::string::npos) {
            foundCount++;
        }
    }

    if (result) {
        std::cout << "All characters are found in the string." << std::endl;
    }
    else {
        std::cout << "Not all characters are found in the string." << std::endl;
    }

    std::cout << "Found " << foundCount << " out of " << searchChars.length() << " characters." << std::endl;

    FreeLibrary(hModule);

    return 0;
}
