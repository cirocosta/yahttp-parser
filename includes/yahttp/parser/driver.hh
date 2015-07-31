#ifndef HTTPDRIVER_HH
#define HTTPDRIVER_HH

#include <string>
#include <map>
#include <memory>

#include "yahttp_parser.hh"
#include "yahttp/HTTP.hh"


namespace yahttp {

typedef struct yy_buffer_state * YY_BUFFER_STATE;

/**
 * Public Interface to the HTTP Parser
 */
class HTTPDriver
{
public:
  // results
  HTTPMessagePtr message;
  int result;

  // ptrs
  std::shared_ptr<HTTPParser> parser = nullptr;
  YY_BUFFER_STATE buffer = nullptr;

  // debugging purposes
  std::string file;
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
  void parse_multi_begin();
  void parse_multi_push(const std::string& source);
  void parse_multi_end();

  void scan_begin();
  void scan_begin_source(const std::string& source);
  void scan_end();
  void scan_end_source();
  void scan_destroy();

  void error(const yahttp::location& l, const std::string& m);
  void error(const std::string& m);

  void _BEGIN_HEADER ();
  void _BEGIN_BODY ();
  void _BEGIN_CHUNKED_BODY ();
};

}; // ! ns yahttp

#endif

