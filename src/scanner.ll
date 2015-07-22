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

ALPHA               [\x41-\x5A\x61-\x7A]
BIT                 [01]
CHAR                [\x01-\x7F]
DIGIT               [0-9]
DQUOTE              \x22
CR                  \x0D
LF                  \x0A
CRLF                {CR}{LF}
SP                  \x20
HTAB                \x09
OCTET               [\x00-\xFF]
VCHAR               [\x21-\x7E]
WSP                 ({SP}|{HTAB})
OWS                 {WSP}*
RWS                 {WSP}+
EOL                 \n
TCHAR               ("!"|"#"|"$"|"%"|"_"|"+"|"-"|{DIGIT}|{ALPHA})

HTTP_VERSION        "HTTP/1.1"
METHOD              ("GET"|"HEAD"|"POST"|"PUT"|"DELETE")
PATH                "/path"
STATUS_CODE         ({DIGIT}){3}
REASON_PHRASE       ({ALPHA})+

FIELD_NAME          ({TCHAR})+
FIELD_VALUE         ({ALPHA}|{DIGIT})({ALPHA}|{DIGIT}|"://"|"."|"/")*

%{
  // Code run each time a pattern is matched.
  #define YY_USER_ACTION  loc.columns(yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step();
%}

":"             return yahttp::HTTPParser::make_COLON(loc);

{METHOD}        {
                  return yahttp::HTTPParser::make_METHOD(
                      yahttp::HTTPMethodMapping.at(yytext), loc
                  );
                }

{HTTP_VERSION}  {
                  return yahttp::HTTPParser::make_HTTP_VERSION(
                      "HTTP/1.1", loc);
                }

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

{SP}|{HTAB}     loc.step(); return yahttp::HTTPParser::make_SP(loc);

{OWS}           loc.step(); return yahttp::HTTPParser::make_OWS(loc);

{REASON_PHRASE} {
                  return yahttp::HTTPParser::make_REASON_PHRASE(
                    std::string(yytext),loc);
                }


{FIELD_VALUE}   return yahttp::HTTPParser::make_FIELD_VALUE(std::string(yytext), loc);

{FIELD_NAME}    return yahttp::HTTPParser::make_FIELD_NAME(std::string(yytext), loc);

.               driver.error(loc, "Invalid Character");

<<EOF>>         return yahttp::HTTPParser::make_END(loc);

%%

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

