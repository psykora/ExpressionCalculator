#pragma once

#include "AST.h"

namespace parser
{
    /**
     * Parse input stream into an AST tree
     *
     * EBNF Grammar
     *  E -> T {op1 T}*
     *  T -> F {op2 F}*
     *  F -> number | op1 F | '(' E ')'
     */
    ast::Expr parse(std::istream& is);

} // namespace parser