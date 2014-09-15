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
 private:
  std::string identifier_name_;
};

class TypeData : public Type {
 public:
  TypeData(const std::string& type_name);
 private:
  std::string type_name_;
};

class IntegerLiteralData : public IntegerLiteral {
 public:
  IntegerLiteralData(const std::string& integer_literal);
 private:
  std::string integer_literal_;
};

class CharacterLiteralData : public CharacterLiteral {
 public:
  CharacterLiteralData(const std::string& character_literal);
 private:
  std::string character_literal_;
};

class TranslationUnitData : public TranslationUnit {
 public:
  TranslationUnitData(std::vector<FunctionDefinitionPtr> functions);
 private:
  std::vector<FunctionDefinitionPtr> functions_;
};

class FunctionDefinitionData : public FunctionDefinition {
 public:
  FunctionDefinitionData(IdentifierPtr function_name,
                         ArgumentListPtr arguments,
                         TypePtr return_type,
                         CompoundStatementPtr function_body);
 private:
  IdentifierPtr function_name_;
  ArgumentListPtr arguments_;
  TypePtr return_type_;
  CompoundStatementPtr function_body_;
};

class ArgumentListData : public ArgumentList {
 public:
  ArgumentListData(std::vector<ArgumentPtr> arguments);
 private:
  std::vector<ArgumentPtr> arguments_;
};

class ArgumentData : public Argument {
 public:
  ArgumentData(TypePtr argument_type, IdentifierPtr argument_name);
 private:
  TypePtr argument_type_;
  IdentifierPtr argument_name_;
};

class CompoundStatementData : public CompoundStatement {
 public:
  CompoundStatementData(std::vector<StatementPtr> statements);
 private:
  std::vector<StatementPtr> statements_;
};

class ExpressionStatementData : public ExpressionStatement {
 public:
  ExpressionStatementData(ExpressionPtr expression);
 private:
  ExpressionPtr expression_;
};

class VariableDefinitionStatementData : public VariableDefinitionStatement {
 public:
  VariableDefinitionStatementData(VariableDefinitionPtr variable_definition);
 private:
  VariableDefinitionPtr variable_definition_;
};

class VariableDefinitionData : public VariableDefinition {
 public:
  VariableDefinitionData(TypePtr type_name,
                         bool is_mutable,
                         IdentifierPtr variable_name,
                         ExpressionPtr expression);
 private:
  TypePtr type_name_;
  bool is_mutable_;
  IdentifierPtr variable_name_;
  ExpressionPtr expression_;
};

class IfStatementData : public IfStatement {
 public:
  IfStatementData(ExpressionPtr condition,
                  CompoundStatementPtr compound_statement,
                  IfStatementPtr else_statement);
 private:
  ExpressionPtr condition_;
  CompoundStatementPtr then_block_;
  IfStatementPtr else_block_;
};

class ElseStatementData : public IfStatement {
 public:
  ElseStatementData(CompoundStatementPtr compound_statement);
 private:
  CompoundStatementPtr else_block_;
};

class WhileStatementData : public WhileStatement {
 public:
  WhileStatementData(ExpressionPtr condition,
                     CompoundStatementPtr compound_statement);
 private:
  ExpressionPtr condition_;
  CompoundStatementPtr compound_statement_;
};

class ForStatementData : public ForStatement {
 public:
  ForStatementData(ExpressionPtr expression1,
                   ExpressionPtr expression2,
                   ExpressionPtr expression3,
                   CompoundStatementPtr compound_statement);
 private:
  ExpressionPtr expression1_, expression2_, expression3_;
  CompoundStatementPtr compound_statement_;
};

