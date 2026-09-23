/* =============================================================
 *          ____   _   _   _____   ___   ____    ____
 *         / ___| | \ | | | ____| |_ _| / ___|  / ___|
 *        | |  _  |  \| | |  _|    | |  \___ \  \___ \
 *        | |_| | | |\  | | |___   | |   ___) |  ___) |
 *         \____| |_| \_| |_____| |___| |____/  |____/
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once
#include <gneiss/Frontend/Lexer/Token.hpp>
#include <vector>

namespace gneiss::frontend {

class Lexer {
public:
    // main tokenize function
    std::vector<Token> tokenize(std::string source);

private:
    // call when encountering a hashtag
    void skip_comment();

    // call when encountering the sequence "/*", ends when encoountering "*/"
    void skip_multiline_comment();

    // call when encountering a digit
    void tokenize_number(std::vector<Token>& tokens);

    // call when encountering a double quote
    void tokenize_string(std::vector<Token>& tokens);

    // call when encountering a single quote
    void tokenize_char(std::vector<Token>& tokens);

    // call when encountering a letter or underscore
    void tokenize_word(std::vector<Token>& tokens);

    // call when none of the above
    void tokenize_symbol(std::vector<Token>& tokens);

    // lexer helper functions
    [[nodiscard]] bool end() const { return position >= source.size(); }
    [[nodiscard]] char peek() const { return end() ? '\0' : source[position]; }
    [[nodiscard]] char peek(int i) const { return position >= source.size() - i ? '\0' : source[position + i]; }
    char next() {
        if (end())
            return '\0';

        char c = source[position++];

        if (c == '\n')
            ++line_number;

        return c;
    }
    [[nodiscard]] bool check(char expected) const { return peek() == expected; }
    bool match(char expected) {
        if (!check(expected))
            return false;
        next();
        return true;
    }

    // helper
    static char generate_escape(char c, size_t line_number);

    std::string source;
    size_t position{0}; // brace initialize because cool
    size_t line_number{1};
};

} // namespace gneiss::frontend