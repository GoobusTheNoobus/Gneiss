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
 * File: PrettyPrint.hpp
 * Description: Interface for pretty printing functions for printing AST nodes
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once
#include <gneiss/Frontend/AST/AST.hpp>
#include <gneiss/Frontend/AST/ASTExpression.hpp>
#include <gneiss/Frontend/AST/ASTStatement.hpp>

namespace gneiss::frontend::pretty {

void set_stream(std::ostream* os);

void print_ast(const Program& program);
void print_block(const Block& block);

void print_identifier(const Identifier& identifier);
void print_int(const LiteralInt& int_);
void print_float(const LiteralFloat& float_);
void print_char(const LiteralChar& char_);
void print_bool(const LiteralBool& bool_);
void print_string(const LiteralString& string);

void print_binary(const BinaryExpression& expr);
void print_unary(const UnaryExpression& expr);
void print_function_call(const FunctionCallExpression& call);

void print_print(const StatementPrint& stm);
void print_println(const StatementPrintln& stm);
void print_exit(const StatementExit& stm);
void print_return(const StatementReturn& stm);
void print_if(const StatementIf& stm);

void print_param(const StatementParameterDeclaration& stm);
void print_var_declaration(const StatementVariableDeclaration& stm);
void print_var_assignment(const StatementVariableAssignment& stm);
void print_function_def(const StatementFunctionDefinition& stm);

} // namespace gneiss::frontend::pretty