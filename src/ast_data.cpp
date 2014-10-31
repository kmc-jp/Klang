#include "ast_data.hpp"

namespace klang {
namespace ast {

IdentifierData::IdentifierData(const std::string& value)
    : value_(value)
{}

TypeData::TypeData(const std::string& value)
    : value_(value)
{}

IntegerLiteralData::IntegerLiteralData(const std::string& value)
    : value_(value)
{}

CharacterLiteralData::CharacterLiteralData(const std::string& value)
    : value_(value)
{}

StringLiteralData::StringLiteralData(const std::string& value)
    : value_(value)
{}

TranslationUnitData::TranslationUnitData(
    std::vector<FunctionDefinitionPtr> functions)
    : functions_(std::move(functions)) {
}

FunctionDefinitionData::FunctionDefinitionData(
    IdentifierPtr name,
    ArgumentListPtr arguments,
    TypePtr return_type,
    CompoundStatementPtr body)
    : name_(std::move(name)),
      arguments_(std::move(arguments)),
      return_type_(std::move(return_type)),
      body_(std::move(body))
{}

ArgumentListData::ArgumentListData(std::vector<ArgumentPtr> arguments)
    : arguments_(std::move(arguments))
{}

ArgumentData::ArgumentData(TypePtr type, IdentifierPtr name)
    : type_(std::move(type)),
      name_(std::move(name))
{}

CompoundStatementData::CompoundStatementData(
    std::vector<StatementPtr> statements)
    : statements_(std::move(statements))
{}

IfStatementData::IfStatementData(ExpressionPtr condition,
                                 CompoundStatementPtr body,
                                 ElseStatementPtr else_block)
    : condition_(std::move(condition)),
      body_(std::move(body)),
      else_block_(std::move(else_block))
{}

ElseStatementData::ElseStatementData(CompoundStatementPtr body)
    : body_(std::move(body))
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

VariableDefinitionStatementData::VariableDefinitionStatementData(
    VariableDefinitionPtr variable_definition)
    : variable_definition_(std::move(variable_definition))
{}

VariableDefinitionData::VariableDefinitionData(
    TypePtr type_name,
    bool is_mutable,
    IdentifierPtr variable_name,
    ExpressionPtr expression)
    : type_name_(std::move(type_name)),
      is_mutable_(is_mutable),
      variable_name_(std::move(variable_name)),
      expression_(std::move(expression))
{}

ExpressionStatementData::ExpressionStatementData(ExpressionPtr expression)
    : expression_(std::move(expression))
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

FunctionCallExpressionData::FunctionCallExpressionData(
    IdentifierPtr function_name,
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

CharacterLiteralExpressionData::CharacterLiteralExpressionData(
    CharacterLiteralPtr character_literal)
    : character_literal_(std::move(character_literal))
{}

StringLiteralExpressionData::StringLiteralExpressionData(
    StringLiteralPtr string_literal)
    : string_literal_(std::move(string_literal))
{}

}  // namespace ast
}  // namespace klang
