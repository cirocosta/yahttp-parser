#ifndef YAHTTP__DRIVER_HH
#define YAHTTP__DRIVER_HH

#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#include "yahttp_parser.hh"
#include "yahttp/HTTP.hh"

namespace yahttp
{

/**
 * Public Interface to the HTTP Parser
 */
class HTTPDriver
{
public:
  // results
  HTTPMessagePtr message;
  int result;

  // debugging purposes
  bool trace_scanning = false;
  bool trace_parsing = false;
  bool multi_parsing = false;

public:
  HTTPDriver();
  HTTPDriver(bool ts = false, bool tp = false, bool mp = false);
  ~HTTPDriver();

public:
  void parse(const char* source);
  void parse(const char* source, const size_t len);
  void parse(std::stringstream& buf);
  void parse(std::ifstream& buf);
  void scan_begin(std::istream* source) const;
  void scan_destroy() const;
  void scan_end() const;

  void error(const yahttp::location& l, const std::string& m);
  void error(const std::string& m);

  void _BEGIN_HEADER();
  void _BEGIN_BODY();
  void _BEGIN_CHUNKED_BODY();
};

}; // ! ns yahttp

#endif
