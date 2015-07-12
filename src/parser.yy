%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"

%defines
%define parser_class_name {HTTPParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include "http_defs.hh"
}

// passing the parsing context
%param { HTTPDriver& driver }

%locations
%initial-action
{
  // Initialize the initial location
  @$.begin.filename = @$.end.filename = &driver.file;
};

%define parse.trace
%define parse.error verbose

%code
{
#include "driver.hh"
}

%define api.token.prefix {HTTP_}

%token END 0 "End of File (EOF)"
%token EOL SP
%token <HTTPMethod> METHOD
%token <std::string> PATH HTTP_VERSION

%type <HTTPStartLine> start_line;


%%
%start http_message;

http_message: start_line EOL {}
            | %empty
            ;

start_line: METHOD SP
            PATH SP
            HTTP_VERSION {
                            driver.start_line.method = $1;
                            driver.start_line.version_major = 1;
                            driver.start_line.version_minor = 1;
                          }
          ;
%%

void yy::HTTPParser::error (const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

