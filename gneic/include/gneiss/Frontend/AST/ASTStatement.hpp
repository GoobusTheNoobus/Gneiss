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
#include <optional>

namespace gneiss::frontend {

struct StatementParameterDeclaration : public ASTNode {
    StatementParameterDeclaration(std::string name, std::string type)
        : ASTNode(ASTNodeKind::StatementVariableDeclaration), name(std::move(name)), type(std::move(type)) {}

    std::string name;
    std::string type;
};

struct StatementVariableDeclaration : public ASTNode {
    StatementVariableDeclaration(std::string name, std::string type, std::unique_ptr<ASTNode> value)
        : ASTNode(ASTNodeKind::StatementVariableDeclaration), name(std::move(name)), type(std::move(type)),
          value(std::move(value)) {}

    std::string name;
    std::string type;
    std::unique_ptr<ASTNode> value;
};

struct StatementVariableAssignment : public ASTNode {
    StatementVariableAssignment(std::string name, std::unique_ptr<ASTNode> value)
        : ASTNode(ASTNodeKind::StatementVariableAssignment), name(std::move(name)), value(std::move(value)) {}

    std::string name;
    std::unique_ptr<ASTNode> value;
};

struct StatementFunctionDefinition : public ASTNode {
    StatementFunctionDefinition(std::string name, std::string type, std::vector<StatementParameterDeclaration> params,
                                std::unique_ptr<Block> body)
        : ASTNode(ASTNodeKind::StatementFunctionDefinition), name(std::move(name)), type(std::move(type)),
          params(std::move(params)), body(std::move(body)) {}
    std::string name;
    std::string type;
    std::vector<StatementParameterDeclaration> params;
    std::unique_ptr<Block> body;
};

struct StatementPrint : public ASTNode {
    explicit StatementPrint(std::vector<std::unique_ptr<ASTNode>> operands)
        : ASTNode(ASTNodeKind::StatementPrint), operands(std::move(operands)) {}
    std::vector<std::unique_ptr<ASTNode>> operands;
};

struct StatementPrintln : public ASTNode {
    explicit StatementPrintln(std::vector<std::unique_ptr<ASTNode>> operands)
        : ASTNode(ASTNodeKind::StatementPrintln), operands(std::move(operands)) {}
    std::vector<std::unique_ptr<ASTNode>> operands;
};

struct StatementExit : public ASTNode {
    explicit StatementExit(std::unique_ptr<ASTNode> value)
        : ASTNode(ASTNodeKind::StatementExit), value(std::move(value)) {}
    std::unique_ptr<ASTNode> value;
};

struct StatementReturn : public ASTNode {
    explicit StatementReturn(std::unique_ptr<ASTNode> value)
        : ASTNode(ASTNodeKind::StatementReturn), value(std::move(value)) {}
    std::unique_ptr<ASTNode> value;
};

struct StatementIf : public ASTNode {
    StatementIf(std::unique_ptr<ASTNode> condition, std::unique_ptr<Block> branch_if_true,
                std::unique_ptr<Block> branch_if_false)
        : ASTNode(ASTNodeKind::StatementIf), condition(std::move(condition)), branch_if_true(std::move(branch_if_true)),
          branch_if_false(std::move(branch_if_false)) {}

    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<Block> branch_if_true;
    std::unique_ptr<Block> branch_if_false;
};

} // namespace gneiss::frontend