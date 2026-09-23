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

#include <gneiss/Core/Core.hpp>
#include <gneiss/Core/Diagnostic.hpp>
#include <gneiss/Core/File.hpp>
#include <gneiss/Frontend/Lexer/Lexer.hpp>

namespace gneiss::frontend {

std::vector<Token> Lexer::tokenize(std::string source) {

    // Take ownership of the source so all lexer helpers can operate on the
    // same input without receiving it as an argument.
    this->source = std::move(source);
    std::vector<Token> tokens;

    while (!end()) {
        char current = peek();

        // We start with comments, since they have highest priority
        if (match('#'))
            skip_comment();

        // Multiline comments
        if (check('/') && peek(1) == '*') {
            next();
            next();
            skip_multiline_comment();
            continue;
        }

        // Whitespace has no semantic meaning in Gneiss, so it is discarded.
        if (std::isspace(static_cast<unsigned char>(current)))
            next();

        // Numeric literals must begin with a digit; a leading '.' is always
        // lexed as the dot token.
        else if (std::isdigit(static_cast<unsigned char>(current)))
            tokenize_number(tokens);

        // Identifiers may contain digits after their first character, but
        // cannot begin with one.
        else if (std::isalpha(static_cast<unsigned char>(current)) || current == '_')
            tokenize_word(tokens);

        else if (match('"'))
            tokenize_string(tokens);

        else if (match('\''))
            tokenize_char(tokens);

        else
            tokenize_symbol(tokens);
    }

    tokens.push_back({TokenKind::EndOfFile, "", line_number});
    return tokens;
}

// Only single line comments are supported
void Lexer::skip_comment() {
    while (!end() && !check('\n')) {
        next();
    }
}

void Lexer::skip_multiline_comment() {
    while (!end()) {
        if (check('*') && peek(1) == '/') {
            next();
            next();
            return;
        }

        next();
    }

    diagnostics::report_error("Unterminated multiline comment", line_number);
}

void Lexer::tokenize_number(std::vector<Token>& tokens) {
    std::string value;
    auto kind = TokenKind::LiteralInt;

    while (!end() && (std::isdigit(static_cast<unsigned char>(peek())) || check('.'))) {
        char current = next();

        // We can track whether it is a floating point as long as it contains a
        // dot. Multiple dot's result in an error.
        if (current == '.') {
            if (kind == TokenKind::LiteralFloat)
                diagnostics::report_error("Too many dots in float literal", line_number);
            else
                kind = TokenKind::LiteralFloat;
        }

        value += current;
    }

    tokens.push_back({kind, value, line_number});
}

void Lexer::tokenize_word(std::vector<Token>& tokens) {
    std::string value;

    while (!end() && (std::isalnum(static_cast<unsigned char>(peek())) || check('_'))) {
        value += next();
    }

    // They should definitely add switch statements for strings. It could just
    // compile to if else. Since C++ didn't claim the idea, I will :D
    auto kind = TokenKind::Identifier;
    if (value == "var")
        kind = TokenKind::KwVar;
    if (value == "function")
        kind = TokenKind::KwFunction;
    if (value == "void")
        kind = TokenKind::KwVoid;
    if (value == "print")
        kind = TokenKind::KwPrint;
    if (value == "println")
        kind = TokenKind::KwPrintln;
    if (value == "exit")
        kind = TokenKind::KwExit;
    if (value == "return")
        kind = TokenKind::KwReturn;
    if (value == "true")
        kind = TokenKind::KwTrue;
    if (value == "false")
        kind = TokenKind::KwFalse;
    if (value == "if")
        kind = TokenKind::KwIf;
    if (value == "else")
        kind = TokenKind::KwElse;

    tokens.push_back({kind, value, line_number});
}

void Lexer::tokenize_symbol(std::vector<Token>& tokens) {
    char c = next();

    // Delimiters are always single-character tokens, so they can be dispatched
    // immediately without looking ahead
    switch (c) {
    case '(':
        tokens.push_back({TokenKind::LeftParen, "(", line_number});
        return;
    case ')':
        tokens.push_back({TokenKind::RightParen, ")", line_number});
        return;
    case '[':
        tokens.push_back({TokenKind::LeftBracket, "[", line_number});
        return;
    case ']':
        tokens.push_back({TokenKind::RightBracket, "]", line_number});
        return;
    case '{':
        tokens.push_back({TokenKind::LeftBrace, "{", line_number});
        return;
    case '}':
        tokens.push_back({TokenKind::RightBrace, "}", line_number});
        return;
    case ':':
        tokens.push_back({TokenKind::Colon, ":", line_number});
        return;
    case ';':
        tokens.push_back({TokenKind::Semicolon, ";", line_number});
        return;
    case ',':
        tokens.push_back({TokenKind::Comma, ",", line_number});
        return;
    case '.':
        tokens.push_back({TokenKind::Dot, ".", line_number});
        return;
    default:
        break;
    }

    // Anything that is not a delimiter is checked against the operator set.
    // Operators may require lookahead (for example, '-' followed by '>' forms
    // the arrow token).
    switch (c) {
    case '+':
        tokens.push_back({TokenKind::Plus, "+", line_number});
        return;
    case '-':
        if (match('>')) {
            tokens.push_back({TokenKind::Arrow, "->", line_number});
            return;
        }

        tokens.push_back({TokenKind::Minus, "-", line_number});
        return;
    case '*':
        tokens.push_back({TokenKind::Star, "*", line_number});
        return;
    case '/':
        tokens.push_back({TokenKind::Slash, "/", line_number});
        return;
    case '%':
        tokens.push_back({TokenKind::Percent, "%", line_number});
        return;
    case '=':
        // double equal sign
        if (match('=')) {
            tokens.push_back({TokenKind::EqualEqual, "==", line_number});
            return;
        }
        tokens.push_back({TokenKind::Equal, "=", line_number});
        return;
    case '>':
        if (match('=')) {
            tokens.push_back({TokenKind::GreaterEqualTo, ">=", line_number});
            return;
        }

        tokens.push_back({TokenKind::GreaterThan, ">", line_number});
        return;
    case '<':
        if (match('=')) {
            tokens.push_back({TokenKind::LessEqualTo, "<=", line_number});
            return;
        }

        tokens.push_back({TokenKind::LessThan, "<", line_number});
        return;

    case '!':
        // We have the != operator, but as of right now, we have no logical
        // operators
        if (match('=')) {
            tokens.push_back({TokenKind::BangEqual, "!=", line_number});
            return;
        }

        // This should fall through into default
    default:
        diagnostics::report_error("Unknown symbol '" + std::string(1, c) + "'", line_number);
    }
}

void Lexer::tokenize_string(std::vector<Token>& tokens) {
    std::string value;
    bool escape = false;

    // " only terminates if escape is false, since \" is a valid sequence
    while (!end() && !check('\n') && (escape || !check('"'))) {
        if (!escape && match('\\')) {
            escape = true;
            continue;
        }

        if (!escape) {
            value += next();
            continue;
        }

        escape  = false;
        char ch = generate_escape(next(), line_number);

        value += ch;
    }

    // The string literal terminated right after the use of '\'
    if (escape) {
        diagnostics::report_error("Incomplete escape sequence", line_number);
    }

    // Either the line ended or the file did, if we don't receive a '"'.
    if (!match('"')) {
        diagnostics::report_error("Unterminated string literal", line_number);
    }

    tokens.push_back({TokenKind::LiteralString, value, line_number});
}

void Lexer::tokenize_char(std::vector<Token>& tokens) {
    std::string value;
    bool escape = false;

    // Gneiss intentionally permits multiple characters in a character literal.
    // This keeps character and string lexing identical; semantic validation can
    // later warn about literals longer than one character.
    while (!end() && !check('\n') && (escape || !check('\''))) {
        if (!escape && match('\\')) {
            escape = true;
            continue;
        }

        if (!escape) {
            value += next();
            continue;
        }

        escape  = false;
        char ch = generate_escape(next(), line_number);

        value += ch;
    }

    // We just issue a warning if the user writes something like
    // var c = 'fuck the rules';
    if (value.size() > 1)
        diagnostics::report_warning("Character literal cannot exceed a length of 1.", line_number);

    // However, we DO NOT accept empty character literal
    if (value.empty()) {
        diagnostics::report_error("Character literal cannot be empty", line_number);
    }

    // Same error handling logic as string literal

    if (escape) {
        diagnostics::report_error("Incomplete escape sequence", line_number);
    }

    if (!match('\'')) {
        diagnostics::report_error("Unterminated character literal", line_number);
    }

    tokens.push_back({TokenKind::LiteralChar, value, line_number});
}

// we have one common generate_escape for char and string
// so, you can write \' in a string literal and it will be lexed as ', even
// though you COULD just write ' on its own, since string literals use double
// quote
char Lexer::generate_escape(char c, size_t line_number) {
    switch (c) {
    case 'n':
        return '\n';
    case 'r':
        return '\r';
    case 't':
        return '\t';
    case '\\':
        return '\\';
    case '\"':
        return '\"';
    case '\'':
        return '\'';
    case 'b':
        return '\b';
    case '0':
        diagnostics::report_warning("Null character is not supported", line_number);
        return c;
    default:
        diagnostics::report_warning("Unknown escape sequence \\" + std::string(1, c), line_number);
        // Invalid escape sequences evaluate to their original form. For
        // example, \q becomes q in the literal
        return c;
    }
}

} // namespace gneiss::frontend