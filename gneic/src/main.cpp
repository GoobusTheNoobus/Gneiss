/* =============================================================
 *          ____   _   _   _____   ___   ____    ____
 *         / ___| | \ | | | ____| |_ _| / ___|  / ___|
 *        | |  _  |  \| | |  _|    | |  \___ \  \___ \
 *        | |_| | | |\  | | |___   | |   ___) |  ___) |
 *         \____| |_| \_| |_____| |___| |____/  |____/
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * Gneiss is licenced under the MIT license
 */

#include "gneiss/ast_pretty.hpp"
#include "gneiss/core.hpp"
#include "gneiss/file.hpp"
#include "gneiss/lexer.hpp"
#include "gneiss/parser.hpp"

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

        gneiss::DiagnosticEngine engine;

        gneiss::parse::Lexer lexer(&engine);
        std::cout << lexer.tokenize(*source) << std::flush;

        engine.print(std::cerr);

        return engine.count_errors() >= 1;
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

        gneiss::DiagnosticEngine engine;

        gneiss::parse::Lexer lexer(&engine);
        auto tokens = lexer.tokenize(*source);

        gneiss::parse::Parser parser(&engine);
        auto ast = parser.parse(tokens);

        gneiss::parse::pretty::print_ast(ast);

        engine.print(std::cerr);

        return engine.count_errors() >= 1;
    }

    std::string path = std::move(arg1);

    std::optional<std::string> source = gneiss::read_file(path);

    if (!source)
        return 1;

    // TODO: finish compiler and compile source code
}
