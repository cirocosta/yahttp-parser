#ifndef HTTPDRIVER_HH
#define HTTPDRIVER_HH

#include <string>
#include <map>
#include "parser.hh"
#include "http_defs.hh"

#define YY_DECL \
  yy::HTTPParser::symbol_type yylex (HTTPDriver& driver)

YY_DECL;

typedef struct yy_buffer_state * YY_BUFFER_STATE;

/**
 * Public Interface to the HTTP Parser
 */
class HTTPDriver
{
public:
  HTTPMessage message;

  bool trace_scanning;
  std::string file;
  bool trace_parsing;
  int result;
  YY_BUFFER_STATE buffer;
  char* src;

public:
  HTTPDriver();
  HTTPDriver(bool ts, bool tp);
  virtual ~HTTPDriver();

public:
  void parse(const std::string& file);
  void parse_source(const std::string& file);

  void scan_begin();
  void scan_begin_source(const std::string& source);
  void scan_end();
  void scan_end_source();
  void scan_destroy();

  void error(const yy::location& l, const std::string& m);
  void error(const std::string& m);
};

#endif
