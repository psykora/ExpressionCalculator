#pragma once

#include "Functional.h"

#include <memory>
#include <variant>

namespace ast
{
    struct UnaryExpr;
    struct BinaryExpr;

    using Expr = std::variant<UnaryExpr, BinaryExpr, double>;

    struct UnaryExpr
    {
        const IUnaryFunc<double>& func;
        std::unique_ptr<Expr> rhs;
    };

    struct BinaryExpr
    {
        const IBinaryFunc<double>& func;
        std::unique_ptr<Expr> lhs;
        std::unique_ptr<Expr> rhs;
    };

} // namespace ast
