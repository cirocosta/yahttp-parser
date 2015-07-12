#include "driver.hh"
#include "parser.hh"

HTTPDriver::HTTPDriver ()
  : trace_scanning(true), trace_parsing(true)
{ }

HTTPDriver::~HTTPDriver()
{ }

int HTTPDriver::parse (const std::string &f)
{
  int res = 0;

  file = f;
  scan_begin();
  yy::HTTPParser parser(*this);
  parser.set_debug_level(trace_parsing);
  res = parser.parse();
  scan_end();

  return res;
}

void HTTPDriver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void HTTPDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}

