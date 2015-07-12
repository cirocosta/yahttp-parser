#ifndef HTTPDRIVER_HH
#define HTTPDRIVER_HH

#include <string>
#include <map>
#include "parser.hh"
#include "http_defs.hh"

#define YY_DECL \
  yy::HTTPParser::symbol_type yylex (HTTPDriver& driver)

YY_DECL;

/**
 * Public Interface to the HTTP Parser
 */
class HTTPDriver
{
public:
  std::map<std::string, std::string> headers;
  HTTPStartLine start_line;

  bool trace_scanning;
  std::string file;
  bool trace_parsing;
  int result;

public:
  HTTPDriver();
  virtual ~HTTPDriver();

public:
  void parse(const std::string& file);

  void scan_begin();
  void scan_end();

  void error(const yy::location& l, const std::string& m);
  void error(const std::string& m);
};

#endif
