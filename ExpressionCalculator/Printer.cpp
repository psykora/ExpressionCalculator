#include "Printer.h"

#include <iostream>

namespace
{

    struct Printer
    {
    public:
        Printer(std::ostream& os) : m_os(os) {}

        void operator()(double num)
        {
            m_os << num;
        }

        void operator()(const ast::UnaryExpr& u)
        {
            m_os << u.func.symbol();
            std::visit(*this, *u.rhs);
        }

        void operator()(const ast::BinaryExpr& b)
        {
            m_os << '(';
            std::visit(*this, *b.lhs);
            m_os << b.func.symbol();
            std::visit(*this, *b.rhs);
            m_os << ')';
        }

    private:
        std::ostream& m_os;
    };

} // namespace

namespace ast
{

    void print(const ast::Expr& ast, std::ostream& os)
    {
        std::visit(Printer(os), ast);
    }

} // namespace ast
