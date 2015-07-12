#include <iostream>
#include "../driver.hh"

int main()
{
  HTTPDriver driver;
  driver.parse("./tests/get-req.txt");

  for (auto it = driver.variables.cbegin();
       it != driver.variables.cend(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
  }

  exit(EXIT_SUCCESS);
}

