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
SP          " "
HTTP_VERSION "HTTP/1.1"
PATH         "/"
EOL         \n

%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step();
%}

{SP}            {
                  loc.step();
                  return yy::HTTPParser::make_SP(loc);
                }

{EOL}           {
                  loc.lines(yyleng); loc.step();
                  return yy::HTTPParser::make_EOL(loc);
                }

{HTTP_VERSION}  {
                  return yy::HTTPParser::make_HTTP_VERSION(
                      std::string(yytext), loc);
                }

{METHOD}        {
                  return yy::HTTPParser::make_METHOD(
                      HTTPMethodMapping[yytext], loc
                  );
                }

{PATH}          return yy::HTTPParser::make_PATH(std::string(yytext), loc);

.               driver.error(loc, "Invalid Character");

<<EOF>>         return yy::HTTPParser::make_END(loc);

%%

void HTTPDriver::scan_begin_source (const std::string& source)
{
  src = new char[source.size() + 1];
  std::copy(source.begin(), source.end(), src);
  src[source.size()] = '\0';

  yy_flex_debug = trace_scanning;
  buffer = yy_scan_string(src);
}

void HTTPDriver::scan_end_source ()
{
  yy_delete_buffer(buffer);
  delete[] src;
}


void HTTPDriver::scan_begin ()
{
  yy_flex_debug = trace_scanning;

  if (!(yyin = fopen(file.c_str(), "r"))) {
    error("Can't open " + file + ": " + strerror(errno));
    exit(EXIT_FAILURE);
  }

  buffer = yy_create_buffer(yyin, YY_BUF_SIZE);
  yy_switch_to_buffer(buffer);
}

void HTTPDriver::scan_destroy ()
{
  yylex_destroy();
}

void HTTPDriver::scan_end ()
{
  yy_flush_buffer(buffer);
  yy_delete_buffer(buffer);
  fclose(yyin);
}

