//
// Created by Petr Jurásek on 10.07.2024.
//

#include "string_modifiers.h"

#include <sstream>

// Function to split a string by a delimiter
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to remove escape sequences from a string
std::string removeEscapeSequences(const std::string &s) {
    std::string result;
    for (char c : s) {
        if (c != '\n' && c != '\r') {
            result += c;
        }
    }
    return result;
}