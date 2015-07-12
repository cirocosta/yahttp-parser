#include <iostream>
#include <cassert>
#include <string>

#include "../driver.hh"


int main()
{
  HTTPDriver driver;
  driver.parse("./tests/get-req.txt");

  assert(driver.result);
  assert(driver.headers.empty());
  assert(driver.start_line.method == HTTPMethod::GET);
  assert(driver.start_line.version_major == 1);
  assert(driver.start_line.version_minor == 1);

  exit(EXIT_SUCCESS);
}

