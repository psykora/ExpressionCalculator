# ExpressionCalculator

This is and experiment to write a simple LL(1) parser without parsing table, but with 
set of rules implemented using *std::variant* and visitor concept.

The set of terminals are defined in *Lexer.h* and the simplistic lexer is implemented in *Lexer.cpp*
The rules for [LL(1)](https://en.wikipedia.org/wiki/LL_parser) parser are defined in *Parser.cpp*

EBNF Grammar is as below:
```
     E -> T {op1 T}*
     T -> F {op2 F}*
     F -> number | op1 F | '(' E ')'
```
This is further converted to the following BNF LL(1) grammar
```
     E  -> T E'
     E' -> $ | bin_op1 T E'
     T  -> F T'
     T' -> $ | bin_op2 F T'
     F  -> number | bin_op1 F | '(' E ')'
```
## References
 - [Sum types and state machines in C++17](http://mooooo.ooo/sumtypes-and-statemachines/)
 - [LLVM Kaleidoscope: Implementing a Parser and AST](https://llvm.org/docs/tutorial/LangImpl02.html)

## Status

Branch / Compiler |  MSVC 2017  | 
------------------| ------------|
master | [![Build status](https://ci.appveyor.com/api/projects/status/59aogvt8lisp9mt0?svg=true)](https://ci.appveyor.com/project/psykora/expressioncalculator) |
