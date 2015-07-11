# yahttparser

> A naive C++ HTTP parser implementation using Bison and Flex

## Install

This project is not using CMake at the moment (but it will) so make sure by yourself that you have all the dependencies installed:

- flex
- bison\*
- make
- a modern c++ compiler - targetting c++11 (recommend clang, 3.5)

Then, simply:

```sh
$ cd src
$ make
```

\*: If you've built `bison` from source and in the `make` step it claims that there's a problem with `m4`, try setting the `pkgdata_dir`:

```
export BISON_PKGDATADIR=/usr/local/share/bison/data
```


## Structure

- Lexer
    - `FlexLexer.h` : defined by Flex distribution. Contains the abstract Lexer class that lexical scanners inherit from.
    - `scanner.ll`  : flex source for the lexical scanner
    - `scanner.cc`  : generated by Flex from `scanner.ll`
        - implements the main lexer function `yylex()`. This function is reponsible for returning the next token for the parser. Such method is implemented in the `yyFlexLexer` class (which derives from `FlexLexer`), which is declared in `FlexLexer.h`.
    - `scanner.h`   :  defines the lexer class `example::Scanner`

- Parser
    - `parser.yy` : bison parser grammar
    - `parser.cc` : generated parser
    - `parser.h`  : generated from parser grammar
    - `yy.tab.h`  : forwards to parser.h. Contains nothing

- Utils
    - `location.hh`
    - `position.hh`
    - `stack.hh`

- Driver
    - `driver.h`  : definition of Driver
    - `driver.cc` : implements the driver, putting together the lexer and parser

Scanner, parser and Driver classes are located within a namespace.

