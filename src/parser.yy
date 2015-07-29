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

%define parse.trace
%define parse.error verbose

%code
{
#include "yahttp/parser/driver.hh"
#include <string>
}

%define api.token.prefix {HTTP_}

%token
  END   0   "End of File (EOF)"
  EOL
  RSP
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
%token <HTTPBody> BODY_CONTENT CHUNKED_BODY_CONTENT;

%type <HTTPMessagePtr> http_message http_top;
%type <HTTPStartLinePtr> start_line;
%type <HTTPStartLinePtr> request_line;
%type <HTTPStartLinePtr> status_line;
%type <HTTPHeader> header;
%type <HTTPHeaderMap> header_field;
%type <HTTPBody> body;

%printer { yyoutput << $$; } <*>;

%%

%start http_message;

http_message
  : http_top body {
  $1->body = $2;
  driver.message = $1;
  $$ = $1;
                  }
  ;

http_top
  : start_line EOL header_field EOL {
  HTTPMessagePtr msg (new HTTPMessage);

  msg->type = $1->type;
  msg->start_line = $1;
  msg->headers = $3;
  $$ = msg;

  HTTPHeaderMap::const_iterator it = msg->headers.find("Transfer-Encoding");

  if (it != msg->headers.end() && it->second == "chunked") {
    driver._BEGIN_CHUNKED_BODY();
  } else {
    driver._BEGIN_BODY();
  }
                                    }
  ;

body
  : %empty                    { $$ = HTTPBody {}; }
  | BODY_CONTENT              { $$ = $1; }
  | CHUNKED_BODY_CONTENT      { $$ = $1; }
  | body CHUNKED_BODY_CONTENT {
  HTTPBody body;

  body.reserve($1.size() + $2.size());
  body.insert(body.end(), $1.begin(), $1.end());
  body.insert(body.end(), $2.begin(), $2.end());
  $$ = body;
                              }
  ;

start_line
  : status_line   { $$ = $1; driver._BEGIN_HEADER(); }
  | request_line  { $$ = $1; driver._BEGIN_HEADER(); }
  ;

status_line
  : HTTP_VERSION RSP STATUS_CODE RSP REASON_PHRASE  {
  HTTPStartLinePtr sl (new HTTPResponseStartLine ($1, $3, $5));
  $$ = sl;
                                                  }
  ;

request_line
  : METHOD RSP PATH RSP HTTP_VERSION  {
  HTTPStartLinePtr sl (new HTTPRequestStartLine ($5, $1, $3));
  $$ = sl;
                                    }
  ;

header_field
  : %empty              { $$ = HTTPHeaderMap {};   }
  | header_field header {
  auto search = $1.find($2.first);

  if (search != $1.end())
    search->second += ("," + $2.second);
  else
    $1.emplace($2); $$ = $1;
                         }
  ;

header: FIELD_NAME FIELD_VALUE EOL { $$ = HTTPHeader {$1, $2}; }
      ;

%%

void yahttp::HTTPParser::error (const location_type& l, const std::string& m)
{
  driver.error(l, m);
}

