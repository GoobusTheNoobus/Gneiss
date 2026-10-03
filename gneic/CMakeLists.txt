# =============================================================
#          ____   _   _   _____   ___   ____    ____
#         / ___| | \ | | | ____| |_ _| / ___|  / ___|
#        | |  _  |  \| | |  _|    | |  \___ \  \___ \
#        | |_| | | |\  | | |___   | |   ___) |  ___) |
#         \____| |_| \_| |_____| |___| |____/  |____/
#
# =============================================================
#
# Gneiss is a toy programming language developed in C++20
#
# Gneiss is licenced under the MIT license

cmake_minimum_required(VERSION 3.20)

set(GNEISS_COMPILER_SOURCES
    src/ast_pretty.cpp
    src/diagnostic.cpp
    src/file.cpp
    src/lexer.cpp
    src/main.cpp
    src/parser.cpp
    src/token.cpp

    include/gneiss/ast.hpp
    include/gneiss/ast_pretty.hpp
    include/gneiss/core.hpp
    include/gneiss/diagnostic.hpp
    include/gneiss/file.hpp
    include/gneiss/lexer.hpp
    include/gneiss/parser.hpp
    include/gneiss/token.hpp
    include/gneiss/symbol.hpp
    include/gneiss/types.hpp
    include/gneiss/symbol.hpp
    src/symbol.cpp
    include/gneiss/sema.hpp
)

# main build
add_executable(gneic
    ${GNEISS_COMPILER_SOURCES}
)

target_include_directories(gneic PRIVATE include)


