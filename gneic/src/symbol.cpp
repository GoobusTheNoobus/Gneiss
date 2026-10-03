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

#include "gneiss/symbol.hpp"

namespace gneiss::sema {

void Scope::define(Variable var) {
    symbols[var.name] = std::move(var);
}
Scope::

} // namespace gneiss::sema