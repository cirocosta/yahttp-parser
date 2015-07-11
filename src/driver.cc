#include "driver.hh"
#include "parser.hh"

calcxx_driver::calcxx_driver ()
  : trace_scanning(false), trace_parsing(false)
{
  variables["one"] = 1;
  variables["two"] = 2;
}

calcxx_driver::~calcxx_driver()
{
}

int calcxx_driver::parse (const std::string &f)
{
  int res = 0;

  file = f;
  scan_begin();
  yy::calcxx_parser parser(*this);
  parser.set_debug_level(trace_parsing);
  res = parser.parse();
  scan_end();

  return res;
}

void calcxx_driver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void calcxx_driver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}

