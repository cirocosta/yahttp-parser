#include "yahttp/HTTP.hh"

/**
 * For debugging purposes, properly defines output
 * streams.
 */

using namespace yahttp;

static const std::string CRLF = "\r\n";
static const std::string SP = " ";

std::ostream& operator<<(std::ostream& o, const HTTPMethod& method)
{
  o << HTTPMethodInverseMapping.at(method);

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPRequestStartLine& req)
{
  o << req.method << SP
    << req.path << SP
    << req.version;

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPResponseStartLine& res)
{
  o << res.version << SP
    << res.status_code << SP
    << res.reason_phrase;

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPHeaders& headers)
{
  for (const auto& header : headers)
    o << header.first << ": " << header.second << CRLF;

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPBody& body)
{
  std::copy(body.begin(), body.end(),
            std::ostream_iterator<char>(o, ""));

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPResponseMessage& message)
{
  o << message.start_line << CRLF
    << message.headers << CRLF
    << message.body << CRLF;

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPRequestMessage& message)
{
  o << message.start_line << CRLF
    << message.headers << CRLF
    << message.body << CRLF;

  return o;
}

