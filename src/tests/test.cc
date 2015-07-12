#include <iostream>
#include "../driver.hh"

int main()
{
  HTTPDriver driver;
  driver.parse("./tests/get-req.txt");

  exit(EXIT_SUCCESS);
}

