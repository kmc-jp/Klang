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
                                       CompoundStatementPtr body)
    : condition_(std::move(condition)),
      body_(std::move(body))
{}

ForStatementData::ForStatementData(ExpressionPtr initialize,
                                   ExpressionPtr condition,
                                   ExpressionPtr reinitialize,
                                   CompoundStatementPtr body)
    : initialize_(std::move(initialize)),
      condition_(std::move(condition)),
      reinitialize_(std::move(reinitialize)),
      body_(std::move(body))
{}

ReturnStatementData::ReturnStatementData(ExpressionPtr return_value)
    : return_value_(std::move(return_value))
{}

BreakStatementData::BreakStatementData()
{}

ContinueStatementData::ContinueStatementData()
{}

VariableDefinitionStatementData::VariableDefinitionStatementData(
    VariableDefinitionPtr body)
    : body_(std::move(body))
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

ExpressionStatementData::ExpressionStatementData(ExpressionPtr body)
    : body_(std::move(body))
{}

AssignExpressionData::AssignExpressionData(
    OrExpressionPtr lhs, OrExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

AddAssignExpressionData::AddAssignExpressionData(
    OrExpressionPtr lhs, OrExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

SubtractAssignExpressionData::SubtractAssignExpressionData(
    OrExpressionPtr lhs, OrExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

MultiplyAssignExpressionData::MultiplyAssignExpressionData(
    OrExpressionPtr lhs, OrExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

DivideAssignExpressionData::DivideAssignExpressionData(
    OrExpressionPtr lhs, OrExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

ModuloAssignExpressionData::ModuloAssignExpressionData(
    OrExpressionPtr lhs, OrExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

OrExpressionData::OrExpressionData(
    AndExpressionPtr lhs, OrExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

AndExpressionData::AndExpressionData(
    ComparativeExpressionPtr lhs, AndExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

EqualExpressionData::EqualExpressionData(
    AdditiveExpressionPtr lhs, AdditiveExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

NotEqualExpressionData::NotEqualExpressionData(
    AdditiveExpressionPtr lhs, AdditiveExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

LessExpressionData::LessExpressionData(
    AdditiveExpressionPtr lhs, AdditiveExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

GreaterExpressionData::GreaterExpressionData(
    AdditiveExpressionPtr lhs, AdditiveExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

LessOrEqualExpressionData::LessOrEqualExpressionData(
    AdditiveExpressionPtr lhs, AdditiveExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

GreaterOrEqualExpressionData::GreaterOrEqualExpressionData(
    AdditiveExpressionPtr lhs, AdditiveExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

AddExpressionData::AddExpressionData(
    MultiplicativeExpressionPtr lhs, AdditiveExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

SubtractExpressionData::SubtractExpressionData(
    MultiplicativeExpressionPtr lhs, AdditiveExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

MultiplyExpressionData::MultiplyExpressionData(
    UnaryExpressionPtr lhs, MultiplicativeExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

DivideExpressionData::DivideExpressionData(
    UnaryExpressionPtr lhs, MultiplicativeExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

ModuloExpressionData::ModuloExpressionData(
    UnaryExpressionPtr lhs, MultiplicativeExpressionPtr rhs)
    : lhs_(std::move(lhs)),
      rhs_(std::move(rhs))
{}

NotExpressionData::NotExpressionData(UnaryExpressionPtr expression)
    : expression_(std::move(expression))
{}

MinusExpressionData::MinusExpressionData(UnaryExpressionPtr expression)
    : expression_(std::move(expression))
{}

FunctionCallExpressionData::FunctionCallExpressionData(
    IdentifierPtr function_name, ParameterListPtr parameter_list)
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

IdentifierExpressionData::IdentifierExpressionData(IdentifierPtr expression)
    : expression_(std::move(expression))
{}

IntegerLiteralExpressionData::IntegerLiteralExpressionData(
    IntegerLiteralPtr expression)
    : expression_(std::move(expression))
{}

CharacterLiteralExpressionData::CharacterLiteralExpressionData(
    CharacterLiteralPtr expression)
    : expression_(std::move(expression))
{}

StringLiteralExpressionData::StringLiteralExpressionData(
    StringLiteralPtr expression)
    : expression_(std::move(expression))
{}

}  // namespace ast
}  // namespace klang
