#include "Evaluator.h"

#include "gtest/gtest.h"

#include <sstream>

namespace
{
    static const UnaryFuncPlus<double> unaryFuncPlus;
    static const UnaryFuncMinus<double> unaryFuncMinus;

    static const BinaryFuncPlus<double> binaryFuncPlus;
    static const BinaryFuncMinus<double> binaryFuncMinus;
    static const BinaryFuncMultiply<double> binaryFuncMultiply;
    static const BinaryFuncDivide<double> binaryFuncDivide;
} // namespace

TEST(EvaluatorTest, evaluateZero)
{
    ast::Expr expr = double{1234.455};
    double result = ast::evaluate(expr);
    EXPECT_DOUBLE_EQ(result, 1234.455);
}

TEST(EvaluatorTest, evaluateSimple)
{
    ast::BinaryExpr mul{binaryFuncMultiply, std::make_unique<ast::Expr>(3),
                        std::make_unique<ast::Expr>(4)};
    ast::BinaryExpr sum{binaryFuncPlus, std::make_unique<ast::Expr>(3),
                        std::make_unique<ast::Expr>(std::move(mul))};
    ast::Expr expr = ast::UnaryExpr{unaryFuncMinus, std::make_unique<ast::Expr>(std::move(sum))};

    double result = ast::evaluate(expr);
    EXPECT_DOUBLE_EQ(result, -15);
}
