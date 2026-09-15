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

#include "Diagnostic.hpp"
#include "Ansi.hpp"

#include <iostream>

namespace gneiss::diagnostics {

static int error_count = 0;

int errors() { return error_count; }

void report_error(const std::string& message, size_t line_number) {
    ++error_count;
    std::cerr << ansi::RED << "Error on line " << line_number << ": " << message
              << '\n'
              << ansi::RESET;
}

void report_warning(const std::string& message, size_t line_number) {
    std::cerr << ansi::YELLOW << "Warning on line " << line_number << ": "
              << message << '\n'
              << ansi::RESET;
}

} // namespace gneiss::diagnostics