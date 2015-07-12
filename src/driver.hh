#ifndef HTTPDRIVER_HH
#define HTTPDRIVER_HH

#include <string>
#include <map>
#include "parser.hh"
#include "http_defs.hh"

#define YY_DECL \
  yy::HTTPParser::symbol_type yylex (HTTPDriver& driver)

YY_DECL;


class HTTPDriver
{
public:
  HTTPDriver();
  virtual ~HTTPDriver();

  std::map<std::string, std::string> headers;
  HTTPStartLine start_line;

  int result;

  void scan_begin();
  void scan_end();
  bool trace_scanning;

  int parse(const std::string& file);
  std::string file;
  bool trace_parsing;

  void error(const yy::location& l, const std::string& m);
  void error(const std::string& m);
};

#endif
