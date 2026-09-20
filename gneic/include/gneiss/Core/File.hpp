/* =============================================================
 *
 *                       G N E I S S
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * File: File.hpp
 * Description: Interface for file related function(s)
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once
#include <optional>
#include <string>

namespace gneiss {

// returns std::nullopt if there is an error reading the file
std::optional<std::string> read_file(const std::string& path);
} // namespace gneiss