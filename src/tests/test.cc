#include <iostream>
#include "../driver.hh"

int main(int argc, char *argv[])
{
  if (argc < 2) {
    std::cerr << "parser requires at least 1 arg." << std::endl;
    exit(EXIT_FAILURE);
  }

  calcxx_driver driver;
  driver.parse(argv[1]);


  for (auto it = driver.variables.cbegin();
       it != driver.variables.cend(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
  }

  exit(EXIT_SUCCESS);
}

