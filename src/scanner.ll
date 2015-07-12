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

METHOD      "GET"|"HEAD"|"POST"|"PUT"|"DELETE"|"CONNECT"|"OPTIONS"|"TRACE"
SP          [ ]
HTTPversion "HTTP/1.1"
END         "\n"
ALPHA       [a-zA-Z\\]+

%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step();
%}

{SP}           loc.step ();
EOL            loc.lines (yyleng); loc.step (); return yy::HTTPParser::make_EOL(loc);
{HTTPversion}  return yy::HTTPParser::make_DIGIT(1, loc);
{METHOD}       return yy::HTTPParser::make_METHOD(HTTPMethod::GET, loc);

.          driver.error(loc, "invalid character");
<<EOF>>    return yy::HTTPParser::make_EOL(loc);

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

