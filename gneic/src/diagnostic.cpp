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

#include "gneiss/diagnostic.hpp"
#include "gneiss/core.hpp"

#include <algorithm>
#include <iostream>
#include <utility>

namespace gneiss {

int DiagnosticEngine::count_errors() const {
    int errors = 0;

    for (const Diagnostic& d : diagnostics) {
        errors += d.severity == DiagnosticSeverity::Error ? 1 : 0;
    }

    return errors;
}

void DiagnosticEngine::raise_error(std::string message, usize line_number) {
    diagnostics.push_back(
        {.message = std::move(message), .line_number = line_number, .severity = DiagnosticSeverity::Error});
}

void DiagnosticEngine::raise_warning(std::string message, usize line_number) {
    diagnostics.push_back(
        {.message = std::move(message), .line_number = line_number, .severity = DiagnosticSeverity::Warning});
}

void DiagnosticEngine::print(std::ostream& out) {
    std::sort(diagnostics.data(), diagnostics.data() + diagnostics.size(),
              [](const Diagnostic& d1, const Diagnostic& d2) -> bool { return d1.line_number > d2.line_number; });

    for (const Diagnostic& d : diagnostics) {
        if (d.severity == DiagnosticSeverity::Warning) {
            out << ansi::YELLOW << "On line " << d.line_number << " Warning: " << d.message << ansi::RESET << '\n';
        } else {
            out << ansi::RED << "On line " << d.line_number << " Error: " << d.message << ansi::RESET << '\n';
        }
    }
}

} // namespace gneiss