class ReturnStatementData : public ReturnStatement {
 public:
  ReturnStatementData(ExpressionPtr return_value);
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

class AssignExpressionData : public AssignExpression {
 public:
  AssignExpressionData(OrExpressionPtr lhs_expression,
                       OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class AddAssignExpressionData : public AssignExpression {
 public:
  AddAssignExpressionData(OrExpressionPtr lhs_expression,
                          OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class SubtractAssignExpressionData : public AssignExpression {
 public:
  SubtractAssignExpressionData(OrExpressionPtr lhs_expression,
                               OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class MultiplyAssignExpressionData : public AssignExpression {
 public:
  MultiplyAssignExpressionData(OrExpressionPtr lhs_expression,
                               OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class DivideAssignExpressionData : public AssignExpression {
 public:
  DivideAssignExpressionData(OrExpressionPtr lhs_expression,
                             OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class ModuloAssignExpressionData : public AssignExpression {
 public:
  ModuloAssignExpressionData(OrExpressionPtr lhs_expression,
                             OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class OrExpressionData : public OrExpression {
 public:
  OrExpressionData(AndExpressionPtr lhs_expression,
                   OrExpressionPtr rhs_expression);
 private:
  AndExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class AndExpressionData : public AndExpression {
 public:
  AndExpressionData(ComparativeExpressionPtr lhs_expression,
                    AndExpressionPtr rhs_expression);
 private:
  ComparativeExpressionPtr lhs_expression_;
  AndExpressionPtr rhs_expression_;
};

class EqualExpressionData : public ComparativeExpression {
 public:
  EqualExpressionData(AdditiveExpressionPtr lhs_expression,
                      AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class NotEqualExpressionData : public ComparativeExpression {
 public:
  NotEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                         AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class LessExpressionData : public ComparativeExpression {
 public:
  LessExpressionData(AdditiveExpressionPtr lhs_expression,
                     AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class GreaterExpressionData : public ComparativeExpression {
 public:
  GreaterExpressionData(AdditiveExpressionPtr lhs_expression,
                        AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class LessOrEqualExpressionData : public ComparativeExpression {
 public:
  LessOrEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                            AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class GreaterOrEqualExpressionData : public ComparativeExpression {
 public:
  GreaterOrEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                               AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class AddExpressionData : public AdditiveExpression {
 public:
  AddExpressionData(MultiplicativeExpressionPtr lhs_expression,
                    AdditiveExpressionPtr rhs_expression);
 private:
  MultiplicativeExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class SubtractExpressionData : public AdditiveExpression {
 public:
  SubtractExpressionData(MultiplicativeExpressionPtr lhs_expression,
                         AdditiveExpressionPtr rhs_expression);
 private:
  MultiplicativeExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class MultiplyExpressionData : public MultiplicativeExpression {
 public:
  MultiplyExpressionData(UnaryExpressionPtr lhs_expression,
                         MultiplicativeExpressionPtr rhs_expression);
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class DivideExpressionData : public MultiplicativeExpression {
 public:
  DivideExpressionData(UnaryExpressionPtr lhs_expression,
                       MultiplicativeExpressionPtr rhs_expression);
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class ModuloExpressionData : public MultiplicativeExpression {
 public:
  ModuloExpressionData(UnaryExpressionPtr lhs_expression,
                       MultiplicativeExpressionPtr rhs_expression);
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class NotExpressionData : public UnaryExpression {
 public:
  NotExpressionData(UnaryExpressionPtr unary_expression);
 private:
  UnaryExpressionPtr unary_expression_;
};

class MinusExpressionData : public UnaryExpression {
 public:
  MinusExpressionData(UnaryExpressionPtr unary_expression);
 private:
  UnaryExpressionPtr unary_expression_;
};

class FunctionCallData : public PostfixExpression {
 public:
  FunctionCallData(IdentifierPtr function_name,
                   ParameterListPtr parameter_list);
 private:
  IdentifierPtr function_name_;
  ParameterListPtr parameter_list_;
};

class ParameterListData : public ParameterList {
 public:
  ParameterListData(std::vector<ParameterPtr> parameters);
 private:
  std::vector<ParameterPtr> parameters_;
};

class ParameterData : public Parameter {
 public:
  ParameterData(ExpressionPtr expression);
 private:
  ExpressionPtr expression_;
};

class ParenthesizedExpressionData : public PrimaryExpression {
 public:
  ParenthesizedExpressionData(ExpressionPtr expression);
 private:
  ExpressionPtr expression_;
};

class IdentifierExpressionData : public PrimaryExpression {
 public:
  IdentifierExpressionData(IdentifierPtr identifier);
 private:
  IdentifierPtr identifier_;
};

class IntegerLiteralExpressionData : public PrimaryExpression {
 public:
  IntegerLiteralExpressionData(IntegerLiteralPtr integer_literal);
 private:
  IntegerLiteralPtr integer_literal_;
};

}  // namespace ast
}  // namespace klang

#endif  // KMC_KLANG_AST_DATA_HPP
