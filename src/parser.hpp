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
  ast::TranslationUnitPtr parse_translation_unit();
  ast::FunctionDefinitionPtr parse_function_definition();
  ast::ArgumentListPtr parse_argument_list();
  ast::ArgumentPtr parse_argument();
  ast::StatementPtr parse_statement();
  ast::CompoundStatementPtr parse_compound_statement();
  ast::IfStatementPtr parse_if_statement();
  ast::IfStatementPtr parse_else_statement();
  ast::WhileStatementPtr parse_while_statement();
  ast::ForStatementPtr parse_for_statement();
  ast::ReturnStatementPtr parse_return_statement();
  ast::BreakStatementPtr parse_break_statement();
  ast::ContinueStatementPtr parse_continue_statement();
  ast::VariableDefinitionStatementPtr parse_variable_definition_statement();
  ast::VariableDefinitionPtr parse_variable_definition();
  ast::ExpressionStatementPtr parse_expression_statement();
  ast::ExpressionPtr parse_expression();
  ast::AssignExpressionPtr parse_assign_expression();
  ast::OrExpressionPtr parse_or_expression();
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
