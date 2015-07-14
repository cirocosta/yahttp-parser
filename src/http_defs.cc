#include "http_defs.hh"

/**
 * For debugging purposes
 */

std::ostream& operator<<(std::ostream& o, const HTTPMethod method)
{
  o << HTTPMethodInverseMapping.at(method);

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPStartLine& start_line)
{
  o << "path: " << start_line.path << std::endl
    << "version: " << start_line.version << std::endl

    << "method: " << start_line.method << std::endl
    << "status: " << start_line.status_code << std::endl
    << "reason_phrase: " << start_line.reason_phrase << std::endl;

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPHeaders& headers)
{
  for (const auto& header : headers)
    o << header.first << ": " << header.second << std::endl;

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPBody& body)
{
  o << body;

  return o;
}

std::ostream& operator<<(std::ostream& o, const HTTPMessage& message)
{

  o << message.start_line << std::endl
    << message.headers << std::endl
    << message.body << std::endl;

  return o;
}
