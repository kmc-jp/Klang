#ifndef KMC_KLANG_PARSER_HPP
#define KMC_KLANG_PARSER_HPP

#include "ast.hpp"
#include "lexer.hpp"

namespace klang {

class Parser {
 public:
  Parser(TokenVector tokens);
  bool parse_symbol(const char* str);
  ast::IdentifierPtr parse_identifier();
  ast::TypePtr parse_type();
  ast::IntegerLiteralPtr parse_integer_literal();
  ast::CharacterLiteralPtr parse_character_literal();
  ast::StringLiteralPtr parse_string_literal();
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
