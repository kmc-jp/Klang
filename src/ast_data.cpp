#include "ast_data.hpp"

#include <cassert>

namespace klang {
namespace ast {

IdentifierData::IdentifierData(const std::string& identifier_name)
    : identifier_name_(identifier_name)
{}

TypeData::TypeData(const std::string& type_name)
    : type_name_(type_name)
{}

IntegerLiteralData::IntegerLiteralData(const std::string& integer_literal)
    : integer_literal_(integer_literal)
{}

TranslationUnitData::TranslationUnitData(
    std::vector<FunctionDefinitionPtr> functions)
    : functions_(std::move(functions)) {
  assert(1 <= functions_.size());
}

FunctionDefinitionData::FunctionDefinitionData(
    IdentifierPtr function_name,
    ArgumentListPtr arguments,
    TypePtr return_type,
    CompoundStatementPtr function_body)
    : function_name_(std::move(function_name)),
      arguments_(std::move(arguments)),
      return_type_(std::move(return_type)),
      function_body_(std::move(function_body))
{}

ArgumentListData::ArgumentListData(std::vector<ArgumentPtr> arguments)
    : arguments_(std::move(arguments))
{}

ArgumentData::ArgumentData(TypePtr argument_type, IdentifierPtr argument_name)
    : argument_type_(std::move(argument_type)),
      argument_name_(std::move(argument_name))
{}

CompoundStatementData::CompoundStatementData(
    std::vector<StatementPtr> statements)
    : statements_(std::move(statements))
{}

ExpressionStatementData::ExpressionStatementData(ExpressionPtr expression)
    : expression_(std::move(expression))
{}

VariableDefinitionStatementData::VariableDefinitionStatementData(
    VariableDefinitionPtr variable_definition)
    : variable_definition_(std::move(variable_definition))
{}

MutableVariableDefinitionData::MutableVariableDefinitionData(
    TypePtr type_name,
    IdentifierPtr variable_name,
    ExpressionPtr expression)
    : type_name_(std::move(type_name)),
      variable_name_(std::move(variable_name)),
      expression_(std::move(expression))
{}

ImmutableVariableDefinitionData::ImmutableVariableDefinitionData(
    TypePtr type_name,
    IdentifierPtr variable_name,
    ExpressionPtr expression)
    : type_name_(std::move(type_name)),
      variable_name_(std::move(variable_name)),
      expression_(std::move(expression))
{}

IfStatementData::IfStatementData(ExpressionPtr condition,
                                 CompoundStatementPtr compound_statement,
                                 IfStatementPtr else_statement)
    : condition_(std::move(condition)),
      then_block_(std::move(compound_statement)),
      else_block_(std::move(else_statement))
{}

ElseStatementData::ElseStatementData(CompoundStatementPtr compound_statement)
    : else_block_(std::move(compound_statement))
{}

WhileStatementData::WhileStatementData(ExpressionPtr condition,
                                       CompoundStatementPtr compound_statement)
    : condition_(std::move(condition)),
      compound_statement_(std::move(compound_statement))
{}

ForStatementData::ForStatementData(ExpressionPtr expression1,
                                   ExpressionPtr expression2,
                                   ExpressionPtr expression3,
                                   CompoundStatementPtr compound_statement)
    : expression1_(std::move(expression1)),
      expression2_(std::move(expression2)),
      expression3_(std::move(expression3)),
      compound_statement_(std::move(compound_statement))
{}

ReturnStatementData::ReturnStatementData(ExpressionPtr return_value)
    : return_value_(std::move(return_value))
{}

BreakStatementData::BreakStatementData()
{}

ContinueStatementData::ContinueStatementData()
{}

AssignExpressionData::AssignExpressionData(
    OrExpressionPtr lhs_expression, OrExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

AddAssignExpressionData::AddAssignExpressionData(
    OrExpressionPtr lhs_expression, OrExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

SubtractAssignExpressionData::SubtractAssignExpressionData(
    OrExpressionPtr lhs_expression, OrExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

MultiplyAssignExpressionData::MultiplyAssignExpressionData(
    OrExpressionPtr lhs_expression, OrExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

DivideAssignExpressionData::DivideAssignExpressionData(
    OrExpressionPtr lhs_expression, OrExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

ModuloAssignExpressionData::ModuloAssignExpressionData(
    OrExpressionPtr lhs_expression, OrExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

OrExpressionData::OrExpressionData(
    AndExpressionPtr lhs_expression, OrExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

AndExpressionData::AndExpressionData(
    ComparativeExpressionPtr lhs_expression, AndExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

EqualExpressionData::EqualExpressionData(
    AdditiveExpressionPtr lhs_expression, AdditiveExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

NotEqualExpressionData::NotEqualExpressionData(
    AdditiveExpressionPtr lhs_expression, AdditiveExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

LessExpressionData::LessExpressionData(
    AdditiveExpressionPtr lhs_expression, AdditiveExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

GreaterExpressionData::GreaterExpressionData(
    AdditiveExpressionPtr lhs_expression, AdditiveExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

LessOrEqualExpressionData::LessOrEqualExpressionData(
    AdditiveExpressionPtr lhs_expression, AdditiveExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

GreaterOrEqualExpressionData::GreaterOrEqualExpressionData(
    AdditiveExpressionPtr lhs_expression, AdditiveExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

AddExpressionData::AddExpressionData(
    MultiplicativeExpressionPtr lhs_expression,
    AdditiveExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

SubtractExpressionData::SubtractExpressionData(
    MultiplicativeExpressionPtr lhs_expression,
    AdditiveExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

MultiplyExpressionData::MultiplyExpressionData(
    UnaryExpressionPtr lhs_expression,
    MultiplicativeExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

DivideExpressionData::DivideExpressionData(
    UnaryExpressionPtr lhs_expression,
    MultiplicativeExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

ModuloExpressionData::ModuloExpressionData(
    UnaryExpressionPtr lhs_expression,
    MultiplicativeExpressionPtr rhs_expression)
    : lhs_expression_(std::move(lhs_expression)),
      rhs_expression_(std::move(rhs_expression))
{}

NotExpressionData::NotExpressionData(UnaryExpressionPtr unary_expression)
    : unary_expression_(std::move(unary_expression))
{}

MinusExpressionData::MinusExpressionData(UnaryExpressionPtr unary_expression)
    : unary_expression_(std::move(unary_expression))
{}

FunctionCallData::FunctionCallData(IdentifierPtr function_name,
                                   ParameterListPtr parameter_list)
    : function_name_(std::move(function_name)),
      parameter_list_(std::move(parameter_list))
{}

ParameterListData::ParameterListData(std::vector<ParameterPtr> parameters)
    : parameters_(std::move(parameters))
{}

ParameterData::ParameterData(ExpressionPtr expression)
    : expression_(std::move(expression))
{}

ParenthesizedExpressionData::ParenthesizedExpressionData(
    ExpressionPtr expression)
    : expression_(std::move(expression))
{}

IdentifierExpressionData::IdentifierExpressionData(IdentifierPtr identifier)
    : identifier_(std::move(identifier))
{}

IntegerLiteralExpressionData::IntegerLiteralExpressionData(
    IntegerLiteralPtr integer_literal)
    : integer_literal_(std::move(integer_literal))
{}

}  // namespace ast
}  // namespace klang
