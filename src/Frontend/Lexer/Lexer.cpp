/* =============================================================
 *
 *                       G N E I S S
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#include "Lexer.hpp"

#include "../../Core/Diagnostic.hpp"

namespace gneiss::frontend {

std::vector<Token> Lexer::tokenize(std::string source) {
    this->source = std::move(source);
    std::vector<Token> tokens;

    while (!end()) {
        char current = peek();

        if (match('#'))
            skip_comment();

        else if (std::isspace(static_cast<unsigned char>(current)))
            next();

        else if (std::isdigit(static_cast<unsigned char>(current)))
            tokenize_number(tokens);

        else if (std::isalpha(static_cast<unsigned char>(current)) ||
                 current == '_')
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

void Lexer::skip_comment() {
    while (!end() && !check('\n')) {
        next();
    }
}

void Lexer::tokenize_number(std::vector<Token>& tokens) {
    std::string value;
    auto kind = TokenKind::LiteralInt;

    while (!end() &&
           (std::isdigit(static_cast<unsigned char>(peek())) || check('.'))) {
        char current = next();

        if (current == '.') {
            if (kind == TokenKind::LiteralFloat)
                diagnostics::report_error("Too many dots in float literal",
                                          line_number);
            else
                kind = TokenKind::LiteralFloat;
        }

        value += current;
    }

    tokens.push_back({kind, value, line_number});
}

void Lexer::tokenize_word(std::vector<Token>& tokens) {
    std::string value;

    while (!end() &&
           (std::isalnum(static_cast<unsigned char>(peek())) || check('_'))) {
        value += next();
    }

    auto kind = TokenKind::Identifier;
    if (value == "var")
        kind = TokenKind::KeywordVar;
    if (value == "function")
        kind = TokenKind::KeywordFunction;
    if (value == "void")
        kind = TokenKind::KeywordVoid;
    if (value == "print")
        kind = TokenKind::KeywordPrint;
    if (value == "println")
        kind = TokenKind::KeywordPrintln;
    if (value == "exit")
        kind = TokenKind::KeywordExit;
    if (value == "return")
        kind = TokenKind::KeywordReturn;
    if (value == "true")
        kind = TokenKind::KeywordTrue;
    if (value == "false")
        kind = TokenKind::KeywordFalse;
    if (value == "if")
        kind = TokenKind::KeywordIf;
    if (value == "else")
        kind = TokenKind::KeywordElse;

    tokens.push_back({kind, value, line_number});
}

void Lexer::tokenize_symbol(std::vector<Token>& tokens) {
    char c = next();
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

    switch (c) {
    case '+':
        tokens.push_back({TokenKind::OperatorPlus, "+", line_number});
        return;
    case '-':
        if (match('>')) {
            tokens.push_back({TokenKind::Arrow, "->", line_number});
            return;
        }

        tokens.push_back({TokenKind::OperatorMinus, "-", line_number});
        return;
    case '*':
        tokens.push_back({TokenKind::OperatorStar, "*", line_number});
        return;
    case '/':
        tokens.push_back({TokenKind::OperatorSlash, "/", line_number});
        return;
    case '%':
        tokens.push_back({TokenKind::OperatorPercent, "%", line_number});
        return;
    case '=':
        if (match('=')) {
            tokens.push_back({TokenKind::OperatorCompEqual, "==", line_number});
            return;
        }
        tokens.push_back({TokenKind::Equal, "=", line_number});
        return;
    case '>':
        if (match('=')) {
            tokens.push_back(
                {TokenKind::OperatorCompGreaterEqual, ">=", line_number});
            return;
        }

        tokens.push_back({TokenKind::OperatorCompGreater, ">", line_number});
        return;
    case '<':
        if (match('=')) {
            tokens.push_back(
                {TokenKind::OperatorCompLessEqual, "<=", line_number});
            return;
        }

        tokens.push_back({TokenKind::OperatorCompLess, "<", line_number});
        return;

    case '!':
        if (match('=')) {
            tokens.push_back(
                {TokenKind::OperatorCompNotEqual, "!=", line_number});
            return;
        }
    default:
        diagnostics::report_error("Unknown symbol '" + std::string(1, c) + "'",
                                  line_number);
    }
}

void Lexer::tokenize_string(std::vector<Token>& tokens) {
    std::string value;
    bool escape = false;

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

    if (escape) {
        diagnostics::report_error("Incomplete escape sequence", line_number);
    }

    if (!match('"')) {
        diagnostics::report_error("Unterminated string literal", line_number);
    }

    tokens.push_back({TokenKind::LiteralString, value, line_number});
}

void Lexer::tokenize_char(std::vector<Token>& tokens) {
    std::string value;
    bool escape = false;

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

    if (value.size() > 1)
        diagnostics::report_warning(
            "Character literal cannot exceed a length of 1.", line_number);

    if (value.empty()) {
        diagnostics::report_error("Character literal cannot be empty",
                                  line_number);
    }

    if (escape) {
        diagnostics::report_error("Incomplete escape sequence", line_number);
    }

    if (!match('\'')) {
        diagnostics::report_error("Unterminated character literal",
                                  line_number);
    }

    tokens.push_back({TokenKind::LiteralChar, value, line_number});
}

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
        diagnostics::report_warning("Null character is not supported",
                                    line_number);
        return c;
    default:
        diagnostics::report_warning(
            "Unknown escape sequence \\" + std::string(1, c), line_number);
        return c;
    }
}

} // namespace gneiss::frontend