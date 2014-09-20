#include "ast.hpp"

namespace klang {
namespace ast {

Base::~Base()
{};

Identifier::~Identifier()
{};

Type::~Type()
{};

IntegerLiteral::~IntegerLiteral()
{};

CharacterLiteral::~CharacterLiteral()
{};

StringLiteral::~StringLiteral()
{};

TranslationUnit::~TranslationUnit()
{};

FunctionDefinition::~FunctionDefinition()
{};

ArgumentList::~ArgumentList()
{};

Argument::~Argument()
{};

Statement::~Statement()
{};

CompoundStatement::~CompoundStatement()
{};

ExpressionStatement::~ExpressionStatement()
{};

VariableDefinitionStatement::~VariableDefinitionStatement()
{};

VariableDefinition::~VariableDefinition()
{};

IfStatement::~IfStatement()
{};

WhileStatement::~WhileStatement()
{};

ForStatement::~ForStatement()
{};

ReturnStatement::~ReturnStatement()
{};

BreakStatement::~BreakStatement()
{};

ContinueStatement::~ContinueStatement()
{};

Expression::~Expression()
{};

AssignExpression::~AssignExpression()
{};

OrExpression::~OrExpression()
{};

AndExpression::~AndExpression()
{};

ComparativeExpression::~ComparativeExpression()
{};

AdditiveExpression::~AdditiveExpression()
{};

MultiplicativeExpression::~MultiplicativeExpression()
{};

UnaryExpression::~UnaryExpression()
{};

PostfixExpression::~PostfixExpression()
{};

ParameterList::~ParameterList()
{};

Parameter::~Parameter()
{};

PrimaryExpression::~PrimaryExpression()
{};

}  // namespace ast
}  // namespace klang