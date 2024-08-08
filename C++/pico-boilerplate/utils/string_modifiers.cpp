//
// Created by Petr Jurásek on 10.07.2024.
//

#include "string_modifiers.h"
#include <vector>
#include <string>
#include <sstream>
#include "ff.h"

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

std::vector<std::string> splitPath(const std::string& path){
    std::vector<std::string> parts = split(path, '/');
    return parts;
}

FRESULT createDirectory(const std::string& path){
    FRESULT fr = f_mkdir(path.c_str());
    if (fr != FR_OK && fr != FR_EXIST) {
        printf("Failed to create directory %s\n", path.c_str());
    }
    return fr;
}

bool ensureDirectoriesExist(const std::string& fullPath, bool isOnSD){
    std::vector<std::string> parts = splitPath(fullPath);

    if (isOnSD){
        parts.erase(parts.begin());
    }

    std::string currentPath = parts[0];

    for (size_t i = 1; i < parts.size(); ++i){
        currentPath += "/" + parts[i];
        FRESULT fr = createDirectory(currentPath);
        if (fr != FR_OK && fr != FR_EXIST){
            return false;
        }
    }

    return true;
}

int compare_date(datetime_t date1, datetime_t date2){
    if (date1.year != date2.year){
        return date1.year - date2.year;
    }
    if (date1.month != date2.month){
        return date1.month - date2.month;
    }
    if (date1.day != date2.day){
        return date1.day - date2.day;
    }
    return 0;
}