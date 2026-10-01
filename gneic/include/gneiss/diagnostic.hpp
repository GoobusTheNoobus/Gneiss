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
#include <string>
#include <vector>

namespace gneiss {

class DiagnosticEngine {
public:
    void raise_error(std::string message, usize line_number);
    void raise_warning(std::string message, usize line_number);

    void print(std::ostream& out);

    int count_errors() const;

private:
    enum class DiagnosticSeverity { Error, Warning };

    struct Diagnostic {
        std::string message;
        usize line_number;
        DiagnosticSeverity severity;
    };

    std::vector<Diagnostic> diagnostics;
};

} // namespace gneiss