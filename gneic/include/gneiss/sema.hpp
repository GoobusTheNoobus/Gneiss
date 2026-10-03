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

#include "diagnostic.hpp"
#include "symbol.hpp"

namespace gneiss {
struct Program;
}
namespace gneiss::sema {

class Sema {
public:
    Sema(DiagnosticEngine* diagnostic) : diagnostic(diagnostic) {
    }

    void analyze(Program& node);

    // TODO: implement

private:
    DiagnosticEngine* diagnostic;
};

} // namespace gneiss::sema