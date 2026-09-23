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
 * File: main.cpp
 * Description: Compiler entry point
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#include <gneiss/Core/Core.hpp>
#include <gneiss/Core/File.hpp>
#include <gneiss/Frontend/Lexer/Lexer.hpp>
#include <gneiss/Frontend/Parser/Parser.hpp>
#include <gneiss/Frontend/Parser/PrettyPrint.hpp>

#include <iostream>

#define VERSION "0.1.0"

int main(int argc, char* argv[]) {

    // the user has given no extra argument(s)
    // note that the executable counts as one argument, hence argc <= 1
    if (argc <= 1) {
        // print usage
        std::cerr << "Gneiss is a toy programming language.\n"
                     "Usage:  gneiss [options] file.gneiss\n"
                     "Confused? Run:  gneiss --help\n";
        return 1;
    }

    std::string arg1 = argv[1];

    if (arg1 == "--version") {
        std::cout << "Gneiss compiler v" VERSION "\n";
        return 0;
    }

    if (arg1 == "--help") {
        std::cout << "Gneiss is a toy programming language.\n\n"
                     "Usage:  gneiss [options] file.gneiss\n\n"
                     "Options: \n"
                     "  --version       # displays the version\n"
                     "  --help          # displays this message\n\n"
                     "That's basically it. Feel free to experiment. Bye!\n";
        return 0;
    }

    // lexical analysis
    if (arg1 == "--lexa") {
        if (argc <= 2) {
            std::cerr << gneiss::ansi::RED << "ERROR: Missing input file \n";
            return 1;
        }

        std::string path = argv[2];

        std::optional<std::string> source = gneiss::read_file(path);

        if (!source)
            return 1;

        gneiss::frontend::Lexer lexer;
        std::cout << lexer.tokenize(*source) << std::flush;

        return gneiss::diagnostics::errors() >= 1;
    }

    // syntactic analysis
    if (arg1 == "--syna") {
        if (argc <= 2) {
            std::cerr << gneiss::ansi::RED << "ERROR: Missing input file \n";
            return 1;
        }

        std::string path = argv[2];

        std::optional<std::string> source = gneiss::read_file(path);

        if (!source)
            return 1;

        gneiss::frontend::Lexer lexer;
        auto tokens = lexer.tokenize(*source);

        gneiss::frontend::Parser parser;
        auto ast = parser.parse(tokens);

        gneiss::frontend::pretty::print_ast(ast);

        return 0;
    }

    std::string path = std::move(arg1);

    std::optional<std::string> source = gneiss::read_file(path);

    if (!source)
        return 1;

    // TODO: finish compiler and compile source code
}
