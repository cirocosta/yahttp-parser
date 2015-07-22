#include "gtest/gtest.h"
#include "yahttp/HTTP.hh"
#include <sstream>
#include <iostream>

using namespace yahttp;

TEST(Http, SimpleRequest) {
  std::ostringstream actual;
  const char* expected =
    "POST /path HTTP/1.1\r\n"
    "Content-Length: 1024\r\n"
    "\r\n"
    "hue hue brbr\r\n";

  HTTPRequestStartLine req ("HTTP/1.1", HTTPMethod::POST, "/path");


  std::string body = "hue hue brbr";
  HTTPBody data (body.begin(), body.end());

  HTTPRequestMessage req_msg (
    req,
    HTTPHeaders {{"Content-Length", "1024"}},
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
    "hue hue brbr\r\n";

  HTTPResponseStartLine res {
    "HTTP/1.1",
    200,
    "Ok"
  };

  std::string body = "hue hue brbr";
  HTTPBody data (body.begin(), body.end());

  HTTPResponseMessage res_msg (
      res,
      HTTPHeaders {{"Content-Length", "1024"}},
      data
  );

  actual << res_msg;
  EXPECT_EQ(expected, actual.str());
}

