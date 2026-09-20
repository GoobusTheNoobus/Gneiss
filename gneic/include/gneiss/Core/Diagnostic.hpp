/* =============================================================
 *
 *                       G N E I S S
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * File: Diagnostic.hpp
 * Description: Interface for the diagnostic system
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once
#include <string>

namespace gneiss::diagnostics {

// Basic error reporting
void report_error(const std::string& message, size_t line_number);
void report_warning(const std::string& message, size_t line_number);
int errors();

} // namespace gneiss::diagnostics