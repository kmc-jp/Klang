#include "ast.hpp"

namespace klang {
namespace ast {

Base::~Base()
{}

Identifier::~Identifier()
{}

Type::~Type()
{}

IntegerLiteral::~IntegerLiteral()
{}

CharacterLiteral::~CharacterLiteral()
{}

StringLiteral::~StringLiteral()
{}

TranslationUnit::~TranslationUnit()
{}

FunctionDefinition::~FunctionDefinition()
{}

ArgumentList::~ArgumentList()
{}

Argument::~Argument()
{}

Statement::~Statement()
{}

CompoundStatement::~CompoundStatement()
{}

ElseStatement::~ElseStatement()
{}

IfStatement::~IfStatement()
{}

WhileStatement::~WhileStatement()
{}

ForStatement::~ForStatement()
{}

ReturnStatement::~ReturnStatement()
{}

BreakStatement::~BreakStatement()
{}

ContinueStatement::~ContinueStatement()
{}

VariableDefinitionStatement::~VariableDefinitionStatement()
{}

VariableDefinition::~VariableDefinition()
{}

ExpressionStatement::~ExpressionStatement()
{}

Expression::~Expression()
{}

AssignExpression::~AssignExpression()
{}

OrExpression::~OrExpression()
{}

AndExpression::~AndExpression()
{}

ComparativeExpression::~ComparativeExpression()
{}

AdditiveExpression::~AdditiveExpression()
{}

MultiplicativeExpression::~MultiplicativeExpression()
{}

UnaryExpression::~UnaryExpression()
{}

PostfixExpression::~PostfixExpression()
{}

FunctionCallExpression::~FunctionCallExpression()
{}

ParameterList::~ParameterList()
{}

Parameter::~Parameter()
{}

PrimaryExpression::~PrimaryExpression()
{}

}  // namespace ast
}  // namespace klang
