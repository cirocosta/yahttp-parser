%{ /* -*- C++ -*- */

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>

#include "yahttp/parser/driver.hh"
#include "parser.hh"

#undef yywrap
#define yywrap() 1

// The location of the current token.
static yahttp::location loc;

%}

%option noyywrap nounput batch debug noinput
%x HEADER
%x BODY

SP                  [ \t]
RSP                 {SP}+
OWS                 {SP}*

VCHAR               [\x21-\x7E]
OCTET               [\x00-\xFF]
ALPHA               [a-zA-Z]
DIGIT               [0-9]
EOL                 ("\r\n"|"\n")
PCT_ENC             "%"[0-9A-Fa-f]{2}
SUB_DELIM           [!$&'\(\)*+,;=]
PCHAR               {ALPHA}|{DIGIT}|"-"|"."|"_"|"~"|{PCT_ENC}|{SUB_DELIM}|":"|"@"
SEGMENT             {PCHAR}+

STATUS_CODE         {DIGIT}{3}

HTTP_VERSION        "HTTP/1.1"
METHOD              ("GET"|"HEAD"|"POST"|"PUT"|"DELETE")
PATH                "/"({SEGMENT}{SEGMENT}*)?

FIELD_NAME          [a-zA-Z_\-0-9]+":"
FIELD_VALUE         {RSP}{VCHAR}+({RSP}{VCHAR})*

BODY_CONTENT        {OCTET}+

REASON_PHRASE       {ALPHA}({RSP}{PCHAR})*

%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step();
%}

{HTTP_VERSION}  return yahttp::HTTPParser::make_HTTP_VERSION(yytext, loc);

{RSP}           return yahttp::HTTPParser::make_RSP(loc);

{METHOD}        return yahttp::HTTPParser::make_METHOD(yahttp::HTTPMethodMapping.at(yytext), loc);

{PATH}          return yahttp::HTTPParser::make_PATH(std::string(yytext), loc);

{STATUS_CODE}   {
                  errno = 0;
                  long n = std::strtol(yytext, NULL, 10);

                  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
                    driver.error (loc, "integer is out of range");

                  return yahttp::HTTPParser::make_STATUS_CODE(n, loc);
                }

{EOL}           {
                  loc.lines(yyleng); loc.step();
                  return yahttp::HTTPParser::make_EOL(loc);
                }

{REASON_PHRASE} {
                  return yahttp::HTTPParser::make_REASON_PHRASE(
                    std::string(yytext),loc);
                }


<HEADER>{FIELD_VALUE}   return yahttp::HTTPParser::make_FIELD_VALUE(yytext+1, loc);

<HEADER>{FIELD_NAME}    {
                          return yahttp::HTTPParser::make_FIELD_NAME(
                              std::string(yytext, 0, yyleng-1), loc
                          );
                        }

<HEADER>{EOL}           return yahttp::HTTPParser::make_EOL(loc);

<BODY>{BODY_CONTENT}  {
                        return yahttp::HTTPParser::make_BODY_CONTENT(
                            yahttp::HTTPBody(yytext, yytext+yyleng), loc
                        );
                      }

.               driver.error(loc, "Invalid Character");

<<EOF>>         return yahttp::HTTPParser::make_END(loc);

%%

void yahttp::HTTPDriver::_BEGIN_HEADER ()
{
  if (trace_scanning)
    std::cout << "\t---- BEGINNING HEADER STATE ----\n";
  BEGIN(HEADER);
}

void yahttp::HTTPDriver::_BEGIN_BODY ()
{
  if (trace_scanning)
    std::cout << "\t---- BEGINNING BODY STATE ----\n";
  BEGIN(BODY);
}

void yahttp::HTTPDriver::scan_begin_source (const std::string& source)
{
  src = new char[source.size() + 1];
  std::copy(source.begin(), source.end(), src);
  src[source.size()] = '\0';

  yy_flex_debug = trace_scanning;
  buffer = yy_scan_string(src);
}

void yahttp::HTTPDriver::scan_end_source ()
{
  yy_delete_buffer(buffer);
  delete[] src;
}


void yahttp::HTTPDriver::scan_begin ()
{
  yy_flex_debug = trace_scanning;

  if (!(yyin = fopen(file.c_str(), "r"))) {
    error("Can't open " + file + ": " + strerror(errno));
    exit(EXIT_FAILURE);
  }

  buffer = yy_create_buffer(yyin, YY_BUF_SIZE);
  yy_switch_to_buffer(buffer);
}

void yahttp::HTTPDriver::scan_destroy ()
{
  yylex_destroy();
}

void yahttp::HTTPDriver::scan_end ()
{
  yy_flush_buffer(buffer);
  yy_delete_buffer(buffer);
  fclose(yyin);
}

