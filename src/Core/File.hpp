/* =============================================================
 *
 *                       G N E I S S
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * Gneiss is licensed under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once
#include <optional>
#include <string>

namespace gneiss {
std::optional<std::string> read_file(const std::string& path);
}