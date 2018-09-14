#include "Lexer.h"

#include <cctype>

namespace lex
{

    Token nextToken(std::istream& is)
    {
        int c = is.peek();

        if (c == std::char_traits<char>::eof())
        {
            return nullptr;
        }

        // ignore all whitespaces
        for (; std::isspace(c); c = is.peek())
        {
            is.get();
        }

        // parser digit
        if (isdigit(c) || c == '.')
        {
            std::string numStr;
            do
            {
                numStr += c;
                is.get();
                c = is.peek();
            } while (isdigit(c) || c == '.');

            return Number{std::strtod(numStr.c_str(), nullptr)};
        }

        if (c == '(')
        {
            is.get();
            return LeftParenthesis{};
        }

        if (c == ')')
        {
            is.get();
            return RightParenthesis{};
        }

        // operator with lower precedence
        if (c == '+' || c == '-')
        {
            is.get();
            return Op1{static_cast<char>(c)};
        }

        // operator with higher precedence
        if (c == '*' || c == '/')
        {
            is.get();
            return Op2{static_cast<char>(c)};
        }

        throw std::runtime_error("Unexpected token");
    }

} // namespace lex