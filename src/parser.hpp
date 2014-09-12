#ifndef KMC_KLANG_PARSER_HPP
#define KMC_KLANG_PARSER_HPP

#include "lexer.hpp"
#include "ast.hpp"

namespace klang {

class Parser {
 public:
  Parser(TokenVector tokens);
  bool parse_symbol(const char* str);
  ast::IdentifierPtr parse_identifier();
 private:
  TokenType current_type() const;
  std::string current_string() const;
  bool is_eof() const;
  bool advance(int count);
  TokenVector::const_iterator make_snapshot() const;
  void rewind(TokenVector::const_iterator snapshot);
  const TokenVector tokens_;
  TokenVector::const_iterator current_;
};

}  // namespace klang

#endif  // KMC_KLANG_PARSER_HPP
