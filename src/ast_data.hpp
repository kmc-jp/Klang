#ifndef KMC_KLANG_AST_DATA_HPP
#define KMC_KLANG_AST_DATA_HPP

#include "ast.hpp"
#include <string>
#include <vector>

namespace klang {
namespace ast {

class IdentifierData : public Identifier {
 public:
  IdentifierData(const std::string& identifier_name);
  std::string const& identifier_name() const { return identifier_name_; }
 private:
  std::string identifier_name_;
};

class TypeData : public Type {
 public:
  TypeData(const std::string& type_name);
  std::string const& type_name() const { return type_name_; }
 private:
  std::string type_name_;
};

class IntegerLiteralData : public IntegerLiteral {
 public:
  IntegerLiteralData(const std::string& integer_literal);
  std::string const& integer_literal() const { return integer_literal_; }
 private:
  std::string integer_literal_;
};

class CharacterLiteralData : public CharacterLiteral {
 public:
  CharacterLiteralData(const std::string& character_literal);
  std::string const& character_literal() const { return character_literal_; }
 private:
  std::string character_literal_;
};

class StringLiteralData : public StringLiteral {
 public:
  StringLiteralData(const std::string& string_literal);
  std::string const& string_literal() const { return string_literal_; }
 private:
  std::string string_literal_;
};

class TranslationUnitData : public TranslationUnit {
 public:
  TranslationUnitData(std::vector<FunctionDefinitionPtr> functions);
  std::vector<FunctionDefinitionPtr> const& functions() const { return functions_; }
 private:
  std::vector<FunctionDefinitionPtr> functions_;
};

class FunctionDefinitionData : public FunctionDefinition {
 public:
  FunctionDefinitionData(IdentifierPtr function_name,
                         ArgumentListPtr arguments,
                         TypePtr return_type,
                         CompoundStatementPtr function_body);
  IdentifierPtr const& function_name() const { return function_name_; }
  ArgumentListPtr const& arguments() const { return arguments_; }
  TypePtr const& return_type() const { return return_type_; }
  CompoundStatementPtr const& function_body() const { return function_body_; }
 private:
  IdentifierPtr function_name_;
  ArgumentListPtr arguments_;
  TypePtr return_type_;
  CompoundStatementPtr function_body_;
};

class ArgumentListData : public ArgumentList {
 public:
  ArgumentListData(std::vector<ArgumentPtr> arguments);
  std::vector<ArgumentPtr> const& arguments() const { return arguments_; }
 private:
  std::vector<ArgumentPtr> arguments_;
};

class ArgumentData : public Argument {
 public:
  ArgumentData(TypePtr argument_type, IdentifierPtr argument_name);
  TypePtr const& argument_type() const { return argument_type_; }
  IdentifierPtr const& argument_name() const { return argument_name_; }
 private:
  TypePtr argument_type_;
  IdentifierPtr argument_name_;
};

class CompoundStatementData : public CompoundStatement {
 public:
  CompoundStatementData(std::vector<StatementPtr> statements);
  std::vector<StatementPtr> const& statements() const { return statements_; }
 private:
  std::vector<StatementPtr> statements_;
};

class IfStatementData : public IfStatement {
 public:
  IfStatementData(ExpressionPtr condition,
                  CompoundStatementPtr compound_statement,
                  ElseStatementPtr else_statement);
  ExpressionPtr const& condition() const { return condition_; }
  CompoundStatementPtr const& then_block() const { return then_block_; }
  ElseStatementPtr const& else_block() const { return else_block_; }
 private:
  ExpressionPtr condition_;
  CompoundStatementPtr then_block_;
  ElseStatementPtr else_block_;
};

class ElseStatementData : public ElseStatement {
 public:
  ElseStatementData(CompoundStatementPtr compound_statement);
  CompoundStatementPtr const& else_block() const { return else_block_; }
 private:
  CompoundStatementPtr else_block_;
};

class WhileStatementData : public WhileStatement {
 public:
  WhileStatementData(ExpressionPtr condition,
                     CompoundStatementPtr compound_statement);
  ExpressionPtr const& condition() const { return condition_; }
  CompoundStatementPtr const& compound_statement() const { return compound_statement_; }
 private:
  ExpressionPtr condition_;
  CompoundStatementPtr compound_statement_;
};

class ForStatementData : public ForStatement {
 public:
  ForStatementData(ExpressionPtr init_expression,
                   ExpressionPtr cond_expression,
                   ExpressionPtr reinit_expression,
                   CompoundStatementPtr compound_statement);
  ExpressionPtr const& init_expression() const { return init_expression_; }
  ExpressionPtr const& cond_expression() const { return cond_expression_; }
  ExpressionPtr const& reinit_expression() const { return reinit_expression_; }
  CompoundStatementPtr const& compound_statement() const { return compound_statement_; }
 private:
  ExpressionPtr init_expression_;
  ExpressionPtr cond_expression_;
  ExpressionPtr reinit_expression_;
  CompoundStatementPtr compound_statement_;
};

class ReturnStatementData : public ReturnStatement {
 public:
  ReturnStatementData(ExpressionPtr return_value);
  ExpressionPtr const& return_value() const { return return_value_; }
 private:
  ExpressionPtr return_value_;
};

class BreakStatementData : public BreakStatement {
 public:
  BreakStatementData();
};

class ContinueStatementData : public ContinueStatement {
 public:
  ContinueStatementData();
};

class VariableDefinitionStatementData : public VariableDefinitionStatement {
 public:
  VariableDefinitionStatementData(VariableDefinitionPtr variable_definition);
  VariableDefinitionPtr const& variable_definition() const { return variable_definition_; }
 private:
  VariableDefinitionPtr variable_definition_;
};

class VariableDefinitionData : public VariableDefinition {
 public:
  VariableDefinitionData(TypePtr type_name,
                         bool is_mutable,
                         IdentifierPtr variable_name,
                         ExpressionPtr expression);
  TypePtr const& type_name() const { return type_name_; }
  bool is_mutable() const { return is_mutable_; }
  IdentifierPtr const& variable_name() const { return variable_name_; }
  ExpressionPtr const& expression() const { return expression_; }
 private:
  TypePtr type_name_;
  bool is_mutable_;
  IdentifierPtr variable_name_;
  ExpressionPtr expression_;
};

class ExpressionStatementData : public ExpressionStatement {
 public:
  ExpressionStatementData(ExpressionPtr expression);
  ExpressionPtr const& expression() const { return expression_; }
 private:
  ExpressionPtr expression_;
};

class AssignExpressionData : public AssignExpression {
 public:
  AssignExpressionData(OrExpressionPtr lhs_expression,
                       OrExpressionPtr rhs_expression);
  OrExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  OrExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class AddAssignExpressionData : public AssignExpression {
 public:
  AddAssignExpressionData(OrExpressionPtr lhs_expression,
                          OrExpressionPtr rhs_expression);
  OrExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  OrExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class SubtractAssignExpressionData : public AssignExpression {
 public:
  SubtractAssignExpressionData(OrExpressionPtr lhs_expression,
                               OrExpressionPtr rhs_expression);
  OrExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  OrExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class MultiplyAssignExpressionData : public AssignExpression {
 public:
  MultiplyAssignExpressionData(OrExpressionPtr lhs_expression,
                               OrExpressionPtr rhs_expression);
  OrExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  OrExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class DivideAssignExpressionData : public AssignExpression {
 public:
  DivideAssignExpressionData(OrExpressionPtr lhs_expression,
                             OrExpressionPtr rhs_expression);
  OrExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  OrExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class ModuloAssignExpressionData : public AssignExpression {
 public:
  ModuloAssignExpressionData(OrExpressionPtr lhs_expression,
                             OrExpressionPtr rhs_expression);
  OrExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  OrExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class OrExpressionData : public OrExpression {
 public:
  OrExpressionData(AndExpressionPtr lhs_expression,
                   OrExpressionPtr rhs_expression);
  AndExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  OrExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  AndExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class AndExpressionData : public AndExpression {
 public:
  AndExpressionData(ComparativeExpressionPtr lhs_expression,
                    AndExpressionPtr rhs_expression);
  ComparativeExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AndExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  ComparativeExpressionPtr lhs_expression_;
  AndExpressionPtr rhs_expression_;
};

class EqualExpressionData : public ComparativeExpression {
 public:
  EqualExpressionData(AdditiveExpressionPtr lhs_expression,
                      AdditiveExpressionPtr rhs_expression);
  AdditiveExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AdditiveExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class NotEqualExpressionData : public ComparativeExpression {
 public:
  NotEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                         AdditiveExpressionPtr rhs_expression);
  AdditiveExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AdditiveExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class LessExpressionData : public ComparativeExpression {
 public:
  LessExpressionData(AdditiveExpressionPtr lhs_expression,
                     AdditiveExpressionPtr rhs_expression);
  AdditiveExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AdditiveExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class GreaterExpressionData : public ComparativeExpression {
 public:
  GreaterExpressionData(AdditiveExpressionPtr lhs_expression,
                        AdditiveExpressionPtr rhs_expression);
  AdditiveExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AdditiveExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class LessOrEqualExpressionData : public ComparativeExpression {
 public:
  LessOrEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                            AdditiveExpressionPtr rhs_expression);
  AdditiveExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AdditiveExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class GreaterOrEqualExpressionData : public ComparativeExpression {
 public:
  GreaterOrEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                               AdditiveExpressionPtr rhs_expression);
  AdditiveExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AdditiveExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class AddExpressionData : public AdditiveExpression {
 public:
  AddExpressionData(MultiplicativeExpressionPtr lhs_expression,
                    AdditiveExpressionPtr rhs_expression);
  MultiplicativeExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AdditiveExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  MultiplicativeExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class SubtractExpressionData : public AdditiveExpression {
 public:
  SubtractExpressionData(MultiplicativeExpressionPtr lhs_expression,
                         AdditiveExpressionPtr rhs_expression);
  MultiplicativeExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  AdditiveExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  MultiplicativeExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class MultiplyExpressionData : public MultiplicativeExpression {
 public:
  MultiplyExpressionData(UnaryExpressionPtr lhs_expression,
                         MultiplicativeExpressionPtr rhs_expression);
  UnaryExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  MultiplicativeExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class DivideExpressionData : public MultiplicativeExpression {
 public:
  DivideExpressionData(UnaryExpressionPtr lhs_expression,
                       MultiplicativeExpressionPtr rhs_expression);
  UnaryExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  MultiplicativeExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class ModuloExpressionData : public MultiplicativeExpression {
 public:
  ModuloExpressionData(UnaryExpressionPtr lhs_expression,
                       MultiplicativeExpressionPtr rhs_expression);
  UnaryExpressionPtr const& lhs_expression() const { return lhs_expression_; }
  MultiplicativeExpressionPtr const& rhs_expression() const { return rhs_expression_; }
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class NotExpressionData : public UnaryExpression {
 public:
  NotExpressionData(UnaryExpressionPtr unary_expression);
  UnaryExpressionPtr const& unary_expression() const { return unary_expression_; }
 private:
  UnaryExpressionPtr unary_expression_;
};

class MinusExpressionData : public UnaryExpression {
 public:
  MinusExpressionData(UnaryExpressionPtr unary_expression);
  UnaryExpressionPtr const& unary_expression() const { return unary_expression_; }
 private:
  UnaryExpressionPtr unary_expression_;
};

class FunctionCallExpressionData : public FunctionCallExpression {
 public:
  FunctionCallExpressionData(IdentifierPtr function_name,
                             ParameterListPtr parameter_list);
  IdentifierPtr const& function_name() const { return function_name_; }
  ParameterListPtr const& parameter_list() const { return parameter_list_; }
 private:
  IdentifierPtr function_name_;
  ParameterListPtr parameter_list_;
};

class ParameterListData : public ParameterList {
 public:
  ParameterListData(std::vector<ParameterPtr> parameters);
  std::vector<ParameterPtr> const& parameters() const { return parameters_; }
 private:
  std::vector<ParameterPtr> parameters_;
};

class ParameterData : public Parameter {
 public:
  ParameterData(ExpressionPtr expression);
  ExpressionPtr const& expression() const { return expression_; }
 private:
  ExpressionPtr expression_;
};

class ParenthesizedExpressionData : public PrimaryExpression {
 public:
  ParenthesizedExpressionData(ExpressionPtr expression);
  ExpressionPtr const& expression() const { return expression_; }
 private:
  ExpressionPtr expression_;
};

class IdentifierExpressionData : public PrimaryExpression {
 public:
  IdentifierExpressionData(IdentifierPtr identifier);
  IdentifierPtr const& identifier() const { return identifier_; }
 private:
  IdentifierPtr identifier_;
};

class IntegerLiteralExpressionData : public PrimaryExpression {
 public:
  IntegerLiteralExpressionData(IntegerLiteralPtr integer_literal);
  IntegerLiteralPtr const& integer_literal() const { return integer_literal_; }
 private:
  IntegerLiteralPtr integer_literal_;
};

class CharacterLiteralExpressionData : public PrimaryExpression {
 public:
  CharacterLiteralExpressionData(CharacterLiteralPtr character_literal);
  CharacterLiteralPtr const& character_literal() const { return character_literal_; }
 private:
  CharacterLiteralPtr character_literal_;
};

class StringLiteralExpressionData : public PrimaryExpression {
 public:
  StringLiteralExpressionData(StringLiteralPtr string_literal);
  StringLiteralPtr const& string_literal() const { return string_literal_; }
 private:
  StringLiteralPtr string_literal_;
};

}  // namespace ast
}  // namespace klang

#endif  // KMC_KLANG_AST_DATA_HPP
