#ifndef YAHTTP__HTTP_HH
#define YAHTTP__HTTP_HH

#include <string>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <iterator>

namespace yahttp {

class HTTPDriver;

enum class HTTPMethod : unsigned char {
  GET, HEAD,
  POST,PUT,DELETE,
  CONNECT,OPTIONS,TRACE
};

enum class HTTPMessageType : unsigned char {
  Response, Request
};

static const std::map<std::string, HTTPMethod> HTTPMethodMapping = {
  {"GET",     HTTPMethod::GET},
  {"HEAD",    HTTPMethod::HEAD},
  {"POST",    HTTPMethod::POST},
  {"PUT",     HTTPMethod::PUT},
  {"DELETE",  HTTPMethod::DELETE},
  {"CONNECT", HTTPMethod::CONNECT},
  {"OPTIONS", HTTPMethod::OPTIONS},
  {"TRACE",   HTTPMethod::TRACE},
};

static const std::map<HTTPMethod, std::string> HTTPMethodInverseMapping = {
  {HTTPMethod::CONNECT, "CONNECT"},
  {HTTPMethod::DELETE,  "DELETE"},
  {HTTPMethod::PUT,     "PUT"},
  {HTTPMethod::POST,    "POST"},
  {HTTPMethod::HEAD,    "HEAD"},
  {HTTPMethod::GET,     "GET"},
  {HTTPMethod::TRACE,   "TRACE"},
  {HTTPMethod::OPTIONS, "OPTIONS"},
};

struct HTTPRequestStartLine
{
  const HTTPMethod method;
  const std::string path;
  const std::string version;
};

struct HTTPResponseStartLine
{
  const std::string version;
  const unsigned status_code;
  const std::string reason_phrase;
};

typedef std::map<std::string, std::string> HTTPHeaders;
typedef std::vector<char> HTTPBody;


class HTTPMessage
{
public:
  const HTTPHeaders headers;
  const HTTPBody body;
protected:
  HTTPMessage(HTTPHeaders h, HTTPBody b)
    : headers(h), body(b)
  {}
};

struct HTTPResponseMessage : public HTTPMessage
{
  const HTTPResponseStartLine start_line;

  HTTPResponseMessage (HTTPResponseStartLine sl, HTTPHeaders h,
                       HTTPBody b)
    : HTTPMessage(h, b), start_line(sl)
  {}
};

struct HTTPRequestMessage : public HTTPMessage
{
  const HTTPRequestStartLine start_line;

  HTTPRequestMessage (HTTPRequestStartLine sl, HTTPHeaders h,
                       HTTPBody b)
    : HTTPMessage(h, b), start_line(sl)
  {}
};

}; // !ns http

using namespace yahttp;

std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPMethod& method);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPRequestStartLine& req);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPResponseStartLine& res);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPHeaders& headers);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPBody& body);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPResponseMessage& message);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPRequestMessage& message);

#endif // ! YAHTTP__HTTP_HH

