%{ /* -*- C++ -*- */

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include "driver.hh"
#include "parser.hh"

#undef yywrap
#define yywrap() 1

// The location of the current token.
static yy::location loc;

%}

%option noyywrap nounput batch debug noinput

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t]

%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step();
%}

{blank}+   loc.step ();
[\n]+      loc.lines (yyleng); loc.step ();
"-"        return yy::HTTPParser::make_MINUS(loc);
"+"        return yy::HTTPParser::make_PLUS(loc);
"*"        return yy::HTTPParser::make_STAR(loc);
"/"        return yy::HTTPParser::make_SLASH(loc);
"("        return yy::HTTPParser::make_LPAREN(loc);
")"        return yy::HTTPParser::make_RPAREN(loc);
":="       return yy::HTTPParser::make_ASSIGN(loc);


{int}      {
  errno = 0;
  long n = strtol (yytext, NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    driver.error(loc, "integer is out of range");
  return yy::HTTPParser::make_NUMBER(n, loc);
}

{id}       return yy::HTTPParser::make_IDENTIFIER(yytext, loc);
.          driver.error(loc, "invalid character");
<<EOF>>    return yy::HTTPParser::make_END(loc);

%%

void
HTTPDriver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r"))) {
    error("cannot open " + file + ": " + strerror(errno));
    exit(EXIT_FAILURE);
  }
}


void
HTTPDriver::scan_end ()
{
  fclose(yyin);
}

