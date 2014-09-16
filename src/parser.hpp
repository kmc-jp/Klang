#ifndef KMC_KLANG_PARSER_HPP
#define KMC_KLANG_PARSER_HPP

#include "lexer.hpp"

namespace klang {

class Parser {
 public:
  Parser(TokenVector tokens);
 private:
  TokenType current_type() const;
  std::string current_string() const;
  bool is_eof() const;
  bool advance(int count);
  const TokenVector tokens_;
  TokenVector::const_iterator current_;
};

}  // namespace klang

#endif  // KMC_KLANG_PARSER_HPP
