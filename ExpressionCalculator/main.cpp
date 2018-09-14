#include "AST.h"
#include "Evaluator.h"
#include "Parser.h"
#include "Printer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    /*    ast::BinaryExpr mul{std::multiplies(), std::make_unique<ast::Expr>(3),
                            std::make_unique<ast::Expr>(4)};
        ast::BinaryExpr sum{std::plus(), std::make_unique<ast::Expr>(3),
                            std::make_unique<ast::Expr>(std::move(mul))};
        ast::Expr expr = ast::UnaryExpr{[](double val) { return -val; },
                                        std::make_unique<ast::Expr>(std::move(sum))};

        std::visit(Printer(std::cout), expr);
        std::cout << " = ";
        std::cout << std::visit(Evaluator(), expr) << std::endl;

        std::string calcExpression{"1 + 3 * 5"}; */

    std::vector<std::string> calcExpressions = {
        {"1 + 3 * 5"}, {"1 + (3 * 5)"}, {"(1 + 3) * 5"}, {"-1"}, {"-(1 + 2 * 3 + 4)"}};
    for (const auto calcExpression : calcExpressions)
    {
        std::istringstream calcExpressionStream(calcExpression);
        auto ast = parser::parse(calcExpressionStream);

        ast::print(ast, std::cout);
        std::cout << " = ";
        std::cout << ast::evaluate(ast) << std::endl;
    }
}
