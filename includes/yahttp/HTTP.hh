#ifndef YAHTTP__HTTP_HH
#define YAHTTP__HTTP_HH

#include <string>
#include <iostream>
#include <utility>
#include <memory>
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

class HTTPStartLine {
public:
  std::string version;
protected:
  HTTPStartLine (std::string ver)
    : version(ver)
  {}
};

struct HTTPRequestStartLine : public HTTPStartLine
{
  HTTPMethod method;
  std::string path;

  HTTPRequestStartLine (std::string vsion, HTTPMethod mthd, std::string pth)
    : HTTPStartLine (vsion), method(mthd), path(pth)
  {}
};

struct HTTPResponseStartLine : public HTTPStartLine
{
  unsigned status_code;
  std::string reason_phrase;

  HTTPResponseStartLine (std::string ver, unsigned sc, std::string rp)
    : HTTPStartLine (ver), status_code(sc), reason_phrase(rp)
  {}
};

typedef std::map<std::string, std::string> HTTPHeaders;
typedef std::vector<char> HTTPBody;
typedef std::shared_ptr<HTTPStartLine> HTTPStartLinePtr;
/* std::ostream& operator<<(std::ostream& o, const HTTPStartLinePtr&); */

struct HTTPMessage
{
  HTTPMessageType type;
  HTTPStartLinePtr start_line;
  HTTPHeaders headers;
  HTTPBody body;
};

struct HTTPResponseMessage : public HTTPMessage
{
  HTTPResponseMessage (HTTPResponseStartLine sl, HTTPHeaders h,
                       HTTPBody b)
  {
    start_line = HTTPStartLinePtr(new HTTPResponseStartLine(sl));
    headers = h;
    body = b;
    type = HTTPMessageType::Response;
  }
};

struct HTTPRequestMessage : public HTTPMessage
{
  HTTPRequestMessage (HTTPRequestStartLine sl, HTTPHeaders h,
                       HTTPBody b)
  {
    start_line = HTTPStartLinePtr(new HTTPRequestStartLine(sl));
    headers = h;
    body = b;
    type = HTTPMessageType::Request;
  }
};

}; // !ns http


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

