#include "yahttp/parser/driver.hh"
#include "parser.hh"

namespace yahttp {

HTTPDriver::HTTPDriver ()
  : trace_scanning(false), trace_parsing(false)
{ }

HTTPDriver::HTTPDriver (bool ts, bool tp)
  : trace_scanning(ts), trace_parsing(tp)
{ }

HTTPDriver::~HTTPDriver()
{
  scan_destroy();
}

void HTTPDriver::parse (const std::string &f)
{
  file = f;
  scan_begin();
  HTTPParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
  scan_end();
}

void HTTPDriver::parse_source (const std::string &source)
{
  scan_begin_source(source);
  HTTPParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
}

void HTTPDriver::error (const location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void HTTPDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}

}; // ! ns yahttp

