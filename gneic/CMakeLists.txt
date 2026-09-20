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

# compiler sources needed for both testing and actual program
set(GNEISS_COMPILER_SOURCES
        include/gneiss/Core/File.hpp
        include/gneiss/Core/Core.hpp
        include/gneiss/Core/Diagnostic.hpp
        include/gneiss/Frontend/Lexer/Token.hpp
        include/gneiss/Frontend/Lexer/Lexer.hpp
        include/gneiss/Frontend/AST/AST.hpp
        include/gneiss/Frontend/AST/ASTExpression.hpp
        include/gneiss/Frontend/AST/ASTStatement.hpp
        include/gneiss/Frontend/Parser/Parser.hpp
        include/gneiss/Frontend/Parser/PrettyPrint.hpp

        src/Core/File.cpp
        src/Core/Diagnostic.cpp
        src/Frontend/Lexer/Token.cpp
        src/Frontend/Lexer/Lexer.cpp
        src/Frontend/Parser/Parser.cpp
        src/Frontend/Parser/PrettyPrint.cpp
)

# main build
add_executable(gneic
        ${GNEISS_COMPILER_SOURCES}
        src/main.cpp
)

target_include_directories(gneic PRIVATE include)


