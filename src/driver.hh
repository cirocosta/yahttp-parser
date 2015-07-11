#ifndef CALV_HH
#define CALV_HH

#include <string>
#include <map>
#include "parser.hh"

#define YY_DECL \
  yy::calcxx_parser::symbol_type yylex (calcxx_driver& driver)

YY_DECL;

class calcxx_driver
{
public:
  calcxx_driver();
  virtual ~calcxx_driver();

  std::map<std::string, int> variables;

  int result;

  void scan_begin();
  void scan_end();
  bool trace_scanning;

  int parse(const std::string& file);
  std::string file;
  bool trace_parsing;

  void error(const yy::location& l, const std::string& m);
  void error(const std::string& m);
};

#endif
