#include <iostream>
#include <cassert>
#include <string>
#include <cstring>

#include "../driver.hh"

HTTPDriver driver(true, true);
void test_1();
void test_2();
void test_3();

int main()
{
  test_1();
  test_2();
  test_3();

  printf("SUCCESS!\n");

  exit(EXIT_SUCCESS);
}

void test_2 ()
{
  driver.parse_source("GET / HTTP/1.1\n");
  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(std::strcmp(driver.message.start_line.version.c_str(), "HTTP/1.1"));

  std::cout << std::endl << "\t\t TEST_2 PASSED!" << std::endl;
}

void test_3 ()
{
  driver.parse_source("HTTP/1.1 404 Not Found\n");
  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(std::strcmp(driver.message.start_line.version.c_str(), "HTTP/1.1"));
  assert(driver.message.start_line.status_code == 404);

  std::cout << driver.message.start_line.reason_phrase << std::endl;
  std::cout << std::endl << "\t\t TEST_3 PASSED!" << std::endl;
}


void test_1 ()
{
  driver.parse("./tests/get-req.txt");
  assert(!driver.result);
  assert(driver.message.headers.empty());
  assert(driver.message.start_line.method == HTTPMethod::GET);
  assert(std::strcmp(driver.message.start_line.version.c_str(), "HTTP/1.1"));

  std::cout << std::endl << "\t\t TEST_1 PASSED!" << std::endl;
}

