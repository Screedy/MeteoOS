//
// Created by Petr Jurásek on 10.07.2024.
//

#ifndef PICO_BOILERPLATE_STRING_MODIFIERS_H
#define PICO_BOILERPLATE_STRING_MODIFIERS_H

#include <string>
#include <vector>

/*
 * Splits a string by a delimiter.
 *
 * @param s The string to split.
 * @param delimiter The delimiter to split the string by.
 *
 * @return A vector of strings that were split by the delimiter.
 */
std::vector<std::string> split(const std::string &s, char delimiter);

/*
 * Removes escape sequences from a string.
 *
 * @param s The string to remove escape sequences from.
 *
 * @return The string with escape sequences removed.
 */
std::string removeEscapeSequences(const std::string &s);

#endif //PICO_BOILERPLATE_STRING_MODIFIERS_H
