#include "gtest/gtest.h"
#include "yahttp/HTTP.hh"
#include <sstream>
#include <iostream>

using namespace yahttp;

TEST(Http, HighLevelRequest) {
  std::ostringstream actual;
  const char* expected =
    "POST /path HTTP/1.1\r\n"
    "Content-Length: 1024\r\n"
    "\r\n"
    "hue hue brbr";

  std::string bmsg = "hue hue brbr";

  HTTPMessage msg;
  HTTPBody body (bmsg.begin(), bmsg.end());
  HTTPHeaderMap headers;

  headers["Content-Length"] = "1024";

  HTTPStartLinePtr sl (
    new HTTPRequestStartLine( "HTTP/1.1", HTTPMethod::POST, "/path")
  );

  msg.start_line = sl;
  msg.headers = headers;
  msg.body = body;
  msg.type = HTTPMessageType::Request;

  actual << msg;
  EXPECT_EQ(expected, actual.str());
}

TEST(Http, RequestWithoutBody) {
  std::ostringstream actual;
  const char* expected =
    "GET /path HTTP/1.1\r\n"
    "Host: localhost:8080\r\n"
    "\r\n";

  HTTPRequestStartLine req ("HTTP/1.1", HTTPMethod::GET, "/path");


  HTTPRequestMessage req_msg (
    req,
    HTTPHeaderMap {{"Host", "localhost:8080"}},
    HTTPBody {}
  );

  actual << req_msg;
  EXPECT_EQ(expected, actual.str());
}

TEST(Http, SimpleRequest) {
  std::ostringstream actual;
  const char* expected =
    "POST /path HTTP/1.1\r\n"
    "Content-Length: 1024\r\n"
    "\r\n"
    "hue hue brbr";

  HTTPRequestStartLine req ("HTTP/1.1", HTTPMethod::POST, "/path");


  std::string body = "hue hue brbr";
  HTTPBody data (body.begin(), body.end());

  HTTPRequestMessage req_msg (
    req,
    HTTPHeaderMap {{"Content-Length", "1024"}},
    data
  );

  actual << req_msg;
  EXPECT_EQ(expected, actual.str());
}

TEST(Http, SimpleResponse) {
  std::ostringstream actual;
  const char* expected =
    "HTTP/1.1 200 Ok\r\n"
    "Content-Length: 1024\r\n"
    "\r\n"
    "hue hue brbr";

  HTTPResponseStartLine res {
    "HTTP/1.1",
    200,
    "Ok"
  };

  std::string body = "hue hue brbr";
  HTTPBody data (body.begin(), body.end());

  HTTPResponseMessage res_msg (
      res,
      HTTPHeaderMap {{"Content-Length", "1024"}},
      data
  );

  actual << res_msg;
  EXPECT_EQ(expected, actual.str());
}

