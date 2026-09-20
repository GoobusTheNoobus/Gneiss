/* =============================================================
 *
 *                       G N E I S S
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * File: File.cpp
 * Description: Implementation for file related function(s)
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#include <gneiss/Core/File.hpp>

#include <fstream>
#include <sstream>

namespace gneiss {

std::optional<std::string> read_file(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {

        return std::nullopt;
    }

    // we extract the file stream's buffer
    std::stringstream stream;
    stream << file.rdbuf();

    return stream.str();
}

} // namespace gneiss