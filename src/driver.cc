#include "yahttp/parser/driver.hh"
#include "parser.hh"

namespace yahttp {

HTTPDriver::HTTPDriver ()
{ }

HTTPDriver::HTTPDriver (bool ts, bool tp, bool mp)
  : trace_scanning(ts), trace_parsing(tp), multi_parsing(mp)
{ }

HTTPDriver::~HTTPDriver()
{
  scan_destroy();
}

void HTTPDriver::parse (std::string& source)
{
  std::stringstream ss;

  ss << source;
  parse(ss);
}

void HTTPDriver::parse (std::stringstream& source)
{
  scan_begin(source);
  parser = std::shared_ptr<HTTPParser>(new HTTPParser(*this));
  parser->set_debug_level(trace_parsing);
  result = parser->parse();
  scan_end();
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

