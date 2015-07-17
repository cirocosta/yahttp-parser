#include <string>

#include "gtest/gtest.h"
#include "yahttp/parser/driver.hh"

TEST(Parser, RequestWithHeadersWithURLs) {
  bool debug = false;
  std::string message = "GET /path HTTP/1.1\n";
  message += "Content-Length: 1024\n";
  message += "Location: https://facebook.com/\n";
  message += "Pragma: no-cache\n";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(!driver.message.headers.empty());
  EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1");
  EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET);
  EXPECT_TRUE(driver.message.start_line.path == "/path");
  EXPECT_TRUE(driver.message.headers["Content-Length"] == "1024");
  EXPECT_TRUE(driver.message.headers["Location"] == "https://facebook.com/");
  EXPECT_TRUE(driver.message.headers["Pragma"] == "no-cache");
}

TEST(Parser, RequestWithSimpleHeaders) {
  bool debug = false;
  std::string message = "GET /path HTTP/1.1\n";
  message += "Content-Length: 1024\n";
  message += "Host: 1111\n";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(!driver.message.headers.empty());
  EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1");
  EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET);
  EXPECT_TRUE(driver.message.start_line.path == "/path");
  EXPECT_TRUE(driver.message.headers["Content-Length"] == "1024");
  EXPECT_TRUE(driver.message.headers["Host"] == "1111");
}

TEST(Parser, RequestWithSingleHeader) {
  bool debug = false;
  HTTPDriver driver(debug, debug);
  driver.parse_source("GET /path HTTP/1.1\nContent-Length: 2448\n");

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(!driver.message.headers.empty());
  EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1");
  EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET);
  EXPECT_TRUE(driver.message.start_line.path == "/path");
  EXPECT_TRUE(driver.message.headers["Content-Length"] == "2448");
}

TEST(Parser, ResponseWithoutHeaders) {
  bool debug = false;
  HTTPDriver driver(debug, debug);
  driver.parse_source("HTTP/1.1 200 OK\n");

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(driver.message.headers.empty());
  EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1");
  EXPECT_TRUE(driver.message.start_line.status_code == 200);
  EXPECT_TRUE(driver.message.start_line.reason_phrase == "OK");
}


TEST(Parser, ResponseWithoutHeadersComplex) {
  bool debug = false;
  HTTPDriver driver(debug, debug);
  driver.parse_source("HTTP/1.1 404 Not Found\n");

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(driver.message.headers.empty());
  EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1");
  EXPECT_TRUE(driver.message.start_line.status_code == 404);
  EXPECT_TRUE(driver.message.start_line.reason_phrase == "Not Found");
}

TEST(Parser, RequestWithoutHeaders) {
  bool debug = false;
  HTTPDriver driver(debug, debug);
  driver.parse_source("GET /path HTTP/1.1\n");

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(driver.message.headers.empty());
  EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET);
  EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1");
  EXPECT_TRUE(driver.message.start_line.path == "/path");
}

TEST(Parser, RequestFromAFile) {
  bool debug = false;
  HTTPDriver driver(debug, debug);
  driver.parse("./tests/get-req.txt");

  EXPECT_TRUE(!driver.result);
  EXPECT_TRUE(driver.message.headers.empty());
  EXPECT_TRUE(driver.message.start_line.method == HTTPMethod::GET);
  EXPECT_TRUE(driver.message.start_line.version == "HTTP/1.1");
  EXPECT_TRUE(driver.message.start_line.path == "/path");
}

