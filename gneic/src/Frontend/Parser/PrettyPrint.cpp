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

#include <gneiss/Frontend/Parser/PrettyPrint.hpp>

#include <cassert>
#include <iostream>
#include <sstream>

namespace gneiss::frontend::pretty {

namespace {

// we have these to eliminate the need to pass them through every function call
std::ostream* out = &std::cout;
int indent        = 0;

void dispatch(const std::unique_ptr<ASTNode>& node) {
    if (!node) {
        *out << std::string(indent, ' ') << "null\n";
        // std::cout << static_cast<int>(node->kind) << std::endl;
        return;
    }

    switch (node->kind) {
    case ASTNodeKind::BinaryExpression:
        print_binary(static_cast<const BinaryExpression&>(*node));
        break;
    case ASTNodeKind::Block:
        print_block(static_cast<const Block&>(*node));
        break;
    case ASTNodeKind::FunctionCallExpression:
        print_function_call(static_cast<const FunctionCallExpression&>(*node));
        break;
    case ASTNodeKind::Identifier:
        print_identifier(static_cast<const Identifier&>(*node));
        break;
    case ASTNodeKind::LiteralBool:
        print_bool(static_cast<const LiteralBool&>(*node));
        break;
    case ASTNodeKind::LiteralChar:
        print_char(static_cast<const LiteralChar&>(*node));
        break;
    case ASTNodeKind::LiteralFloat:
        print_float(static_cast<const LiteralFloat&>(*node));
        break;
    case ASTNodeKind::LiteralInt:
        print_int(static_cast<const LiteralInt&>(*node));
        break;
    case ASTNodeKind::LiteralString:
        print_string(static_cast<const LiteralString&>(*node));
        break;
    case ASTNodeKind::Program:
        throw std::runtime_error("Program node is nested.");
    case ASTNodeKind::StatementExit:
        print_exit(static_cast<const StatementExit&>(*node));
        break;
    case ASTNodeKind::StatementFunctionDefinition:
        print_function_def(static_cast<const StatementFunctionDefinition&>(*node));
        break;
    case ASTNodeKind::StatementIf:
        print_if(static_cast<const StatementIf&>(*node));
        break;
    case ASTNodeKind::StatementParameterDeclaration:
        print_param(static_cast<const StatementParameterDeclaration&>(*node));
        break;
    case ASTNodeKind::StatementPrint:
        print_print(static_cast<const StatementPrint&>(*node));
        break;
    case ASTNodeKind::StatementPrintln:
        print_println(static_cast<const StatementPrintln&>(*node));
        break;
    case ASTNodeKind::StatementReturn:
        print_return(static_cast<const StatementReturn&>(*node));
        break;
    case ASTNodeKind::StatementVariableAssignment:
        print_var_assignment(static_cast<const StatementVariableAssignment&>(*node));
        break;
    case ASTNodeKind::StatementVariableDeclaration:
        print_var_declaration(static_cast<const StatementVariableDeclaration&>(*node));
        break;
    case ASTNodeKind::UnaryExpression:
        print_unary(static_cast<const UnaryExpression&>(*node));
        break;
    default:
        throw std::runtime_error("Unknown node kind (id=" + std::to_string(static_cast<int>(node->kind)) + ")");
    }
}

} // namespace

void set_stream(std::ostream* os) { out = os; }

void print_ast(const Program& program) {
    for (const auto& node : program.block.children) {
        dispatch(node);
    }
}

void print_block(const Block& block) {
    indent += 2;
    for (const auto& node : block.children) {
        dispatch(node);
    }
    indent -= 2;
}

void print_identifier(const Identifier& identifier) {
    *out << std::string(indent, ' ') << "Identifier(" << identifier.name << ")\n";
}

void print_int(const LiteralInt& int_) { *out << std::string(indent, ' ') << "LiteralInt(" << int_.value << ")\n"; }
void print_float(const LiteralFloat& float_) {
    *out << std::string(indent, ' ') << "LiteralFloat(" << float_.value << ")\n";
}
void print_char(const LiteralChar& char_) {
    *out << std::string(indent, ' ') << "LiteralChar('" << char_.value << "')\n";
}
void print_bool(const LiteralBool& bool_) {
    *out << std::string(indent, ' ') << "LiteralBool(" << bool_.value << ")\n";
}
void print_string(const LiteralString& string) {
    *out << std::string(indent, ' ') << "LiteralString('" << string.value << "')\n";
}

void print_binary(const BinaryExpression& expr) {
    *out << std::string(indent, ' ') << "BinaryExpression(" << token_kind_repr(expr.op) << ")\n";
    indent += 2;
    dispatch(expr.left);
    dispatch(expr.right);
    indent -= 2;
}
void print_unary(const UnaryExpression& expr) {
    *out << std::string(indent, ' ') << "UnaryExpression(" << token_kind_repr(expr.op) << ")\n";
    indent += 2;
    dispatch(expr.operand);
    indent -= 2;
}

void print_function_call(const FunctionCallExpression& call) {
    assert(call.name->kind == ASTNodeKind::Identifier);

    *out << std::string(indent, ' ') << "FunctionCallExpression(" << static_cast<const Identifier&>(*call.name).name
         << ")\n";
    indent += 2;
    for (auto& param : call.params) {
        dispatch(param);
    }
    indent -= 2;
}

void print_print(const StatementPrint& stm) {
    *out << std::string(indent, ' ') << "StatementPrint()\n";
    indent += 2;
    for (auto& operand : stm.operands) {
        dispatch(operand);
    }
    indent -= 2;
}

void print_println(const StatementPrintln& stm) {
    *out << std::string(indent, ' ') << "StatementPrintln()\n";
    indent += 2;
    for (auto& operand : stm.operands) {
        dispatch(operand);
    }
    indent -= 2;
}

void print_exit(const StatementExit& stm) {
    *out << std::string(indent, ' ') << "Exit()\n";
    indent += 2;
    dispatch(stm.value);
    indent -= 2;
}
void print_return(const StatementReturn& stm) {
    *out << std::string(indent, ' ') << "Return()\n";
    indent += 2;
    dispatch(stm.value);
    indent -= 2;
}
void print_if(const StatementIf& stm) {
    *out << std::string(indent, ' ') << "If(\n";
    indent += 2;
    dispatch(stm.condition);
    indent -= 2;
    *out << std::string(indent, ' ') << ")\n";
    print_block(*stm.branch_if_true);
    *out << std::string(indent, ' ') << "Else\n";
    indent += 2;
    print_block(*stm.branch_if_false);
    indent -= 2;
}

void print_param(const StatementParameterDeclaration& stm) { *out << stm.type << ' ' << stm.name << ' '; }
void print_var_declaration(const StatementVariableDeclaration& stm) {
    *out << std::string(indent, ' ') << "StatementVariableDeclaration(" << stm.name << ", "
         << (stm.type.empty() ? "<infer>" : stm.type) << ")\n";
    if (!stm.value)
        return;

    indent += 2;
    dispatch(stm.value);
    indent -= 2;
}

void print_var_assignment(const StatementVariableAssignment& stm) {
    *out << std::string(indent, ' ') << "StatementVariableDeclaration(" << stm.name << ")\n";
    if (!stm.value)
        return;

    indent += 2;
    dispatch(stm.value);
    indent -= 2;
}

void print_function_def(const StatementFunctionDefinition& stm) {
    *out << std::string(indent, ' ') << "StatementFunctionDefinition(" << stm.name << ", " << stm.type << ")\n";
    indent += 2;
    for (auto& param : stm.params) {
        print_param(param);
    }

    print_block(*stm.body);
    indent -= 2;
}

} // namespace gneiss::frontend::pretty