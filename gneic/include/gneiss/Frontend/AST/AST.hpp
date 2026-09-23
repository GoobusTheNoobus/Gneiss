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
 * File: AST.hpp
 * Description: Definition of some base AST nodes
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once

#include <memory>
#include <vector>

namespace gneiss::frontend {

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

using ASTNodeID = size_t;

struct ASTNode {
    explicit ASTNode(ASTNodeKind kind) : kind(kind), id{} {}
    ASTNodeKind kind;
    ASTNodeID id;
    size_t line_number{};
};

struct Block : public ASTNode {
    Block() : ASTNode(ASTNodeKind::Block) {}
    std::vector<std::unique_ptr<ASTNode>> children;
};

struct Program : public ASTNode {
    Program() : ASTNode(ASTNodeKind::Program) {}
    Block block;
};

} // namespace gneiss::frontend