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

%type <HTTPMessagePtr> http_message;
%type <HTTPStartLinePtr> start_line;
%type <HTTPStartLinePtr> request_line;
%type <HTTPStartLinePtr> status_line;
%type <std::string> reason_phrase;
%type <HTTPHeader> header;
%type <HTTPHeaderMap> header_field;

%%
%start http_message;

http_message
  : start_line EOL header_field  {
  HTTPMessagePtr msg (new HTTPMessage);

  msg->type = $1->type;
  msg->start_line = $1;
  msg->headers = $3;

  driver.message = msg;
  $$ = driver.message;
                                  }
  ;

start_line
  : status_line   { $$ = $1; }
  | request_line  { $$ = $1; }
  ;

status_line
  : HTTP_VERSION SP STATUS_CODE SP reason_phrase  {
  HTTPStartLinePtr sl (new HTTPResponseStartLine ($1, $3, $5));
  $$ = sl;
                                                  }
  ;

reason_phrase
  : %empty                          { $$ = "";  }
  | REASON_PHRASE                   { $$ = $1;  }
  | reason_phrase SP REASON_PHRASE  { $$ = $1 + $3;  }
  ;

request_line
  : METHOD SP PATH SP HTTP_VERSION  {
  HTTPStartLinePtr sl (new HTTPRequestStartLine ($5, $1, $3));
  $$ = sl;
                                    }
  ;

header_field
  : %empty              { $$ = HTTPHeaderMap {}; }
  | header_field header { $1.emplace($2); $$ = $1; }
  ;

header: FIELD_NAME ":" SP FIELD_VALUE EOL { $$ = HTTPHeader {$1, $4}; }
      ;

%%

void yahttp::HTTPParser::error (const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

