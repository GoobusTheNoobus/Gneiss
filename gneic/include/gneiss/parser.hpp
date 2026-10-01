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

#pragma once
#include "gneiss/ast.hpp"
#include "gneiss/diagnostic.hpp"
#include "gneiss/token.hpp"
#include <vector>

namespace gneiss::parse {

class Parser {
public:
    explicit Parser(DiagnosticEngine* diagnostic) : diagnostic(diagnostic) {}

    // Main parse function
    Program parse(const std::vector<Token>& tokens);

private:
    std::unique_ptr<ASTNode> parse_statement();

    // Just a wrapper function to the lowest precedence function
    std::unique_ptr<ASTNode> parse_expr() { return parse_equality_comp(); }

    // ==, !=
    std::unique_ptr<ASTNode> parse_equality_comp();

    // <, >, <=, >=
    std::unique_ptr<ASTNode> parse_relational_comp();

    // +, - (3 + 4 - 3)
    std::unique_ptr<ASTNode> parse_additive();

    // /, *, %
    std::unique_ptr<ASTNode> parse_multiplicative();

    // +, - (+10)
    std::unique_ptr<ASTNode> parse_unary();

    // like function calls
    std::unique_ptr<ASTNode> parse_postfix();

    std::unique_ptr<ASTNode> parse_primary();

    std::vector<std::unique_ptr<ASTNode>> parse_call_params();
    std::vector<StatementParameterDeclaration> parse_function_params();
    std::unique_ptr<Block> parse_block();

    // parser helper functions
    [[nodiscard]] bool end() const;
    [[nodiscard]] const Token& peek() const;
    [[nodiscard]] const Token& peek_next() const;

    const Token& next();

    [[nodiscard]] bool check(TokenKind expected) const;
    [[nodiscard]] bool match(TokenKind expected);
    bool expect(TokenKind expected);

    // make_unique alias that also assigns node id
    template <typename Type, typename... ArgTypes>
    std::unique_ptr<Type> make_node(size_t line_number, ArgTypes&&... args) {
        auto node         = std::make_unique<Type>(std::forward<ArgTypes>(args)...);
        node->id          = id++;
        node->line_number = line_number;
        return node;
    }

    std::vector<Token> source;
    size_t position{}; // brace initialize because cool
    ASTNodeID id{};

    DiagnosticEngine* diagnostic;
};

} // namespace gneiss::parse