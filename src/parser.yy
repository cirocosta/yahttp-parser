%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"

%defines
%define api.namespace {yahttp}
%define parser_class_name {HTTPParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include "yahttp/HTTP.hh"
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
#include "yahttp/parser/driver.hh"
#include <string>
}

%define api.token.prefix {HTTP_}

%token
  END 0 "End of File (EOF)"
  COLON
  EOL
  SP
  OWS
;

%token <int> STATUS_CODE

%token <std::string>
  PATH
  HTTP_VERSION
  REASON_PHRASE
  FIELD_NAME
  FIELD_VALUE
;

%token <HTTPMethod> METHOD;


%type <std::string> http_message;
%type <std::string> start_line;
%type <std::string> request_line;
%type <std::string> status_line;
%type <std::string> reason_phrase;
%type <std::string> header_field;
%type <std::string> header;


%%
%start http_message;

http_message: start_line EOL header_field { }
            ;

start_line: status_line      {  }
          | request_line     {  }
          ;

status_line:  HTTP_VERSION SP
              STATUS_CODE SP
              reason_phrase   {

                              }
           ;

reason_phrase:  %empty          {  }
             |  REASON_PHRASE   { }
             |  reason_phrase SP REASON_PHRASE { }
             ;

request_line: METHOD SP
              PATH SP
              HTTP_VERSION  { }
            ;

header_field: %empty              { }
            | header header_field { }
            ;

header: FIELD_NAME ":" SP FIELD_VALUE EOL { }
      ;

%%

void yahttp::HTTPParser::error (const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

