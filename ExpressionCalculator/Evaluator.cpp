#include "Evaluator.h"

namespace
{

    struct Evaluator
    {
        double operator()(double num)
        {
            return num;
        }

        double operator()(const ast::UnaryExpr& u)
        {
            return u.func(std::visit(*this, *u.rhs));
        }

        double operator()(const ast::BinaryExpr& b)
        {
            return b.func(std::visit(*this, *b.lhs), std::visit(*this, *b.rhs));
        }
    };

} // namespace

namespace ast
{

    double evaluate(const ast::Expr& ast)
    {
        return std::visit(Evaluator(), ast);
    }

} // namespace ast
