#include <string>

#include "gtest/gtest.h"
#include "yahttp/parser/driver.hh"

using namespace yahttp;

TEST(Parser, RequestWithBody) {
  bool debug = false;
  const char* message =
    "GET /path HTTP/1.1\n"
    "Content-Length: 1024\n"
    "Location: https://facebook.com/\n"
    "Pragma: no-cache\n"
    "\n"
    "brbr huehue zueira never ends";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(!driver.message->headers.empty());
  EXPECT_TRUE(driver.message->start_line->version == "HTTP/1.1");

  EXPECT_EQ(driver.message->type, HTTPMessageType::Request);

  HTTPRequestStartLine* sl =
    static_cast<HTTPRequestStartLine*>(driver.message->start_line.get());

  EXPECT_TRUE(sl->method == HTTPMethod::GET);
  EXPECT_EQ(sl->path, "/path");

  EXPECT_EQ(driver.message->headers["Content-Length"], "1024");
  EXPECT_EQ(driver.message->headers["Location"], "https://facebook.com/");
  EXPECT_EQ(driver.message->headers["Pragma"], "no-cache");

  std::string body_msg (driver.message->body.begin(),
                        driver.message->body.end());

  EXPECT_EQ(body_msg, "brbr huehue zueira never ends");
}

TEST(Parser, RequestWithHeadersWithURLs) {
  bool debug = false;
  const char* message =
    "GET /path HTTP/1.1\n"
    "Content-Length: 1024\n"
    "Location: https://facebook.com/\n"
    "Pragma: no-cache\n"
    "\n";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(!driver.message->headers.empty());
  EXPECT_TRUE(driver.message->start_line->version == "HTTP/1.1");

  EXPECT_EQ(driver.message->type, HTTPMessageType::Request);

  HTTPRequestStartLine* sl =
    static_cast<HTTPRequestStartLine*>(driver.message->start_line.get());

  EXPECT_TRUE(sl->method == HTTPMethod::GET);
  EXPECT_EQ(sl->path, "/path");

  EXPECT_EQ(driver.message->headers["Content-Length"], "1024");
  EXPECT_EQ(driver.message->headers["Location"], "https://facebook.com/");
  EXPECT_EQ(driver.message->headers["Pragma"], "no-cache");
}

TEST(Parser, ResponseWithHeaders) {
  bool debug = false;
  const char* message =
    "HTTP/1.1 200 Ok\r\n"
    "Content-Length: 1024\r\n"
    "\r\n";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(!driver.message->headers.empty());
  EXPECT_TRUE(driver.message->start_line->version == "HTTP/1.1");
  EXPECT_EQ(driver.message->type, HTTPMessageType::Response);

  HTTPResponseStartLine* sl =
    static_cast<HTTPResponseStartLine*>(driver.message->start_line.get());

  EXPECT_EQ(sl->status_code, 200);
  EXPECT_EQ(sl->reason_phrase, "Ok");

  EXPECT_EQ(driver.message->headers["Content-Length"], "1024");
}

TEST(Parser, ResponseWithBody) {
  bool debug = false;
  const char* message =
    "HTTP/1.1 200 Ok\r\n"
    "Content-Length: 1024\r\n"
    "\r\n"
    "huehue brbr\n"
    "\t\tzueira never ends";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(!driver.message->headers.empty());
  EXPECT_TRUE(driver.message->start_line->version == "HTTP/1.1");
  EXPECT_EQ(driver.message->type, HTTPMessageType::Response);

  HTTPResponseStartLine* sl =
    static_cast<HTTPResponseStartLine*>(driver.message->start_line.get());

  EXPECT_EQ(sl->status_code, 200);
  EXPECT_EQ(sl->reason_phrase, "Ok");

  EXPECT_EQ(driver.message->headers["Content-Length"], "1024");

  std::string body_msg (driver.message->body.begin(),
                        driver.message->body.end());

  EXPECT_EQ(body_msg, "huehue brbr\n\t\tzueira never ends");
}

