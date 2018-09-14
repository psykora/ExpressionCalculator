#include "Parser.h"
#include "Lexer.h"

#include <stack>

namespace
{
    /**
     * Converted BNF grammar:
     *  E -> T {op1 T}*
     *  T -> F {op2 F}*
     *  F -> number | op1 F | '(' E ')'
     *
     *  E  -> T E'
     *  E' -> @ | bin_op1 T E'
     *  T  -> F T'
     *  T' -> @ | bin_op2 F T'
     *  F  -> number | bin_op1 F | '(' E ')'
     */

    // non-terminals
    struct Expression
    {};
    struct Expression2
    {};
    struct Term
    {};
    struct Term2
    {};
    struct Factor
    {};

    // special rules for building AST
    struct MakeUnary
    {
        const IUnaryFunc<double>& op;
    };
    struct MakeBinary
    {
        const IBinaryFunc<double>& op;
    };

    using Rule = std::variant<Expression, Expression2, Term, Term2, Factor, MakeUnary, MakeBinary,
                               lex::RightParenthesis>;

    static const UnaryFuncPlus<double> unaryFuncPlus;
    static const UnaryFuncMinus<double> unaryFuncMinus;

    static const BinaryFuncPlus<double> binaryFuncPlus;
    static const BinaryFuncMinus<double> binaryFuncMinus;
    static const BinaryFuncMultiply<double> binaryFuncMultiply;
    static const BinaryFuncDivide<double> binaryFuncDivide;

    const IUnaryFunc<double>& operatorToUnaryFunc(char op)
    {
        switch (op)
        {
        case '+':
            return unaryFuncPlus;
        case '-':
            return unaryFuncMinus;
        default:
            throw std::runtime_error("Unsupported operator");
        }
    }

    const IBinaryFunc<double>& operatorToBinaryFunc(char op)
    {
        switch (op)
        {
        case '+':
            return binaryFuncPlus;
        case '-':
            return binaryFuncMinus;
        case '*':
            return binaryFuncMultiply;
        case '/':
            return binaryFuncDivide;
        default:
            throw std::runtime_error("Unsupported operator");
        }
    }

    /**
     * Pop without copying
     *
     * @note Hack until standard library allows this
     */
    template <typename T>
    auto pop(std::stack<T>& s)
    {
        auto retVal = std::move(s.top());
        s.pop();
        return retVal;
    }

    class Parser
    {
    public:
        Parser(std::istream& is) : m_is(is) {}

    public:
        template <typename S, typename T>
        void operator()(S s, const T& t)
        {
            throw std::runtime_error("Unexpected state or input token");
        }

        /**
         * E  -> T E'
         *
         * @note Could handle all valid token variants as using LL(1) parsing table
         */
        template <typename T>
        void operator()(Expression, const T& anything)
        {
            m_ruleStack.push(Expression2{});
            m_ruleStack.push(Term{});
        }

        /** E' -> @ */
        template <typename T>
        void operator()(Expression2, const T& anything)
        {}

        /** E' -> bin_op1 T E' */
        template <>
        void operator()(Expression2, const lex::Op1& binop)
        {
            m_ruleStack.push(Expression2{});
            m_ruleStack.push(MakeBinary{operatorToBinaryFunc(binop.op)});
            m_ruleStack.push(Term{});
            consumeToken();
        }

        /** T  -> F T' */
        template <typename T>
        void operator()(Term, const T& anything)
        {
            m_ruleStack.push(Term2{});
            m_ruleStack.push(Factor{});
        }

        /** T' -> @ */
        template <typename T>
        void operator()(Term2, const T& anything)
        {}

        /** T ' ->  bin_op2 F T' */
        template <>
        void operator()(Term2, const lex::Op2& binop)
        {
            m_ruleStack.push(Term2{});
            m_ruleStack.push(MakeBinary{operatorToBinaryFunc(binop.op)});
            m_ruleStack.push(Factor{});
            consumeToken();
        }

        /** F -> number */ 
        template <>
        void operator()(Factor, const lex::Number& number)
        {
            m_nodeStack.push(number.num);
            consumeToken();
        }

        /** F -> bin_op1 F */
        template <>
        void operator()(Factor, const lex::Op1& binop)
        {
            m_ruleStack.push(MakeUnary{operatorToUnaryFunc(binop.op)});
            m_ruleStack.push(Factor{});
            consumeToken();
        }

        /** F -> '(' E ')' */
        template <>
        void operator()(Factor, const lex::LeftParenthesis& binop)
        {
            m_ruleStack.push(lex::RightParenthesis{});
            m_ruleStack.push(Expression{});
            consumeToken();
        }

        template <>
        void operator()(lex::RightParenthesis, const lex::RightParenthesis&)
        {
            consumeToken();
        }

        template <typename T>
        void operator()(MakeUnary state, const T& anything)
        {
            auto subNode = pop(m_nodeStack);
            m_nodeStack.push(
                ast::UnaryExpr{state.op, std::make_unique<ast::Expr>(std::move(subNode))});
        }

        template <typename T>
        void operator()(MakeBinary state, const T& anything)
        {
            auto subNode1 = pop(m_nodeStack);
            auto subNode2 = pop(m_nodeStack);
            m_nodeStack.push(ast::BinaryExpr{state.op,
                                             std::make_unique<ast::Expr>(std::move(subNode2)),
                                             std::make_unique<ast::Expr>(std::move(subNode1))});
        }

    public:
        ast::Expr parse()
        {
            m_currentToken = lex::nextToken(m_is);

            m_ruleStack.push(Expression{});

            while (!m_ruleStack.empty())
            {
                auto rule = pop(m_ruleStack);
                std::visit(*this, std::move(rule), const_cast<const lex::Token&>(m_currentToken));
            }

            return pop(m_nodeStack);
        }

    private:
        void consumeToken()
        {
            m_currentToken = lex::nextToken(m_is);
        }

    private:
        lex::Token m_currentToken;
        std::istream& m_is;
        std::stack<ast::Expr> m_nodeStack;
        std::stack<Rule> m_ruleStack;
    };

} // namespace parser

namespace parser
{

    ast::Expr parse(std::istream& is)
    {
        auto parser = Parser(is);
        return parser.parse();
    }

}