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

#include "Token.hpp"
#include <sstream>

namespace gneiss::frontend {

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "{data: \'" << token.data
       << "\', kind: " << token_kind_to_string(token.kind) << ", line: " << token.line_number << '}';
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens) {
    os << "[\n";
    for (size_t i = 0; i < tokens.size(); ++i) {
        os << "  " << tokens[i];
        if (i != tokens.size() - 1)
            os << ',';
        os << '\n';
    }

    os << "]\n";

    return os;
}

std::string token_kind_to_string(TokenKind kind) {
    switch (kind) {
    case TokenKind::EndOfFile:
        return "EndOfFile";
    case TokenKind::Error:
        return "Error";
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
    case TokenKind::KeywordVar:
        return "KeywordVar";
    case TokenKind::KeywordFunction:
        return "KeywordFunction";
    case TokenKind::KeywordVoid:
        return "KeywordVoid";
    case TokenKind::KeywordPrint:
        return "KeywordPrint";
    case TokenKind::KeywordPrintln:
        return "KeywordPrintln";
    case TokenKind::KeywordExit:
        return "KeywordExit";
    case TokenKind::KeywordReturn:
        return "KeywordReturn";
    case TokenKind::KeywordTrue:
        return "KeywordTrue";
    case TokenKind::KeywordFalse:
        return "KeywordFalse";
    case TokenKind::OperatorPlus:
        return "OperatorPlus";
    case TokenKind::OperatorMinus:
        return "OperatorMinus";
    case TokenKind::OperatorStar:
        return "OperatorStar";
    case TokenKind::OperatorSlash:
        return "OperatorSlash";
    case TokenKind::OperatorPercent:
        return "OperatorPercent";
    case TokenKind::OperatorCompLess:
        return "OperatorCompLess";
    case TokenKind::OperatorCompGreater:
        return "OperatorCompGreater";
    case TokenKind::OperatorCompLessEqual:
        return "OperatorCompLessEqual";
    case TokenKind::OperatorCompGreaterEqual:
        return "OperatorCompGreaterEqual";
    case TokenKind::OperatorCompEqual:
        return "OperatorCompEqual";
    case TokenKind::OperatorCompNotEqual:
        return "OperatorCompNotEqual";
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
    case TokenKind::KeywordIf:
        return "KeywordIf";
    case TokenKind::KeywordElse:
        return "KeywordElse";
    default:
        return "Unknown (id " + std::to_string(static_cast<int>(kind)) + ")";
    }
}

} // namespace gneiss::frontend