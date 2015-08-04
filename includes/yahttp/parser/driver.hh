#ifndef YAHTTP__DRIVER_HH
#define YAHTTP__DRIVER_HH

#include <string>
#include <map>
#include <sstream>
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
  bool trace_scanning = false;
  bool trace_parsing = false;
  bool multi_parsing = false;

public:
  HTTPDriver();
  HTTPDriver(bool ts = false, bool tp = false, bool mp = false);
  ~HTTPDriver();

public:
  void parse(std::string& source);
  void parse(std::stringstream& source);
  void scan_begin(std::stringstream& source) const;
  void scan_end() const;
  void scan_destroy() const;

  void error(const yahttp::location& l, const std::string& m);
  void error(const std::string& m);

  void _BEGIN_HEADER ();
  void _BEGIN_BODY ();
  void _BEGIN_CHUNKED_BODY ();
};

}; // ! ns yahttp

#endif

