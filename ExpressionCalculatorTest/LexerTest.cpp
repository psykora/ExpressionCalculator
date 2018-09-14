#include "Lexer.h"

#include "gtest/gtest.h"

#include <sstream>

TEST(LexerTest, parseEmpty)
{
    std::istringstream is("");

    EXPECT_TRUE(std::holds_alternative<nullptr_t>(lex::nextToken(is)));
}

TEST(LexerTest, parseZero)
{
    std::istringstream is("0");

    EXPECT_DOUBLE_EQ(std::get<lex::Number>(lex::nextToken(is)).num, 0);
    EXPECT_TRUE(std::holds_alternative<nullptr_t>(lex::nextToken(is)));
}

TEST(LexerTest, parseExpression)
{
    std::istringstream is("-(0\t/12.334+3  *2)(");

    EXPECT_EQ(std::get<lex::Op1>(lex::nextToken(is)).op, '-');
    EXPECT_TRUE(std::holds_alternative<lex::LeftParenthesis>(lex::nextToken(is)));
    EXPECT_DOUBLE_EQ(std::get<lex::Number>(lex::nextToken(is)).num, 0);
    EXPECT_EQ(std::get<lex::Op2>(lex::nextToken(is)).op, '/');
    EXPECT_DOUBLE_EQ(std::get<lex::Number>(lex::nextToken(is)).num, 12.334);
    EXPECT_EQ(std::get<lex::Op1>(lex::nextToken(is)).op, '+');
    EXPECT_DOUBLE_EQ(std::get<lex::Number>(lex::nextToken(is)).num, 3);
    EXPECT_EQ(std::get<lex::Op2>(lex::nextToken(is)).op, '*');
    EXPECT_DOUBLE_EQ(std::get<lex::Number>(lex::nextToken(is)).num, 2);
    EXPECT_TRUE(std::holds_alternative<lex::RightParenthesis>(lex::nextToken(is)));
    EXPECT_TRUE(std::holds_alternative<lex::LeftParenthesis>(lex::nextToken(is)));
    EXPECT_TRUE(std::holds_alternative<nullptr_t>(lex::nextToken(is)));
}