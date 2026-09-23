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
 * File: Token.hpp
 * Description: Declaration for token kinds and structure
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once
#include <string>
#include <vector>

namespace gneiss::frontend {

enum class TokenKind {
    EndOfFile,

    Identifier,
    LiteralString,
    LiteralInt,
    LiteralFloat,
    LiteralChar,

    KwVar,
    KwFunction,
    KwVoid,
    KwPrint,
    KwPrintln,
    KwExit,
    KwReturn,
    KwTrue,
    KwFalse,
    KwIf,
    KwElse,

    Plus,
    Minus,
    Star,
    Slash,
    Percent,

    LessThan,
    GreaterThan,
    LessEqualTo,
    GreaterEqualTo,
    EqualEqual,
    BangEqual,

    Equal,
    Arrow,
    LeftParen,
    RightParen,
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,

    Semicolon,
    Colon,
    Dot,
    Comma,
};

struct Token {
    TokenKind kind;
    std::string data;
    size_t line_number = 0;
};

// human-readable representation helpers
std::string token_kind_to_string(TokenKind kind);
std::ostream& operator<<(std::ostream& os, const Token& token);
std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens);
std::string token_kind_repr(TokenKind kind); // for error reporting

} // namespace gneiss::frontend