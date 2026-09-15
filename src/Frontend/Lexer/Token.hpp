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
#include <string>
#include <vector>

namespace gneiss::frontend {

enum class TokenKind {
    EndOfFile,
    Error,

    Identifier,
    LiteralString,
    LiteralInt,
    LiteralFloat,
    LiteralChar,

    KeywordVar,
    KeywordFunction,
    KeywordVoid,
    KeywordPrint,
    KeywordPrintln,
    KeywordExit,
    KeywordReturn,
    KeywordTrue,
    KeywordFalse,
    KeywordIf,
    KeywordElse,

    OperatorPlus,
    OperatorMinus,
    OperatorStar,
    OperatorSlash,
    OperatorPercent,

    OperatorCompLess,
    OperatorCompGreater,
    OperatorCompLessEqual,
    OperatorCompGreaterEqual,
    OperatorCompEqual,
    OperatorCompNotEqual,

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
    TokenKind kind = TokenKind::Error;
    std::string data;
    size_t line_number = 0;
};

std::string token_kind_to_string(TokenKind kind);
std::ostream& operator<<(std::ostream& os, const Token& token);
std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens);

} // namespace gneiss::frontend