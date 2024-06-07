#include <iostream>
#include <windows.h>
#include <string>

typedef bool (*contains_all_characters_func)(const char*, const char*);

int main() {
    std::string input_str, search_chars;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input_str);
    std::cout << "Enter characters to search for: ";
    std::getline(std::cin, search_chars);

    const HMODULE h_module = LoadLibrary(TEXT("StringChecker.dll"));
    if (h_module == nullptr) {
        std::cerr << "Could not load the dynamic library." << '\n';
        return 1;
    }

    const auto contains_all_characters = reinterpret_cast<contains_all_characters_func>
        (GetProcAddress(h_module, "containsAllCharacters"));
    if (!contains_all_characters) {
        std::cerr << "Could not locate the function." << '\n';
        FreeLibrary(h_module);
        return 1;
    }

    const bool result = contains_all_characters(input_str.c_str(), search_chars.c_str());
    int found_count = 0;
    for (const char ch : search_chars) {
        if (input_str.find(ch) != std::string::npos) {
            found_count++;
        }
    }

    if (result) {
        std::cout << "All characters are found in the string." << '\n';
    }
    else {
        std::cout << "Not all characters are found in the string." << '\n';
    }

    std::cout << "Found " << found_count << " out of " << search_chars.length() << " characters." << '\n';

    FreeLibrary(h_module);

    return 0;
}
