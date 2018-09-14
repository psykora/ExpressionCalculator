#pragma once

#include "AST.h"

namespace ast
{

    /**
     * Printn Abstract Syntax Tree with parentheses to display structure 
     */
    void print(const ast::Expr& ast, std::ostream& os);

} // namespace ast