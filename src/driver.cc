#include "yahttp/parser/driver.hh"

namespace yahttp
{

HTTPDriver::HTTPDriver() {}

HTTPDriver::HTTPDriver(bool ts, bool tp, bool mp)
    : trace_scanning(ts), trace_parsing(tp), multi_parsing(mp)
{
}

HTTPDriver::~HTTPDriver() { scan_destroy(); }

void HTTPDriver::parse(const char* source)
{
  std::stringstream ss;

  ss.write(source, strlen(source));
  parse(ss);
}

void HTTPDriver::parse(const char* source, const size_t len)
{
  std::stringstream ss;

  ss.write(source, len);
  parse(ss);
}

void HTTPDriver::parse(std::ifstream& file)
{
  if (!file)
    throw std::runtime_error("could'nt find file");

  scan_begin(&file);
  HTTPParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
  scan_end();
}

void HTTPDriver::parse(std::stringstream& source)
{
  scan_begin(&source);
  HTTPParser parser(*this);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
  scan_end();
}

void HTTPDriver::error(const location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void HTTPDriver::error(const std::string& m) { std::cerr << m << std::endl; }

}; // ! ns yahttp

