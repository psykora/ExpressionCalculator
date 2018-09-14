#pragma once

#include <variant>
#include <iostream>

namespace lex
{
    struct Number
    {
        double num;
    };
    struct Op1
    {
        char op;
    };
    struct Op2
    {
        char op;
    };
    struct LeftParenthesis
    {};
    struct RightParenthesis
    {};

    using Token =
        std::variant<Number, Op1, Op2, LeftParenthesis, RightParenthesis, std::nullptr_t>;

    /**
     * Simplistic lexer - token parser
     *  Token -> Decimal | Op1 | Op2 | LeftParenthesis | RightParenthesis
     *  Decimal -> [0-9.]+
     *  Op1 -> [+ -]
     *  Op2 -> [* /]
     *  LeftParenthesis -> [(]
     *  RightParenthesis -> [)]
     * 
     * @param is  Stream to read from
     * @return next token from the stream or nullptr if EOF
     */
    Token nextToken(std::istream& is);
} // namespace lex