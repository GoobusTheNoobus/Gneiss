/* =============================================================
 *
 *                       G N E I S S
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * File: Diagnostic.cpp
 * Description: Implementation of the diagnostic system
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#include <gneiss/Core/Core.hpp>
#include <gneiss/Core/Diagnostic.hpp>
#include <iostream>

namespace gneiss::diagnostics {

static int error_count = 0;
int errors() { return error_count; }

// Errors don't immediately terminate. Instead, most of the time, errors can be
// recovered
void report_error(const std::string& message, size_t line_number) {
    ++error_count;
    std::cerr << ansi::RED << "Error on line " << line_number << ": " << message << '\n' << ansi::RESET;
}

void report_warning(const std::string& message, size_t line_number) {
    std::cerr << ansi::YELLOW << "Warning on line " << line_number << ": " << message << '\n' << ansi::RESET;
}

} // namespace gneiss::diagnostics