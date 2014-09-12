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
  ast::TypePtr parse_type();
  ast::IntegerLiteralPtr parse_integer_literal();
  ast::CharacterLiteralPtr parse_character_literal();
  ast::StringLiteralPtr parse_string_literal();
  ast::TranslationUnitPtr parse_translation_unit();
  ast::FunctionDefinitionPtr parse_function_definition();
  ast::ArgumentListPtr parse_argument_list();
  ast::CompoundStatementPtr parse_compound_statement();
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