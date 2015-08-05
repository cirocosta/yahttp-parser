#include "yahttp/HTTP.hh"

namespace yahttp
{

static const std::string CRLF = "\r\n";
static const std::string SP = " ";

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPMethod& method)
{
  o << yahttp::HTTPMethodInverseMapping.at(method);

  return o;
}

std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPRequestStartLine& req)
{
  o << req.method << SP << req.path << SP << req.version;

  return o;
}

std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPResponseStartLine& res)
{
  o << res.version << SP << res.status_code << SP << res.reason_phrase;

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPHeader& header)
{
  o << header.first << ": " << header.second;

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPHeaderMap& headers)
{
  for (const auto& header : headers)
    o << header << CRLF;

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPBody& body)
{
  std::copy(body.begin(), body.end(), std::ostream_iterator<char>(o, ""));

  return o;
}

std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPResponseMessage& message)
{
  yahttp::HTTPResponseStartLine* res_sl =
      static_cast<yahttp::HTTPResponseStartLine*>(message.start_line.get());

  o << *res_sl << CRLF << message.headers << CRLF << message.body;

  return o;
}

std::ostream& operator<<(std::ostream& o,
                         const yahttp::HTTPRequestMessage& message)
{
  yahttp::HTTPRequestStartLine* req_sl =
      static_cast<yahttp::HTTPRequestStartLine*>(message.start_line.get());

  o << *req_sl << CRLF << message.headers << CRLF << message.body;

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

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPStartLinePtr& sl)
{
  if (sl->type == HTTPMessageType::Request) {
    o << *static_cast<const yahttp::HTTPRequestStartLine*>(sl.get());
  } else if (sl->type == HTTPMessageType::Response) {
    o << *static_cast<const yahttp::HTTPResponseStartLine*>(sl.get());
  } else {
    throw std::runtime_error("Unrecognized http message type.");
  }

  return o;
}

std::ostream& operator<<(std::ostream& o, const yahttp::HTTPMessagePtr& msg)
{
  if (msg->type == HTTPMessageType::Request) {
    o << *static_cast<const yahttp::HTTPRequestMessage*>(msg.get());
  } else if (msg->type == HTTPMessageType::Response) {
    o << *static_cast<const yahttp::HTTPResponseMessage*>(msg.get());
  } else {
    throw std::runtime_error("Unrecognized http message type.");
  }

  return o;
}
};
