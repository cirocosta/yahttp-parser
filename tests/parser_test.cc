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

TEST(Parser, RequestCollidingHeaders) {
  bool debug = false;
  const char* message =
    "GET /path HTTP/1.1\n"
    "Content-Length: 1024\n"
    "Connection: keep-alive\n"
    "Connection: Transfer-Encoding\n"
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
  EXPECT_EQ(driver.message->headers["Connection"], "keep-alive,Transfer-Encoding");
  EXPECT_EQ(driver.message->headers["Pragma"], "no-cache");
}

TEST(Parser, MultipleInputsParse) {
  bool debug = false;
  HTTPDriver driver(debug, debug, true);

  const char* message1 =
    "GET /path HTTP/1.1\n"
    "Content-Length: 1024\n";

  const char* message2 =
    "Location: https://facebook.com/\n"
    "Pragma: no-cache\n"
    "\n"
    "brbr huehue zueira never ends";

  driver.parse_multi_begin();
  driver.parse_multi_push(message1);
  driver.parse_multi_push(message2);
  driver.parse_multi_end();

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

TEST(Parser, ChunkEncoded) {
  bool debug = false;
  const char* message =
    "HTTP/1.1 200 funky chunky!\r\n"
    "Server: fakeit/0.9 fakeitbad/1.0\r\n"
    "Transfer-Encoding:   chunked  \r\n"
    "Trailer: chunky-trailer\r\n"
    "Connection: mooo\r\n"
    "\r\n"
    "40\r\n"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n\r\n"
    "30\r\n"
    "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\r\n"
    "000\r\n"
    "\r\n";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  ASSERT_EQ(driver.result, 0);
  ASSERT_EQ(driver.message->headers.empty(), false);
  ASSERT_EQ(driver.message->headers["Transfer-Encoding"], "chunked");

  std::string body_msg (driver.message->body.begin(),
                        driver.message->body.end());
  const char* expected_body =
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"
    "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";

  EXPECT_EQ(body_msg, expected_body);
}

