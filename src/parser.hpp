#ifndef KMC_KLANG_PARSER_HPP
#define KMC_KLANG_PARSER_HPP

#include "lexer.hpp"

namespace klang {

class Parser {
 public:
  Parser(TokenVector tokens);
 private:
  const TokenVector tokens_;
  TokenVector::const_iterator current_;
};

}  // namespace klang

#endif  // KMC_KLANG_PARSER_HPP
