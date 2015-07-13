#include <iostream>
#include <cassert>
#include <string>

#include "../driver.hh"

HTTPDriver driver;
void test_1();
void test_2();
/* void test_3(); */
/* void test_4(); */
/* void test_5(); */
/* void test_6(); */
/* void test_7(); */

int main()
{
  driver.trace_parsing = false;
  driver.trace_scanning = false;

  test_1();
  test_2();

  printf("SUCCESS!\n");

  exit(EXIT_SUCCESS);
}

void test_2 ()
{
  driver.parse_source("GET / HTTP/1.1\n");
  assert(!driver.result);
  assert(driver.headers.empty());
  assert(driver.start_line.method == HTTPMethod::GET);
  assert(driver.start_line.version_major == 1);
  assert(driver.start_line.version_minor == 1);
}


void test_1 ()
{
  driver.parse("./tests/get-req.txt");
  assert(!driver.result);
  assert(driver.headers.empty());
  assert(driver.start_line.method == HTTPMethod::GET);
  assert(driver.start_line.version_major == 1);
  assert(driver.start_line.version_minor == 1);
}

