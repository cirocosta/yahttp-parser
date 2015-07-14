#include <iostream>
#include <cassert>
#include <string>
#include <cstring>

#include "../driver.hh"

void test_1(bool);
void test_2(bool);
void test_3(bool);
void test_4(bool);
void test_5(bool);
void test_6(bool);
void test_7(bool);

int main()
{
  test_1(false);
  test_2(false);
  test_3(false);
  test_4(false);
  test_5(false);
  test_6(true);
  test_7(true);

  printf("SUCCESS!\n");

  exit(EXIT_SUCCESS);
}

void test_7 (bool debug)
{
  std::string message = "GET /path HTTP/1.1\n";
  message += "Content-Length: 1024\n";
  message += "Location: https://facebook.com/\n";
  message += "Pragma: no-cache\n";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  assert(!driver.result);
  assert(!driver.message.headers.empty());
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(driver.message.start_line.path == "/path");
  assert(driver.message.headers["Content-Length"] == "1024");
  assert(driver.message.headers["Location"] == "https://facebook.com/");
  assert(driver.message.headers["Pragma"] == "no-cache");

  std::cout << std::endl << "\t\t TEST_7 PASSED!" << std::endl;
}

void test_6 (bool debug)
{
  std::string message = "GET /path HTTP/1.1\n";
  message += "Content-Length: 1024\n";
  message += "Host: 1111\n";

  HTTPDriver driver(debug, debug);
  driver.parse_source(message);

  assert(!driver.result);
  assert(!driver.message.headers.empty());
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(driver.message.start_line.path == "/path");
  assert(driver.message.headers["Content-Length"] == "1024");
  assert(driver.message.headers["Host"] == "1111");

  std::cout << std::endl << "\t\t TEST_6 PASSED!" << std::endl;
}

void test_5 (bool debug)
{
  HTTPDriver driver(debug, debug);
  driver.parse_source("GET /path HTTP/1.1\nContent-Length: 2448\n");

  assert(!driver.result);
  assert(!driver.message.headers.empty());
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(driver.message.start_line.path == "/path");
  assert(driver.message.headers["Content-Length"] == "2448");

  std::cout << std::endl << "\t\t TEST_5 PASSED!" << std::endl;
}

void test_4 (bool debug)
{
  HTTPDriver driver(debug, debug);
  driver.parse_source("HTTP/1.1 200 OK\n");

  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.status_code == 200);
  assert(driver.message.start_line.reason_phrase == "OK");

  std::cout << std::endl << "\t\t TEST_4 PASSED!" << std::endl;
}


void test_3 (bool debug)
{
  HTTPDriver driver(debug, debug);
  driver.parse_source("HTTP/1.1 404 Not Found\n");

  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.status_code == 404);
  assert(driver.message.start_line.reason_phrase == "Not Found");

  std::cout << std::endl << "\t\t TEST_3 PASSED!" << std::endl;
}

void test_2 (bool debug)
{
  HTTPDriver driver(debug, debug);
  driver.parse_source("GET /path HTTP/1.1\n");

  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.path == "/path");

  std::cout << std::endl << "\t\t TEST_2 PASSED!" << std::endl;
}

void test_1 (bool debug)
{
  HTTPDriver driver(debug, debug);
  driver.parse("./tests/get-req.txt");

  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.path == "/path");

  std::cout << std::endl << "\t\t TEST_1 PASSED!" << std::endl;
}

