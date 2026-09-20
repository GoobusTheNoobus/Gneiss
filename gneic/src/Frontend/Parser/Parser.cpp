/* =============================================================
 *
 *                       G N E I S S
 *
 * =============================================================
 *
 * Gneiss is a toy programming language developed in C++20
 *
 * File: Parser.cpp
 * Description: Implementation for Parser, used for syntactic analysis
 *
 * Gneiss is licenced under the MIT license
 * Copyright (c) 2026  GoobusTheNoobus
 */

#include <gneiss/Core/Core.hpp>
#include <gneiss/Core/Diagnostic.hpp>
#include <gneiss/Frontend/AST/ASTExpression.hpp>
#include <gneiss/Frontend/AST/ASTStatement.hpp>
#include <gneiss/Frontend/Lexer/Token.hpp>
#include <gneiss/Frontend/Parser/Parser.hpp>

#include <charconv>

namespace gneiss::frontend {

Program Parser::parse(const std::vector<Token>& tokens) {
    Program program;

    this->source = tokens;

    while (!end()) {
        if (match(TokenKind::Semicolon))
            continue;

        if (check(TokenKind::EndOfFile))
            break;

        program.block.children.push_back(parse_statement());
    }

    return program;
}

std::unique_ptr<Block> Parser::parse_block() {
    auto block = make_node<Block>(peek().line_number);

    while (!end() && !check(TokenKind::RightBrace)) {
        if (match(TokenKind::Semicolon))
            continue;

        block->children.push_back(parse_statement());
    }

    return block;
}

std::unique_ptr<ASTNode> Parser::parse_statement() {
    auto token = peek();

    usize line_number = peek().line_number;

    switch (token.kind) {
    case TokenKind::KwExit: {
        next();

        auto node = make_node<StatementExit>(line_number, parse_expr());

        expect(TokenKind::Semicolon);

        return node;
    }
    case TokenKind::KwFunction: {
        next();

        std::string name = peek().data;
        next();

        expect(TokenKind::LeftParen);
        auto params = parse_function_params();
        expect(TokenKind::RightParen);

        std::string type = "void";

        if (match(TokenKind::Arrow)) {
            // identifiers are just types, while void is a special keyword
            if (peek().kind != TokenKind::Identifier && peek().kind != TokenKind::KwVoid) {
                diagnostics::report_error("Invalid type name '" + peek().data + "'", peek().line_number);

            } else {
                type = peek().data;
                next();
            }
        }

        expect(TokenKind::LeftBrace);
        auto block = parse_block();
        expect(TokenKind::RightBrace);

        return make_node<StatementFunctionDefinition>(line_number, name, type, std::move(params), std::move(block));
    }
    case TokenKind::KwIf: {
        next();

        auto condition = parse_expr();

        expect(TokenKind::LeftBrace);
        auto branch_if_true = parse_block();
        expect(TokenKind::RightBrace);

        std::unique_ptr<Block> branch_if_false;

        if (match(TokenKind::KwElse)) {
            expect(TokenKind::LeftBrace);
            branch_if_false = std::move(parse_block());
            expect(TokenKind::RightBrace);
        }

        return make_node<StatementIf>(line_number, std::move(condition), std::move(branch_if_true),
                                      std::move(branch_if_false));
    }
    case TokenKind::KwPrint:
    case TokenKind::KwPrintln: {
        next();

        std::vector<std::unique_ptr<ASTNode>> operands;
        while (!end() && !match(TokenKind::Semicolon)) {
            operands.push_back(std::move(parse_expr()));
        }

        if (token.kind == TokenKind::KwPrintln)
            return make_node<StatementPrintln>(line_number, std::move(operands));

        return make_node<StatementPrint>(line_number, std::move(operands));
    }
    case TokenKind::KwReturn: {
        next();

        if (match(TokenKind::Semicolon))
            return make_node<StatementReturn>(line_number, nullptr);

        auto node = make_node<StatementReturn>(line_number, parse_expr());

        expect(TokenKind::Semicolon);

        return node;
    }
    case TokenKind::KwVar: {
        next();

        std::string name;

        if (check(TokenKind::Identifier)) {
            name = next().data;
        } else {
            diagnostics::report_error("Expected identifier", peek().line_number);
        }

        std::string type;
        if (match(TokenKind::Colon)) {
            type = peek().data;

            if (check(TokenKind::Identifier)) {
                type = next().data;
            } else if (check(TokenKind::KwVoid)) {
                diagnostics::report_error("Variable cannot be type void", next().line_number);
            } else {
                diagnostics::report_error("Expected type name", peek().line_number);
            }
        }

        std::unique_ptr<ASTNode> value = nullptr;
        if (match(TokenKind::Equal)) {
            value = parse_expr();
        }

        expect(TokenKind::Semicolon);

        if (!value && type.empty()) {
            diagnostics::report_error("Cannot deduce type", line_number);
        }

        return make_node<StatementVariableDeclaration>(line_number, name, type, std::move(value));
    }
    case TokenKind::LeftBrace: {
        next();

        auto block = parse_block();
        expect(TokenKind::RightBrace);

        return block;
    }
    case TokenKind::Identifier: {
        if (peek_next().kind == TokenKind::Equal) {
            std::string name = next().data;
            next();

            auto value = parse_expr();

            expect(TokenKind::Semicolon);

            return make_node<StatementVariableAssignment>(line_number, name, std::move(value));
        }
    }
    default: {
        auto expr = parse_expr();
        expect(TokenKind::Semicolon);
        return expr;
    }
    }
}

std::unique_ptr<ASTNode> Parser::parse_equality_comp() {
    usize line_number = peek().line_number;

    auto left = parse_relational_comp();

    while (!end() && (check(TokenKind::EqualEqual) || check(TokenKind::BangEqual))) {
        TokenKind op = next().kind;

        auto right = parse_relational_comp();

        // we move left and right into a single operation stored in left
        left = make_node<BinaryExpression>(line_number, std::move(left), std::move(right), op);
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parse_relational_comp() {
    usize line_number = peek().line_number;

    auto left = parse_additive();

    while (!end() && (check(TokenKind::LessThan) || check(TokenKind::LessEqualTo) || check(TokenKind::GreaterThan) ||
                      check(TokenKind::GreaterEqualTo))) {
        TokenKind op = next().kind;

        auto right = parse_additive();

        // we move left and right into a single operation stored in left
        left = make_node<BinaryExpression>(line_number, std::move(left), std::move(right), op);
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parse_additive() {
    usize line_number = peek().line_number;

    auto left = parse_multiplicative();

    while (!end() && (check(TokenKind::Plus) || check(TokenKind::Minus))) {
        TokenKind op = next().kind;

        auto right = parse_multiplicative();

        // we move left and right into a single operation stored in left
        left = make_node<BinaryExpression>(line_number, std::move(left), std::move(right), op);
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parse_multiplicative() {
    usize line_number = peek().line_number;

    auto left = parse_unary();

    while (!end() && (check(TokenKind::Star) || check(TokenKind::Slash) || check(TokenKind::Percent))) {

        TokenKind op = next().kind;

        auto right = parse_unary();

        // we move left and right into a single operation stored in left
        left = make_node<BinaryExpression>(line_number, std::move(left), std::move(right), op);
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parse_unary() {
    usize line_number = peek().line_number;

    if (!end() && (check(TokenKind::Plus) || check(TokenKind::Minus))) {
        TokenKind op = next().kind;

        return make_node<UnaryExpression>(line_number, parse_unary(), op);
    }

    return parse_postfix();
}

std::unique_ptr<ASTNode> Parser::parse_postfix() {
    usize line_number = peek().line_number;

    auto expr = parse_primary();

    while (!end() && match(TokenKind::LeftParen)) {
        auto call_params = parse_call_params();
        expr             = make_node<FunctionCallExpression>(line_number, std::move(expr), std::move(call_params));
    }

    return expr;
}

std::unique_ptr<ASTNode> Parser::parse_primary() {
    Token token       = peek();
    usize line_number = token.line_number;

    switch (peek().kind) {
    case TokenKind::Identifier:
        return make_node<Identifier>(line_number, next().data);
    case TokenKind::LiteralChar: {
        char data{};
        if (!token.data.empty())
            data = token.data[0];

        next();
        return make_node<LiteralChar>(line_number, data);
    }
    case TokenKind::LiteralFloat: {
        f64 data{};

        auto [ptr, ec] = std::from_chars(token.data.data(), token.data.data() + token.data.size(), data);

        if (ec != std::errc{}) {
            diagnostics::report_error("Invalid float literal " + token.data, line_number);
        }
        next();
        return make_node<LiteralFloat>(line_number, data);
    }
    case TokenKind::LiteralInt: {
        i64 data{};

        auto [ptr, ec] = std::from_chars(token.data.data(), token.data.data() + token.data.size(), data);

        if (ec != std::errc{}) {
            diagnostics::report_error("Invalid int literal " + token.data, line_number);
        }
        next();
        return make_node<LiteralInt>(line_number, data);
    }
    case TokenKind::LiteralString:
        return make_node<LiteralString>(line_number, next().data);
    case TokenKind::KwTrue:
        next();
        return make_node<LiteralBool>(line_number, true);
    case TokenKind::KwFalse:
        next();
        return make_node<LiteralBool>(line_number, false);
    case TokenKind::LeftParen: {
        next();
        auto expr = parse_expr();
        expect(TokenKind::RightParen);
        return expr;
    }
    default:
        Token tok = next();
        diagnostics::report_error("Expected expression, got '" +
                                      (tok.kind == TokenKind::EndOfFile ? "EOF" : "'" + tok.data + "'") + "'",
                                  line_number);
        return nullptr;
    }
}

std::vector<std::unique_ptr<ASTNode>> Parser::parse_call_params() {
    std::vector<std::unique_ptr<ASTNode>> call_params;
    while (!end() && !check(TokenKind::RightParen)) {
        call_params.push_back(parse_expr());

        // we allow trailing commas
        if (!check(TokenKind::RightParen)) {
            expect(TokenKind::Comma);
        }
    }

    expect(TokenKind::RightParen);

    return call_params;
}

std::vector<StatementParameterDeclaration> Parser::parse_function_params() {
    std::vector<StatementParameterDeclaration> def_params;

    while (!end() && !check(TokenKind::RightParen)) {
        std::string name;
        std::string type;

        // we allow unnamed names
        if (check(TokenKind::Identifier)) {
            name = peek().data;
            next();
        }

        expect(TokenKind::Colon);

        if (check(TokenKind::Identifier)) {
            type = next().data;
        }

        else if (check(TokenKind::KwVoid)) {
            diagnostics::report_error("Parameter cannot be type void", next().line_number);
        }

        else {
            diagnostics::report_error("Expected type name", peek().line_number);
        }

        StatementParameterDeclaration param{name, type};
        param.id = id++;

        def_params.push_back(param);

        // we allow trailing commas
        if (!check(TokenKind::RightParen)) {
            expect(TokenKind::Comma);
        }
    }

    return def_params;
}

} // namespace gneiss::frontend
