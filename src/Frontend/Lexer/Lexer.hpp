/* =============================================================
 *
 *                       G N E I S S
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * Gneiss is licensed under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once
#include "Token.hpp"
#include <vector>

namespace gneiss::frontend {

class Lexer {
public:
    // Main tokenize function
    std::vector<Token> tokenize(std::string source);

private:
    // Call when encountering a hashtag
    void skip_comment();

    // Call when encountering a digit
    void tokenize_number(std::vector<Token>& tokens);

    // Call when encountering a double quote
    void tokenize_string(std::vector<Token>& tokens);

    // Call when encountering a single quote
    void tokenize_char(std::vector<Token>& tokens);

    // Call when encountering a letter or underscore
    void tokenize_word(std::vector<Token>& tokens);

    // Call when none of the above
    void tokenize_symbol(std::vector<Token>& tokens);

    // Lexer helper functions
    bool end() const { return position >= source.size(); }
    char peek() const { return end() ? '\0': source[position]; }
    char next() {
        if (end())
            return '\0';

        char c = source[position++];

        if (c == '\n')
            ++line_number;

        return c;
    }
    bool check(char expected) const { return peek() == expected; }
    bool match(char expected) {
        if (!check(expected)) return false;
        next();
        return true;
    }

    // other helper(s)
    static char generate_escape(char c, size_t line_number) ;

    std::string source;
    size_t position{0}; // brace initialize because cool
    size_t line_number{1};
};

} // namespace gneiss::frontend