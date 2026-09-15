# =============================================================
#
#                        G N E I S S
#
# =============================================================
#
# Gneiss is a toy programming language developed in C++20
#
# Gneiss is licensed under the MIT license
# Copyright (c) 2026  GoobusTheNoobus

cmake_minimum_required(VERSION 3.20)
project(Gneiss)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(gneiss
        src/main.cpp
        src/main.cpp
        src/Core/File.hpp
        src/Core/File.cpp
        src/Core/Ansi.hpp
        src/Frontend/Lexer/Token.hpp
        src/Frontend/Lexer/Token.cpp
        src/Frontend/Lexer/Lexer.hpp
        src/Frontend/Lexer/Lexer.cpp
        src/Core/Diagnostic.hpp
        src/Core/Diagnostic.cpp
)

