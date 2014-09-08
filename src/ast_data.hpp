#ifndef KMC_KLANG_AST_DATA_HPP
#define KMC_KLANG_AST_DATA_HPP

#include "ast.hpp"
#include <string>
#include <vector>

namespace klang {

class IdentifierData : public IdentifierAst {
 public:
  IdentifierData(const std::string& identifier_name);
 private:
  std::string identifier_name_;
};

class TypeData : public TypeAst {
 public:
  TypeData(const std::string& type_name);
 private:
  std::string type_name_;
};

class IntegerLiteralData : public IntegerLiteralAst {
 public:
  IntegerLiteralData(const std::string& integer_literal);
 private:
  std::string integer_literal_;
};

class ProgramData : public ProgramAst {
 public:
  ProgramData(std::vector<FunctionDefinitionPtr> functions);
 private:
  std::vector<FunctionDefinitionPtr> functions_;
};

class FunctionDefinitionData : public FunctionDefinitionAst {
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

class ArgumentListData : public ArgumentListAst {
 public:
  ArgumentListData(std::vector<ArgumentPtr> arguments);
 private:
  std::vector<ArgumentPtr> arguments_;
};

class ArgumentData : public ArgumentAst {
 public:
  ArgumentData(TypePtr argument_type, IdentifierPtr argument_name);
 private:
  TypePtr argument_type_;
  IdentifierPtr argument_name_;
};

class CompoundStatementData : public CompoundStatementAst {
 public:
  CompoundStatementData(std::vector<StatementPtr> statements);
 private:
  std::vector<StatementPtr> statements_;
};

class ExpressionStatementData : public ExpressionStatementAst {
 public:
  ExpressionStatementData(ExpressionPtr expression);
 private:
  ExpressionPtr expression_;
};

class VariableDefinitionStatementData : public VariableDefinitionStatementAst {
 public:
  VariableDefinitionStatementData(VariableDefinitionPtr variable_definition);
 private:
  VariableDefinitionPtr variable_definition_;
};

class MutableVariableDefinitionData : public VariableDefinitionAst {
 public:
  MutableVariableDefinitionData(IdentifierPtr variable_name,
                                ExpressionPtr rhs_expression);
 private:
  IdentifierPtr variable_name_;
  ExpressionPtr rhs_expression_;
};

class ImmutableVariableDefinitionData : public VariableDefinitionAst {
 public:
  ImmutableVariableDefinitionData(IdentifierPtr variable_name,
                                  ExpressionPtr rhs_expression);
 private:
  IdentifierPtr variable_name_;
  ExpressionPtr rhs_expression_;
};

class IfStatementData : public IfStatementAst {
 public:
  IfStatementData(ExpressionPtr condition,
                  CompoundStatementPtr compound_statement,
                  IfStatementPtr else_statement);
 private:
  ExpressionPtr condition_;
  CompoundStatementPtr then_block_;
  IfStatementPtr else_block_;
};

class ElseStatementData : public IfStatementAst {
 public:
  ElseStatementData(CompoundStatementPtr compound_statement);
 private:
  CompoundStatementPtr else_block_;
};

class WhileStatementData : public WhileStatementAst {
 public:
  WhileStatementData(ExpressionPtr condition,
                     CompoundStatementPtr compound_statement);
 private:
  ExpressionPtr condition_;
  CompoundStatementPtr compound_statement_;
};

class ForStatementData : public ForStatementAst {
 public:
  ForStatementData(ExpressionPtr expression1,
                   ExpressionPtr expression2,
                   ExpressionPtr expression3,
                   CompoundStatementPtr compound_statement);
 private:
  ExpressionPtr expression1_, expression2_, expression3_;
  CompoundStatementPtr compound_statement_;
};

class ReturnStatementData : public ReturnStatementAst {
 public:
  ReturnStatementData(ExpressionPtr return_value);
 private:
  ExpressionPtr return_value_;
};

class BreakStatementData : public BreakStatementAst {
 public:
  BreakStatementData();
};

class ContinueStatementData : public ContinueStatementAst {
 public:
  ContinueStatementData();
};

class AssignExpressionData : public AssignExpressionAst {
 public:
  AssignExpressionData(OrExpressionPtr lhs_expression,
                       OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class AddAssignExpressionData : public AssignExpressionAst {
 public:
  AddAssignExpressionData(OrExpressionPtr lhs_expression,
                          OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class SubtractAssignExpressionData : public AssignExpressionAst {
 public:
  SubtractAssignExpressionData(OrExpressionPtr lhs_expression,
                               OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class MultiplyAssignExpressionData : public AssignExpressionAst {
 public:
  MultiplyAssignExpressionData(OrExpressionPtr lhs_expression,
                               OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class DivideAssignExpressionData : public AssignExpressionAst {
 public:
  DivideAssignExpressionData(OrExpressionPtr lhs_expression,
                             OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class ModuloAssignExpressionData : public AssignExpressionAst {
 public:
  ModuloAssignExpressionData(OrExpressionPtr lhs_expression,
                             OrExpressionPtr rhs_expression);
 private:
  OrExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class OrExpressionData : public OrExpressionAst {
 public:
  OrExpressionData(AndExpressionPtr lhs_expression,
                   OrExpressionPtr rhs_expression);
 private:
  AndExpressionPtr lhs_expression_;
  OrExpressionPtr rhs_expression_;
};

class AndExpressionData : public AndExpressionAst {
 public:
  AndExpressionData(ComparativeExpressionPtr lhs_expression,
                    AndExpressionPtr rhs_expression);
 private:
  ComparativeExpressionPtr lhs_expression_;
  AndExpressionPtr rhs_expression_;
};

class EqualExpressionData : public ComparativeExpressionAst {
 public:
  EqualExpressionData(AdditiveExpressionPtr lhs_expression,
                      AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class NotEqualExpressionData : public ComparativeExpressionAst {
 public:
  NotEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                         AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class LessExpressionData : public ComparativeExpressionAst {
 public:
  LessExpressionData(AdditiveExpressionPtr lhs_expression,
                     AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class GreaterExpressionData : public ComparativeExpressionAst {
 public:
  GreaterExpressionData(AdditiveExpressionPtr lhs_expression,
                        AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class LessOrEqualExpressionData : public ComparativeExpressionAst {
 public:
  LessOrEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                            AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class GreaterOrEqualExpressionData : public ComparativeExpressionAst {
 public:
  GreaterOrEqualExpressionData(AdditiveExpressionPtr lhs_expression,
                               AdditiveExpressionPtr rhs_expression);
 private:
  AdditiveExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class AddExpressionData : public AdditiveExpressionAst {
 public:
  AddExpressionData(MultiplicativeExpressionPtr lhs_expression,
                    AdditiveExpressionPtr rhs_expression);
 private:
  MultiplicativeExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class SubtractExpressionData : public AdditiveExpressionAst {
 public:
  SubtractExpressionData(MultiplicativeExpressionPtr lhs_expression,
                         AdditiveExpressionPtr rhs_expression);
 private:
  MultiplicativeExpressionPtr lhs_expression_;
  AdditiveExpressionPtr rhs_expression_;
};

class MultiplyExpressionData : public MultiplicativeExpressionAst {
 public:
  MultiplyExpressionData(UnaryExpressionPtr lhs_expression,
                         MultiplicativeExpressionPtr rhs_expression);
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class DivideExpressionData : public MultiplicativeExpressionAst {
 public:
  DivideExpressionData(UnaryExpressionPtr lhs_expression,
                       MultiplicativeExpressionPtr rhs_expression);
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class ModuloExpressionData : public MultiplicativeExpressionAst {
 public:
  ModuloExpressionData(UnaryExpressionPtr lhs_expression,
                       MultiplicativeExpressionPtr rhs_expression);
 private:
  UnaryExpressionPtr lhs_expression_;
  MultiplicativeExpressionPtr rhs_expression_;
};

class NotExpressionData : public UnaryExpressionAst {
 public:
  NotExpressionData(UnaryExpressionPtr unary_expression);
 private:
  UnaryExpressionPtr unary_expression_;
};

class MinusExpressionData : public UnaryExpressionAst {
 public:
  MinusExpressionData(UnaryExpressionPtr unary_expression);
 private:
  UnaryExpressionPtr unary_expression_;
};

class FunctionCallData : public PostfixExpressionAst {
 public:
  FunctionCallData(IdentifierPtr function_name,
                   ParameterListPtr parameter_list);
 private:
  IdentifierPtr function_name_;
  ParameterListPtr parameter_list_;
};

class ParameterListData : public ParameterListAst {
 public:
  ParameterListData(std::vector<ParameterPtr> parameters);
 private:
  std::vector<ParameterPtr> parameters_;
};

class ParameterData : public ParameterAst {
 public:
  ParameterData(ExpressionPtr expression);
 private:
  ExpressionPtr expression_;
};

class ParenthesizedExpressionData : public PrimaryExpressionAst {
 public:
  ParenthesizedExpressionData(ExpressionPtr expression);
 private:
  ExpressionPtr expression_;
};

class IdentifierExpressionData : public PrimaryExpressionAst {
 public:
  IdentifierExpressionData(IdentifierPtr identifier);
 private:
  IdentifierPtr identifier_;
};

class IntegerLiteralExpressionData : public PrimaryExpressionAst {
 public:
  IntegerLiteralExpressionData(IntegerLiteralPtr integer_literal);
 private:
  IntegerLiteralPtr integer_literal_;
};

}  // namespace klang

#endif  // KMC_KLANG_AST_DATA_HPP
