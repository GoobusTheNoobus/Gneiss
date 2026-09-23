/* =============================================================
*          ____   _   _   _____   ___   ____    ____  
*         / ___| | \ | | | ____| |_ _| / ___|  / ___| 
*        | |  _  |  \| | |  _|    | |  \___ \  \___ \ 
*        | |_| | | |\  | | |___   | |   ___) |  ___) |
*         \____| |_| \_| |_____| |___| |____/  |____/ 
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * File: Core.hpp
 * Description: Declaration of some core stuff used throughout the project
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#pragma once
#include <cstddef>
#include <cstdint>

namespace gneiss {

// define Rust-style types since C++ integer types are ugly
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

using usize = size_t;
using isize = ptrdiff_t;

// ANSI text decoration codes used for error/warning reporting and such

namespace ansi {

inline constexpr auto RESET   = "\033[0m";
inline constexpr auto RED     = "\033[31m";
inline constexpr auto YELLOW  = "\033[33m";
inline constexpr auto MAGENTA = "\033[35m";

} // namespace ansi

} // namespace gneiss