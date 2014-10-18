#ifndef KMC_KLANG_PARSER_HPP
#define KMC_KLANG_PARSER_HPP

#include "ast.hpp"
#include "either.hpp"
#include "lexer.hpp"

namespace klang {

using ErrorInfo = Token;

template <class T>
using WithError = Either<ErrorInfo, T>;

class Parser {
 public:
  Parser(TokenVector tokens);
  bool parse_symbol(const char* str);
  WithError<ast::IdentifierPtr> parse_identifier();
  WithError<ast::TypePtr> parse_type();
  WithError<ast::IntegerLiteralPtr> parse_integer_literal();
  WithError<ast::CharacterLiteralPtr> parse_character_literal();
  WithError<ast::StringLiteralPtr> parse_string_literal();
  WithError<ast::TranslationUnitPtr> parse_translation_unit();
  WithError<ast::FunctionDefinitionPtr> parse_function_definition();
  WithError<ast::ArgumentListPtr> parse_argument_list();
  WithError<ast::ArgumentPtr> parse_argument();
  WithError<ast::StatementPtr> parse_statement();
  WithError<ast::CompoundStatementPtr> parse_compound_statement();
  WithError<ast::IfStatementPtr> parse_if_statement();
  WithError<ast::ElseStatementPtr> parse_else_statement();
  WithError<ast::WhileStatementPtr> parse_while_statement();
  WithError<ast::ForStatementPtr> parse_for_statement();
  WithError<ast::ReturnStatementPtr> parse_return_statement();
  WithError<ast::BreakStatementPtr> parse_break_statement();
  WithError<ast::ContinueStatementPtr> parse_continue_statement();
  WithError<ast::VariableDefinitionStatementPtr>
  parse_variable_definition_statement();
  WithError<ast::VariableDefinitionPtr> parse_variable_definition();
  WithError<ast::ExpressionStatementPtr> parse_expression_statement();
  WithError<ast::ExpressionPtr> parse_expression();
  WithError<ast::AssignExpressionPtr> parse_assign_expression();
  WithError<ast::OrExpressionPtr> parse_or_expression();
  WithError<ast::AndExpressionPtr> parse_and_expression();
  WithError<ast::ComparativeExpressionPtr> parse_comparative_expression();
  WithError<ast::AdditiveExpressionPtr> parse_additive_expression();
  WithError<ast::MultiplicativeExpressionPtr> parse_multiplicative_expression();
  WithError<ast::UnaryExpressionPtr> parse_unary_expression();
  WithError<ast::PostfixExpressionPtr> parse_postfix_expression();
  WithError<ast::FunctionCallExpressionPtr> parse_function_call_expression();
  WithError<ast::ParameterListPtr> parse_parameter_list();
  WithError<ast::ParameterPtr> parse_parameter();
  WithError<ast::PrimaryExpressionPtr> parse_primary_expression();
 private:
  using Pointer = TokenVector::const_iterator;
  TokenType current_type() const;
  std::string current_string() const;
  bool is_eof() const;
  bool advance(int count);
  Pointer snapshot() const;
  void rewind(Pointer p);
  Left<ErrorInfo> make_error() const;
  const TokenVector tokens_;
  Pointer current_;
};

}  // namespace klang

#endif  // KMC_KLANG_PARSER_HPP
