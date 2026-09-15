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

#include "File.hpp"
#include "Ansi.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

namespace gneiss {

std::optional<std::string> read_file(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << ansi::RED << "ERROR: Cannot open source file '" << path
                  << "'\n";
        return std::nullopt;
    }

    std::stringstream stream;
    stream << file.rdbuf();

    return stream.str();
}

} // namespace gneiss