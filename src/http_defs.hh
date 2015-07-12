#ifndef HTTP_DEFS_HH
#define HTTP_DEFS_HH

#include <string>
#include <iostream>
#include <map>

class HTTPDriver;

enum class HTTPMethod {
  GET, HEAD,
  POST,PUT,DELETE,
  CONNECT,OPTIONS,TRACE
};

static std::map<std::string, HTTPMethod> HTTPMethodMapping = {
  {"GET", HTTPMethod::GET},
  {"HEAD", HTTPMethod::HEAD},
  {"POST", HTTPMethod::POST},
  {"PUT", HTTPMethod::PUT},
  {"DELETE", HTTPMethod::DELETE},
  {"CONNECT", HTTPMethod::CONNECT},
  {"OPTIONS", HTTPMethod::OPTIONS},
  {"TRACE", HTTPMethod::TRACE},
};

struct HTTPStartLine {
  HTTPMethod method;
  unsigned version_minor;
  unsigned version_major;
};

#endif
