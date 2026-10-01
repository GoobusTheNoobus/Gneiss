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
#include "core.hpp"
#include "gneiss/token.hpp"

#include <memory>
#include <vector>

namespace gneiss::parse {

enum class ASTNodeKind {

    Program,
    Block,

    Identifier,
    LiteralInt,
    LiteralFloat,
    LiteralChar,
    LiteralBool,
    LiteralString,

    StatementParameterDeclaration,
    StatementVariableDeclaration,
    StatementVariableAssignment,
    StatementFunctionDefinition,

    StatementPrint,
    StatementPrintln,
    StatementExit,
    StatementReturn,
    StatementIf,

    BinaryExpression,
    UnaryExpression,
    FunctionCallExpression,

};

using ASTNodeID = usize;

/**
 * @brief Base class for all nodes in the Gneiss abstract syntax tree.
 *
 * Each node stores its kind and source line number.
 */

struct ASTNode {
    explicit ASTNode(ASTNodeKind kind) : kind(kind) {}
    ASTNodeKind kind;
    usize line_number{};
};

struct Block : ASTNode {
    Block() : ASTNode(ASTNodeKind::Block) {}
    std::vector<std::unique_ptr<ASTNode>> children;
};

struct Program : ASTNode {
    Program() : ASTNode(ASTNodeKind::Program) {}
    Block block;
};

struct Identifier : ASTNode {
    explicit Identifier(std::string name) : ASTNode(ASTNodeKind::Identifier), name(std::move(name)) {}
    std::string name;
};

struct LiteralInt : ASTNode {
    explicit LiteralInt(uint64_t value) : ASTNode(ASTNodeKind::LiteralInt), value(value) {}
    uint64_t value;
};

struct LiteralFloat : ASTNode {
    explicit LiteralFloat(double value) : ASTNode(ASTNodeKind::LiteralFloat), value(value) {}
    double value;
};

struct LiteralChar : ASTNode {
    explicit LiteralChar(char value) : ASTNode(ASTNodeKind::LiteralChar), value(value) {}
    char value;
};

struct LiteralBool : ASTNode {
    explicit LiteralBool(bool value) : ASTNode(ASTNodeKind::LiteralBool), value(value) {}
    bool value;
};

struct LiteralString : ASTNode {
    explicit LiteralString(std::string value) : ASTNode(ASTNodeKind::LiteralString), value(std::move(value)) {}
    std::string value;
};

struct BinaryExpression : ASTNode {
    BinaryExpression(std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right, TokenKind op)
        : ASTNode(ASTNodeKind::BinaryExpression), left(std::move(left)), right(std::move(right)), op(op) {}
    std::unique_ptr<ASTNode> left, right;
    TokenKind op;
};

struct UnaryExpression : ASTNode {
    UnaryExpression(std::unique_ptr<ASTNode> operand, TokenKind op)
        : ASTNode(ASTNodeKind::UnaryExpression), operand(std::move(operand)), op(op) {}
    std::unique_ptr<ASTNode> operand;
    TokenKind op;
};

struct FunctionCallExpression : ASTNode {
    FunctionCallExpression(std::unique_ptr<ASTNode> name, std::vector<std::unique_ptr<ASTNode>> params)
        : ASTNode(ASTNodeKind::FunctionCallExpression), name(std::move(name)), params(std::move(params)) {}
    std::unique_ptr<ASTNode> name;
    std::vector<std::unique_ptr<ASTNode>> params;
};

struct StatementParameterDeclaration : ASTNode {
    StatementParameterDeclaration(std::string name, std::string type)
        : ASTNode(ASTNodeKind::StatementVariableDeclaration), name(std::move(name)), type(std::move(type)) {}

    std::string name;
    std::string type;
};

struct StatementVariableDeclaration : ASTNode {
    StatementVariableDeclaration(std::string name, std::string type, std::unique_ptr<ASTNode> value)
        : ASTNode(ASTNodeKind::StatementVariableDeclaration), name(std::move(name)), type(std::move(type)),
          value(std::move(value)) {}

    std::string name;
    std::string type;
    std::unique_ptr<ASTNode> value;
};

struct StatementVariableAssignment : ASTNode {
    StatementVariableAssignment(std::string name, std::unique_ptr<ASTNode> value)
        : ASTNode(ASTNodeKind::StatementVariableAssignment), name(std::move(name)), value(std::move(value)) {}

    std::string name;
    std::unique_ptr<ASTNode> value;
};

struct StatementFunctionDefinition : ASTNode {
    StatementFunctionDefinition(std::string name, std::string type, std::vector<StatementParameterDeclaration> params,
                                std::unique_ptr<Block> body)
        : ASTNode(ASTNodeKind::StatementFunctionDefinition), name(std::move(name)), type(std::move(type)),
          params(std::move(params)), body(std::move(body)) {}
    std::string name;
    std::string type;
    std::vector<StatementParameterDeclaration> params;
    std::unique_ptr<Block> body;
};

struct StatementPrint : ASTNode {
    explicit StatementPrint(std::vector<std::unique_ptr<ASTNode>> operands)
        : ASTNode(ASTNodeKind::StatementPrint), operands(std::move(operands)) {}
    std::vector<std::unique_ptr<ASTNode>> operands;
};

struct StatementPrintln : ASTNode {
    explicit StatementPrintln(std::vector<std::unique_ptr<ASTNode>> operands)
        : ASTNode(ASTNodeKind::StatementPrintln), operands(std::move(operands)) {}
    std::vector<std::unique_ptr<ASTNode>> operands;
};

struct StatementExit : ASTNode {
    explicit StatementExit(std::unique_ptr<ASTNode> value)
        : ASTNode(ASTNodeKind::StatementExit), value(std::move(value)) {}
    std::unique_ptr<ASTNode> value;
};

struct StatementReturn : ASTNode {
    explicit StatementReturn(std::unique_ptr<ASTNode> value)
        : ASTNode(ASTNodeKind::StatementReturn), value(std::move(value)) {}
    std::unique_ptr<ASTNode> value;
};

struct StatementIf : ASTNode {
    StatementIf(std::unique_ptr<ASTNode> condition, std::unique_ptr<Block> branch_if_true,
                std::unique_ptr<Block> branch_if_false)
        : ASTNode(ASTNodeKind::StatementIf), condition(std::move(condition)), branch_if_true(std::move(branch_if_true)),
          branch_if_false(std::move(branch_if_false)) {}

    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<Block> branch_if_true;
    std::unique_ptr<Block> branch_if_false;
};

} // namespace gneiss::parse