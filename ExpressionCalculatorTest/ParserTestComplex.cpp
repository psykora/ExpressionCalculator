#include "Parser.h"
#include "Printer.h"

#include "gtest/gtest.h"

#include <sstream>

void compareParsed(const std::string& src, const std::string& structure)
{
    std::istringstream is(src);
    std::ostringstream os;
    auto result = parser::parse(is);
    ast::print(result, os);
    EXPECT_EQ(structure, os.str());
}

TEST(ParserTestComplex, parseOperatorPriority)
{
    compareParsed("3 + 2 * 5", "(3+(2*5))");
    compareParsed("3 + (2 * 5)", "(3+(2*5))");
    compareParsed("(3 + (2 * 5))", "(3+(2*5))");

    compareParsed("(3 + 2) * 5", "((3+2)*5)");

    compareParsed("3 * 2 + 5 / 8 + 4", "(((3*2)+(5/8))+4)");
    compareParsed("3 * ((2 + 5) / 8 + 4)", "(3*(((2+5)/8)+4))");
}
