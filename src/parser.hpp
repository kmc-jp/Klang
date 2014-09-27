#ifndef KMC_KLANG_PARSER_HPP
#define KMC_KLANG_PARSER_HPP

#include "lexer.hpp"

namespace klang {

class Parser {
 public:
  Parser(TokenVector tokens);
 private:
  using Pointer = TokenVector::const_iterator;
  TokenType current_type() const;
  std::string current_string() const;
  bool is_eof() const;
  bool advance(int count);
  Pointer snapshot() const;
  void rewind(Pointer p);
  const TokenVector tokens_;
  Pointer current_;
};

}  // namespace klang

#endif  // KMC_KLANG_PARSER_HPP
