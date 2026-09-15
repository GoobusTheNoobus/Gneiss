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

#include "Core/File.hpp"
#include "Frontend/Lexer/Lexer.hpp"

#include <iostream>

#define VERSION "0.1.0"

int main(int argc, char* argv[]) {

    // The user has given no extra argument(s)
    // Note that the executable counts as one argument, hence argc <= 1
    if (argc <= 1) {
        // Print usage
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

    std::string path = std::move(arg1);

    std::optional<std::string> source = gneiss::read_file(path);

    if (!source) return 1;

    gneiss::frontend::Lexer lexer;
    auto tokens = lexer.tokenize(*source);

    std::cout << tokens << std::endl;

}
