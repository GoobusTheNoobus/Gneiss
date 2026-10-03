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
#include "types.hpp"

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace gneiss::sema {

struct Variable {
    std::string name;
    Type type;
};

struct Function {
    std::string name;
    std::vector<Type> overload;
    Type return_type;
};

class Scope {
    std::unordered_map<std::string, Variable> symbols;

public:
    void define(Variable);
    std::optional<Variable> lookup(const std::string& name);
};

} // namespace gneiss::sema