#pragma once

#include "AST.h"

namespace ast
{

    /**
     * Evaluation mathematical expression in given Abstract Syntax Tree
     */
    double evaluate(const ast::Expr& ast);

} // namespace ast