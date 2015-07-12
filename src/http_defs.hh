#ifndef HTTP_DEFS_HH
#define HTTP_DEFS_HH

#include <string>
#include <iostream>

class HTTPDriver;

enum class HTTPMethod {
  GET, HEAD,
  POST,PUT,DELETE,
  CONNECT,OPTIONS,TRACE
};

struct HTTPStartLine {
  HTTPMethod method;
  unsigned version_minor;
  unsigned version_major;
};

#endif
