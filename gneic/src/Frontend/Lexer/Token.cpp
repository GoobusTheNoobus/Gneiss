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
 * File: Token.cpp
 * Description: Implementation for token representation functions
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#include <gneiss/Frontend/Lexer/Token.hpp>
#include <sstream>

namespace gneiss::frontend {

// Prints a single token in a compact debug representation;
// weird formatting can occur if the token is a string/char containing escape
// characters.
std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token_kind_to_string(token.kind) << "('" << token.data + "')";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens) {
    for (const Token& token : tokens) {
        os << token << '\n';
    }

    return os;
}

std::string token_kind_to_string(TokenKind kind) {
    switch (kind) {
    case TokenKind::EndOfFile:
        return "EndOfFile";
    case TokenKind::Identifier:
        return "Identifier";
    case TokenKind::LiteralString:
        return "LiteralString";
    case TokenKind::LiteralInt:
        return "LiteralInt";
    case TokenKind::LiteralFloat:
        return "LiteralFloat";
    case TokenKind::LiteralChar:
        return "LiteralChar";
    case TokenKind::KwVar:
        return "KwVar";
    case TokenKind::KwFunction:
        return "KwFunction";
    case TokenKind::KwVoid:
        return "KwVoid";
    case TokenKind::KwPrint:
        return "KwPrint";
    case TokenKind::KwPrintln:
        return "KwPrintln";
    case TokenKind::KwExit:
        return "KwExit";
    case TokenKind::KwReturn:
        return "KwReturn";
    case TokenKind::KwTrue:
        return "KwTrue";
    case TokenKind::KwFalse:
        return "KwFalse";
    case TokenKind::Plus:
        return "Plus";
    case TokenKind::Minus:
        return "Minus";
    case TokenKind::Star:
        return "Star";
    case TokenKind::Slash:
        return "Slash";
    case TokenKind::Percent:
        return "Percent";
    case TokenKind::LessThan:
        return "LessThan";
    case TokenKind::GreaterThan:
        return "GreaterThan";
    case TokenKind::LessEqualTo:
        return "LessEqualTo";
    case TokenKind::GreaterEqualTo:
        return "GreaterEqualTo";
    case TokenKind::EqualEqual:
        return "EqualEqual";
    case TokenKind::BangEqual:
        return "BangEqual";
    case TokenKind::Arrow:
        return "Arrow";
    case TokenKind::LeftParen:
        return "LeftParen";
    case TokenKind::RightParen:
        return "RightParen";
    case TokenKind::LeftBracket:
        return "LeftBracket";
    case TokenKind::RightBracket:
        return "RightBracket";
    case TokenKind::LeftBrace:
        return "LeftBrace";
    case TokenKind::RightBrace:
        return "RightBrace";
    case TokenKind::Semicolon:
        return "Semicolon";
    case TokenKind::Colon:
        return "Colon";
    case TokenKind::Dot:
        return "Dot";
    case TokenKind::Comma:
        return "Comma";
    case TokenKind::Equal:
        return "Equal";
    case TokenKind::KwIf:
        return "KwIf";
    case TokenKind::KwElse:
        return "KwElse";
    default:
        return "Unknown (id " + std::to_string(static_cast<int>(kind)) + ")";
    }
}

std::string token_kind_repr(TokenKind kind) {
    switch (kind) {
    case TokenKind::Arrow:
        return "'->'";
    case TokenKind::Colon:
        return "':'";
    case TokenKind::Comma:
        return "','";
    case TokenKind::Dot:
        return "'.'";
    case TokenKind::EndOfFile:
        return "EOF";
    case TokenKind::Equal:
        return "'='";
    case TokenKind::Identifier:
        return "identifier";

    case TokenKind::LiteralString:
        return "string literal";
    case TokenKind::LiteralInt:
        return "integer literal";
    case TokenKind::LiteralFloat:
        return "float literal";
    case TokenKind::LiteralChar:
        return "character literal";

    case TokenKind::KwElse:
        return "'else'";
    case TokenKind::KwExit:
        return "'exit'";
    case TokenKind::KwFalse:
        return "'false'";
    case TokenKind::KwFunction:
        return "'function'";
    case TokenKind::KwIf:
        return "'if'";
    case TokenKind::KwPrint:
        return "'print'";
    case TokenKind::KwPrintln:
        return "'println'";
    case TokenKind::KwReturn:
        return "'return'";
    case TokenKind::KwTrue:
        return "'true'";
    case TokenKind::KwVar:
        return "'var'";
    case TokenKind::KwVoid:
        return "'void'";

    case TokenKind::Plus:
        return "'+'";
    case TokenKind::Minus:
        return "'-'";
    case TokenKind::Star:
        return "'*'";
    case TokenKind::Slash:
        return "'/'";
    case TokenKind::Percent:
        return "'%'";

    case TokenKind::LessThan:
        return "'<'";
    case TokenKind::GreaterThan:
        return "'>'";
    case TokenKind::LessEqualTo:
        return "'<='";
    case TokenKind::GreaterEqualTo:
        return "'>='";
    case TokenKind::EqualEqual:
        return "'=='";
    case TokenKind::BangEqual:
        return "'!='";

    case TokenKind::LeftParen:
        return "'('";
    case TokenKind::RightParen:
        return "')'";
    case TokenKind::LeftBracket:
        return "'['";
    case TokenKind::RightBracket:
        return "']'";
    case TokenKind::LeftBrace:
        return "'{'";
    case TokenKind::RightBrace:
        return "'}'";

    case TokenKind::Semicolon:
        return "';'";
    default:
        return "Unknown (id " + std::to_string(static_cast<int>(kind)) + ")";
    }
}

} // namespace gneiss::frontend