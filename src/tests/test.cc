#include <iostream>
#include <cassert>
#include <string>
#include <cstring>

#include "../driver.hh"

void test_1();
void test_2();
void test_3();
void test_4();
void test_5();

int main()
{
  test_1();
  test_2();
  test_3();
  test_4();
  test_5();

  printf("SUCCESS!\n");

  exit(EXIT_SUCCESS);
}

void test_5 ()
{
  HTTPDriver driver(true, true);
  driver.parse_source("GET /path HTTP/1.1\nContent-Length: 2448");

  assert(!driver.result);
  assert(!driver.message.headers.empty());
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(driver.message.start_line.path == "/path");
  assert(driver.message.headers["Content-Length"] == "2448");

  std::cout << std::endl << "\t\t TEST_5 PASSED!" << std::endl;
}

void test_4 ()
{
  HTTPDriver driver(true, true);
  driver.parse_source("HTTP/1.1 200 OK\n");

  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.status_code == 200);
  assert(driver.message.start_line.reason_phrase == "OK");

  std::cout << std::endl << "\t\t TEST_4 PASSED!" << std::endl;
}


void test_3 ()
{
  HTTPDriver driver(true, true);
  driver.parse_source("HTTP/1.1 404 Not Found\n");

  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.status_code == 404);
  assert(driver.message.start_line.reason_phrase == "Not Found");

  std::cout << std::endl << "\t\t TEST_3 PASSED!" << std::endl;
}

void test_2 ()
{
  HTTPDriver driver(true, true);
  driver.parse_source("GET /path HTTP/1.1\n");

  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.path == "/path");

  std::cout << std::endl << "\t\t TEST_2 PASSED!" << std::endl;
}

void test_1 ()
{
  HTTPDriver driver(true, true);
  driver.parse("./tests/get-req.txt");

  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(driver.message.start_line.version == "HTTP/1.1");
  assert(driver.message.start_line.path == "/path");

  std::cout << std::endl << "\t\t TEST_1 PASSED!" << std::endl;
}

