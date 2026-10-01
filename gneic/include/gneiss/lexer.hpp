/* =============================================================
 *          ____   _   _   _____   ___   ____    ____
 *         / ___| | \ | | | ____| |_ _| / ___|  / ___|
 *        | |  _  |  \| | |  _|    | |  \___ \  \___ \
 *        | |_| | | |\  | | |___   | |   ___) |  ___) |
 *         \____| |_| \_| |_____| |___| |____/  |____/
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * Gneiss is licenced under the MIT license
 */

#pragma once
#include "gneiss/token.hpp"
#include <vector>

namespace gneiss {
class DiagnosticEngine;
}

namespace gneiss::parse {

/**
 * @brief converts Gneiss source code into tokens
 *
 * The lexer recognizes literals, identifiers, keywords, operators,
 * comments, and other syntactic elements used by the parser.
 */
class Lexer {
public:
    /**
     * @brief creates a lexer using the given diagnostic engine
     *
     * @param diagnostic diagnostic engine used to report lexical errors
     */
    explicit Lexer(DiagnosticEngine* diagnostic) : diagnostic(diagnostic) {}

    /**
     * @brief tokenizes a Gneiss source file
     *
     * @param source the source code to tokenize
     * @return the tokens produced from the source code
     */
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
    [[nodiscard]] bool end() const;
    [[nodiscard]] char peek() const;
    [[nodiscard]] char peek(int i) const;
    [[nodiscard]] bool check(char expected) const;

    char next();
    bool match(char expected);

    char generate_escape(char c, size_t line_number);

    std::string source;
    size_t position{0}; // brace initialize because cool
    size_t line_number{1};

    DiagnosticEngine* diagnostic;
};

} // namespace gneiss::parse