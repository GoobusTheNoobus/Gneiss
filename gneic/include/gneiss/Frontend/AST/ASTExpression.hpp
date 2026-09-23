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
#include <gneiss/Frontend/AST/AST.hpp>
#include <gneiss/Frontend/Lexer/Token.hpp>

namespace gneiss::frontend {

struct Identifier : public ASTNode {
    Identifier(std::string name) : ASTNode(ASTNodeKind::Identifier), name(std::move(name)) {}
    std::string name;
};

struct LiteralInt : public ASTNode {
    LiteralInt(uint64_t value) : ASTNode(ASTNodeKind::LiteralInt), value(value) {}
    uint64_t value;
};

struct LiteralFloat : public ASTNode {
    LiteralFloat(double value) : ASTNode(ASTNodeKind::LiteralFloat), value(value) {}
    double value;
};

struct LiteralChar : public ASTNode {
    LiteralChar(char value) : ASTNode(ASTNodeKind::LiteralChar), value(value) {}
    char value;
};

struct LiteralBool : public ASTNode {
    LiteralBool(bool value) : ASTNode(ASTNodeKind::LiteralBool), value(value) {}
    bool value;
};

struct LiteralString : public ASTNode {
    LiteralString(std::string value) : ASTNode(ASTNodeKind::LiteralString), value(std::move(value)) {}
    std::string value;
};

struct BinaryExpression : public ASTNode {
    BinaryExpression(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, TokenKind op)
        : ASTNode(ASTNodeKind::BinaryExpression), left(std::move(left)), right(std::move(right)), op(op) {}
    std::unique_ptr<ASTNode> left, right;
    TokenKind op;
};

struct UnaryExpression : public ASTNode {
    UnaryExpression(std::unique_ptr<ASTNode> operand, TokenKind op)
        : ASTNode(ASTNodeKind::UnaryExpression), operand(std::move(operand)), op(op) {}
    std::unique_ptr<ASTNode> operand;
    TokenKind op;
};

struct FunctionCallExpression : public ASTNode {
    FunctionCallExpression(std::unique_ptr<ASTNode> name, std::vector<std::unique_ptr<ASTNode>> params)
        : ASTNode(ASTNodeKind::FunctionCallExpression), name(std::move(name)), params(std::move(params)) {}
    std::unique_ptr<ASTNode> name;
    std::vector<std::unique_ptr<ASTNode>> params;
};

} // namespace gneiss::frontend