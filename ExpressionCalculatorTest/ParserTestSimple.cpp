#include "Parser.h"

#include "gtest/gtest.h"

#include <sstream>

TEST(ParserTestSimple, parseZero)
{
    std::istringstream is("0");

    auto result = parser::parse(is);
    EXPECT_DOUBLE_EQ(std::get<double>(result), 0);
}

TEST(ParserTestSimple, parseNumber)
{
    std::istringstream is("74563.4421");

    auto result = parser::parse(is);
    EXPECT_DOUBLE_EQ(std::get<double>(result), 74563.4421);
}

TEST(ParserTestSimple, parseNegativeNumber)
{
    std::istringstream is("- 2");

    auto result = parser::parse(is);
    const auto& unaryExpr = std::get<ast::UnaryExpr>(result);
    EXPECT_EQ(unaryExpr.func.symbol(), "-");
    EXPECT_DOUBLE_EQ(std::get<double>(*unaryExpr.rhs), 2);
}

TEST(ParserTestSimple, parseRedundantParentheses)
{
    std::istringstream is("((- ((2))))");

    auto result = parser::parse(is);
    const auto& unaryExpr = std::get<ast::UnaryExpr>(result);
    EXPECT_EQ(unaryExpr.func.symbol(), "-");
    EXPECT_DOUBLE_EQ(std::get<double>(*unaryExpr.rhs), 2);
}

TEST(ParserTestSimple, parseInvalid)
{
    std::istringstream is("*");
    EXPECT_THROW(auto result = parser::parse(is), std::runtime_error);
}

TEST(ParserTestSimple, parseNotClosed)
{
    std::istringstream is("(1 + 2");
    EXPECT_THROW(auto result = parser::parse(is), std::runtime_error);
}
