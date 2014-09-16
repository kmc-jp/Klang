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
  ast::ArgumentPtr parse_argument();
  ast::StatementPtr parse_statement();
  ast::CompoundStatementPtr parse_compound_statement();
  ast::ExpressionStatementPtr parse_expression_statement();
  ast::VariableDefinitionStatementPtr parse_variable_definition_statement();
  ast::VariableDefinitionPtr parse_variable_definition();
  ast::IfStatementPtr parse_if_statement();
  ast::IfStatementPtr parse_else_statement();
  ast::WhileStatementPtr parse_while_statement();
  ast::ForStatementPtr parse_for_statement();
  ast::ReturnStatementPtr parse_return_statement();
  ast::BreakStatementPtr parse_break_statement();
  ast::ContinueStatementPtr parse_continue_statement();
  ast::ExpressionPtr parse_expression();
  ast::AssignExpressionPtr parse_assign_expression();
  ast::AssignExpressionPtr parse_single_assign_expression();
  ast::AssignExpressionPtr parse_add_assign_expression();
  ast::AssignExpressionPtr parse_subtract_assign_expression();
  ast::AssignExpressionPtr parse_multiply_assign_expression();
  ast::AssignExpressionPtr parse_divide_assign_expression();
  ast::AssignExpressionPtr parse_modulo_assign_expression();
  ast::OrExpressionPtr parse_or_expression();
  ast::AndExpressionPtr parse_and_expression();
  ast::ComparativeExpressionPtr parse_comparative_expression();
  ast::ComparativeExpressionPtr parse_equal_expression();
  ast::ComparativeExpressionPtr parse_not_equal_expression();
  ast::ComparativeExpressionPtr parse_less_expression();
  ast::AdditiveExpressionPtr parse_additive_expression();
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
