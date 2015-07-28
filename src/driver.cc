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

void HTTPDriver::parse (const std::string &f)
{
  file = f;
  scan_begin();
  parser = std::shared_ptr<HTTPParser>(new HTTPParser(*this));
  parser->set_debug_level(trace_parsing);
  result = parser->parse();
  scan_end();
}
void HTTPDriver::parse_source (const std::string &source)
{
  scan_begin_source(source);
  parser = std::shared_ptr<HTTPParser>(new HTTPParser(*this));
  parser->set_debug_level(trace_parsing);
  result = parser->parse();
  scan_end_source();
}

void HTTPDriver::parse_multi_begin()
{
  multi_parsing = true;
  parser = std::shared_ptr<HTTPParser>(new HTTPParser(*this));
  parser->set_debug_level(trace_parsing);
}

void HTTPDriver::parse_multi_push(const std::string& source)
{
  scan_begin_source(source);
}

void HTTPDriver::parse_multi_end()
{
  result = parser->parse();
  scan_end_source();
  multi_parsing = false;
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

