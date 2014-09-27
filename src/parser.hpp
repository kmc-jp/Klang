#ifndef KMC_KLANG_PARSER_HPP
#define KMC_KLANG_PARSER_HPP

#include "lexer.hpp"

namespace klang {

class Parser {
 public:
  Parser(TokenVector tokens);
 private:
  using Pointer = TokenVector::const_iterator;
  bool is_eof() const;
  const TokenVector tokens_;
  Pointer current_;
};

}  // namespace klang

#endif  // KMC_KLANG_PARSER_HPP
