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
%token <std::string> PATH HTTP_VERSION REASON_PHRASE
%token <int> STATUS_CODE

%type <HTTPStartLine> start_line;
%type <std::string> reason_phrase;


%%
%start http_message;

http_message: start_line EOL {}
            | %empty
            ;

start_line: status_line   {}
          | request_line  {}
          ;

status_line:  HTTP_VERSION SP
              STATUS_CODE SP
              reason_phrase   {
                                driver.message.start_line.status_code = $3;
                                driver.message.start_line.version = "1.1";
                              }
           ;

reason_phrase:  %empty          { $$ = ""; }
             |  REASON_PHRASE   {
                  $$ = $1;
                  driver.message.start_line.reason_phrase += $1;
                }
             |  reason_phrase SP REASON_PHRASE {
                  $$ = " " + $3;
                  driver.message.start_line.reason_phrase += $$;
                }
             ;

request_line: METHOD SP
              PATH SP
              HTTP_VERSION  {
                              driver.message.start_line.method = $1;
                              driver.message.start_line.path = $3;
                              driver.message.start_line.version = "1.1";
                            }
            ;

%%

void yy::HTTPParser::error (const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

