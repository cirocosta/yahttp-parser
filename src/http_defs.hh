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

static const std::map<std::string, HTTPMethod> HTTPMethodMapping = {
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
  std::string path;
  std::string version;

  HTTPMethod method;
  unsigned status_code;
  std::string reason_phrase;
};

typedef std::map<std::string, std::string> HTTPHeaders;
typedef std::string HTTPBody;

struct HTTPMessage {
  HTTPStartLine start_line;
  HTTPHeaders headers;
  HTTPBody body;
};

#endif
