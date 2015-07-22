#include "yahttp/HTTP.hh"


static const std::string CRLF = "\r\n";
static const std::string SP = " ";

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPMethod& method)
{
  o << yahttp::HTTPMethodInverseMapping.at(method);

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPRequestStartLine& req)
{
  o << req.method << SP
    << req.path << SP
    << req.version;

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPResponseStartLine& res)
{
  o << res.version << SP
    << res.status_code << SP
    << res.reason_phrase;

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPHeaders& headers)
{
  for (const auto& header : headers)
    o << header.first << ": " << header.second << CRLF;

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPBody& body)
{
  std::copy(body.begin(), body.end(),
            std::ostream_iterator<char>(o, ""));

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPResponseMessage& message)
{
  yahttp::HTTPResponseStartLine* res_sl =
    static_cast<yahttp::HTTPResponseStartLine*>(message.start_line.get());

  o << *res_sl << CRLF
    << message.headers << CRLF
    << message.body << CRLF;

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPRequestMessage& message)
{
  yahttp::HTTPRequestStartLine* req_sl =
    static_cast<yahttp::HTTPRequestStartLine*>(message.start_line.get());

  o << *req_sl << CRLF
    << message.headers << CRLF
    << message.body << CRLF;

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPMessage& message)
{
  if (message.type == yahttp::HTTPMessageType::Request) {
    o << *static_cast<const yahttp::HTTPRequestMessage*>(&message);
  } else if (message.type == yahttp::HTTPMessageType::Response) {
    o << *static_cast<const yahttp::HTTPResponseMessage*>(&message);
  } else {
    throw std::runtime_error("Unrecognized http message type.");
  }

  return o;
}

