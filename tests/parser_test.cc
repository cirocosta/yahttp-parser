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
  bool debug = true;
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

/* TEST(Parser, RequestWithSimpleHeaders) { */
/*   bool debug = false; */
/*   std::string message = */
/*     "GET /path HTTP/1.1\n" */
/*     "Content-Length: 1024\n" */
/*     "Host: 1111\n"; */

/*   HTTPDriver driver(debug, debug); */
/*   driver.parse_source(message); */

/*   EXPECT_TRUE(!driver.result); */
/*   EXPECT_TRUE(!driver.message.headers.empty()); */
/*   EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1"); */
/*   EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET); */
/*   EXPECT_TRUE(driver.message.start_line.path == "/path"); */
/*   EXPECT_TRUE(driver.message.headers["Content-Length"] == "1024"); */
/*   EXPECT_TRUE(driver.message.headers["Host"] == "1111"); */
/* } */

/* TEST(Parser, RequestWithSingleHeader) { */
/*   bool debug = false; */
/*   HTTPDriver driver(debug, debug); */
/*   driver.parse_source("GET /path HTTP/1.1\nContent-Length: 2448\n"); */

/*   EXPECT_TRUE(!driver.result); */
/*   EXPECT_TRUE(!driver.message.headers.empty()); */
/*   EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1"); */
/*   EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET); */
/*   EXPECT_TRUE(driver.message.start_line.path == "/path"); */
/*   EXPECT_TRUE(driver.message.headers["Content-Length"] == "2448"); */
/* } */

/* TEST(Parser, ResponseWithoutHeaders) { */
/*   bool debug = false; */
/*   HTTPDriver driver(debug, debug); */
/*   driver.parse_source("HTTP/1.1 200 OK\n"); */

/*   EXPECT_TRUE(!driver.result); */
/*   EXPECT_TRUE(driver.message.headers.empty()); */
/*   EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1"); */
/*   EXPECT_TRUE(driver.message.start_line.status_code == 200); */
/*   EXPECT_TRUE(driver.message.start_line.reason_phrase == "OK"); */
/* } */


/* TEST(Parser, ResponseWithoutHeadersComplex) { */
/*   bool debug = false; */
/*   HTTPDriver driver(debug, debug); */
/*   driver.parse_source("HTTP/1.1 404 Not Found\n"); */

/*   EXPECT_TRUE(!driver.result); */
/*   EXPECT_TRUE(driver.message.headers.empty()); */
/*   EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1"); */
/*   EXPECT_TRUE(driver.message.start_line.status_code == 404); */
/*   EXPECT_TRUE(driver.message.start_line.reason_phrase == "Not Found"); */
/* } */

/* TEST(Parser, RequestWithoutHeaders) { */
/*   bool debug = false; */
/*   HTTPDriver driver(debug, debug); */
/*   driver.parse_source("GET /path HTTP/1.1\n"); */

/*   EXPECT_TRUE(!driver.result); */
/*   EXPECT_TRUE(driver.message.headers.empty()); */
/*   EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET); */
/*   EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1"); */
/*   EXPECT_TRUE(driver.message.start_line.path == "/path"); */
/* } */

/* TEST(Parser, RequestFromAFile) { */
/*   bool debug = false; */
/*   HTTPDriver driver(debug, debug); */
/*   driver.parse("./assets/get-req.txt"); */

/*   EXPECT_TRUE(!driver.result); */
/*   EXPECT_TRUE(driver.message.headers.empty()); */
/*   EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET); */
/*   EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1"); */
/*   EXPECT_TRUE(driver.message.start_line.path == "/path"); */
/* } */

