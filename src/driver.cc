#include "driver.hh"
#include "parser.hh"

HTTPDriver::HTTPDriver ()
  : trace_scanning(false), trace_parsing(false)
{
  message.start_line.reason_phrase = "";
}

HTTPDriver::HTTPDriver (bool ts, bool tp)
  : trace_scanning(ts), trace_parsing(tp)
{
  message.start_line.reason_phrase = "";
}

HTTPDriver::~HTTPDriver()
{
  scan_destroy();
}

void HTTPDriver::parse (const std::string &f)
{
  file = f;
  scan_begin();
  yy::HTTPParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
  scan_end();
}

void HTTPDriver::parse_source (const std::string &source)
{
  scan_begin_source(source);
  yy::HTTPParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
}

void HTTPDriver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void HTTPDriver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}

