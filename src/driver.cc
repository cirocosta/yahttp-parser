#include "driver.hh"
#include "parser.hh"

HTTPDriver::HTTPDriver ()
  : trace_scanning(true), trace_parsing(false)
{ }

HTTPDriver::~HTTPDriver()
{ }

void HTTPDriver::parse (const std::string &f)
{
  file = f;
  scan_begin();
  yy::HTTPParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
  scan_end();
}

void HTTPDriver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void HTTPDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}

