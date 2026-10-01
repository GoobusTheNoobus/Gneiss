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
#include "gneiss/ast.hpp"

namespace gneiss::parse::pretty {

/**
 * @brief Sets the output stream used by the pretty printer.
 *
 * @param os The stream to which AST output is written.
 */
void set_stream(std::ostream* os);

/**
 * @brief Prints a complete AST to the configured output stream.
 *
 * @param program The program AST to print.
 */
void print_ast(const Program& program);

} // namespace gneiss::parse::pretty