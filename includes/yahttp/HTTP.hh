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

struct HTTPStartLine {
  std::string version;
  HTTPMessageType type;
};

struct HTTPRequestStartLine : public HTTPStartLine
{
  HTTPMethod method;
  std::string path;

  HTTPRequestStartLine (std::string ver, HTTPMethod mthd, std::string pth)
    : method(mthd), path(pth)
  {
    version = ver;
    type = HTTPMessageType::Request;
  }
};

struct HTTPResponseStartLine : public HTTPStartLine
{
  unsigned status_code;
  std::string reason_phrase;

  HTTPResponseStartLine (std::string ver, unsigned sc, std::string rp)
    : status_code(sc), reason_phrase(rp)
  {
    version = ver;
    type = HTTPMessageType::Response;
  }
};

struct HTTPHeaderMap : std::map<std::string, std::string>
{
  using std::map<std::string, std::string>::map;
};

struct HTTPHeader : std::pair<std::string, std::string>
{
  using std::pair<std::string, std::string>::pair;
};

typedef std::vector<char> HTTPBody;
typedef std::shared_ptr<HTTPStartLine> HTTPStartLinePtr;

struct HTTPMessage
{
  HTTPMessageType type;
  HTTPStartLinePtr start_line;
  HTTPHeaderMap headers;
  HTTPBody body;
};

typedef std::shared_ptr<HTTPMessage> HTTPMessagePtr;

struct HTTPResponseMessage : public HTTPMessage
{
  HTTPResponseMessage (HTTPResponseStartLine sl, HTTPHeaderMap h,
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
  HTTPRequestMessage (HTTPRequestStartLine sl, HTTPHeaderMap h,
                       HTTPBody b)
  {
    start_line = HTTPStartLinePtr(new HTTPRequestStartLine(sl));
    headers = h;
    body = b;
    type = HTTPMessageType::Request;
  }
};

std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPMethod& method);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPRequestStartLine& req);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPResponseStartLine& res);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPHeader& header);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPHeaderMap& headers);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPBody& body);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPMessage& message);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPResponseMessage& message);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPRequestMessage& message);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPStartLinePtr& sl);
std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPMessagePtr& msg);

}; // !ns http


#endif // ! YAHTTP__HTTP_HH

