#include "AST.h"
#include "Evaluator.h"
#include "Parser.h"
#include "Printer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * Interactive expression calculator
 */
int main(int argc, const char* argv[])
{
    bool quietMode = false;
    if (argc > 1 && std::string("--quiet") == argv[0])
    {
        quietMode = true;
    }

    std::cout << "==== Expression calculator ====" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter an expression (e.g. '5 * (3.2 + 4)') and press enter" << std::endl;
    std::cout << std::endl;
    std::cout << "> ";

    for (std::string line; std::getline(std::cin, line);)
    {
        if (line == "exit")
        {
            break;
        }

        try
        {
            std::istringstream is(line);
            auto ast = parser::parse(is);

            if (!quietMode)
            {
                ast::print(ast, std::cout);
                std::cout << " = ";
            }
            std::cout << ast::evaluate(ast) << std::endl;
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << "Error processing input: " << e.what() << std::endl;
        }
        
        std::cout << std::endl;
        std::cout << "> ";
    }

    return 0;
}
