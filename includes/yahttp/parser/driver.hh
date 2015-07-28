#ifndef HTTPDRIVER_HH
#define HTTPDRIVER_HH

#include <string>
#include <map>
#include <memory>

#include "parser.hh"
#include "yahttp/HTTP.hh"

#define YY_DECL \
  yahttp::HTTPParser::symbol_type yylex (yahttp::HTTPDriver& driver)

YY_DECL;

namespace yahttp {

typedef struct yy_buffer_state * YY_BUFFER_STATE;

/**
 * Public Interface to the HTTP Parser
 */
class HTTPDriver
{
public:
  HTTPMessagePtr message;
  int result;

  std::string file;
  YY_BUFFER_STATE buffer;
  char* src;

  bool trace_scanning = false;
  bool trace_parsing = false;
  bool multi_parsing = false;

public:
  HTTPDriver();
  HTTPDriver(bool ts = false, bool tp = false, bool mp = false);
  virtual ~HTTPDriver();

public:
  void parse(const std::string& file);
  void parse_source(const std::string& source);
  /* void parse_multi(const std::string& source); */
  /* void parse_multi_end(); */

  void scan_begin();
  void scan_begin_source(const std::string& source);
  void scan_end();
  void scan_end_source();
  void scan_destroy();

  void error(const yahttp::location& l, const std::string& m);
  void error(const std::string& m);

  void _BEGIN_HEADER ();
  void _BEGIN_BODY ();
};

}; // ! ns yahttp

#endif

