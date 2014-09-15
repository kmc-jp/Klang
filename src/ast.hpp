#ifndef KMC_KLANG_AST_HPP
#define KMC_KLANG_AST_HPP

#include "memory.hpp"

namespace klang {
namespace ast {

class Base;
class Identifier;
class Type;
class IntegerLiteral;
class CharacterLiteral;
class TranslationUnit;
class FunctionDefinition;
class ArgumentList;
class Argument;
class Statement;
class CompoundStatement;
class ExpressionStatement;
class VariableDefinitionStatement;
class VariableDefinition;
class IfStatement;
class WhileStatement;
class ForStatement;
class ReturnStatement;
class BreakStatement;
class ContinueStatement;
class Expression;
class AssignExpression;
class OrExpression;
class AndExpression;
class ComparativeExpression;
class AdditiveExpression;
class MultiplicativeExpression;
class UnaryExpression;
class PostfixExpression;
class ParameterList;
class Parameter;
class PrimaryExpression;

using BasePtr = std::unique_ptr<Base>;
using IdentifierPtr = std::unique_ptr<Identifier>;
using TypePtr = std::unique_ptr<Type>;
using IntegerLiteralPtr = std::unique_ptr<IntegerLiteral>;
using CharacterLiteralPtr = std::unique_ptr<CharacterLiteral>;
using TranslationUnitPtr = std::unique_ptr<TranslationUnit>;
using FunctionDefinitionPtr = std::unique_ptr<FunctionDefinition>;
using ArgumentListPtr = std::unique_ptr<ArgumentList>;
using ArgumentPtr = std::unique_ptr<Argument>;
using StatementPtr = std::unique_ptr<Statement>;
using CompoundStatementPtr = std::unique_ptr<CompoundStatement>;
using ExpressionStatementPtr = std::unique_ptr<ExpressionStatement>;
using VariableDefinitionStatementPtr =
    std::unique_ptr<VariableDefinitionStatement>;
using VariableDefinitionPtr = std::unique_ptr<VariableDefinition>;
using IfStatementPtr = std::unique_ptr<IfStatement>;
using WhileStatementPtr = std::unique_ptr<WhileStatement>;
using ForStatementPtr = std::unique_ptr<ForStatement>;
using ReturnStatementPtr = std::unique_ptr<ReturnStatement>;
using BreakStatementPtr = std::unique_ptr<BreakStatement>;
using ContinueStatementPtr = std::unique_ptr<ContinueStatement>;
using ExpressionPtr = std::unique_ptr<Expression>;
using AssignExpressionPtr = std::unique_ptr<AssignExpression>;
using OrExpressionPtr = std::unique_ptr<OrExpression>;
using AndExpressionPtr = std::unique_ptr<AndExpression>;
using ComparativeExpressionPtr = std::unique_ptr<ComparativeExpression>;
using AdditiveExpressionPtr = std::unique_ptr<AdditiveExpression>;
using MultiplicativeExpressionPtr = std::unique_ptr<MultiplicativeExpression>;
using UnaryExpressionPtr = std::unique_ptr<UnaryExpression>;
using PostfixExpressionPtr = std::unique_ptr<PostfixExpression>;
using ParameterListPtr = std::unique_ptr<ParameterList>;
using ParameterPtr = std::unique_ptr<Parameter>;
using PrimaryExpressionPtr = std::unique_ptr<PrimaryExpression>;

class Base {
 public:
  virtual ~Base() = 0;
};

class Identifier : public Base {
 public:
  virtual ~Identifier() = 0;
};

class Type : public Base {
 public:
  virtual ~Type() = 0;
};

class IntegerLiteral : public Base {
 public:
  virtual ~IntegerLiteral() = 0;
};

class CharacterLiteral : public Base {
 public:
  virtual ~CharacterLiteral() = 0;
};

class TranslationUnit : public Base {
 public:
  virtual ~TranslationUnit() = 0;
};

class FunctionDefinition : public Base {
 public:
  virtual ~FunctionDefinition() = 0;
};

class ArgumentList : public Base {
 public:
  virtual ~ArgumentList() = 0;
};

class Argument : public Base {
 public:
  virtual ~Argument() = 0;
};

class Statement : public Base {
 public:
  virtual ~Statement() = 0;
};

class CompoundStatement : public Statement {
 public:
  virtual ~CompoundStatement() = 0;
};

class ExpressionStatement : public Statement {
 public:
  virtual ~ExpressionStatement() = 0;
};

class VariableDefinitionStatement : public Statement {
 public:
  virtual ~VariableDefinitionStatement() = 0;
};

class VariableDefinition : public Base {
 public:
  virtual ~VariableDefinition() = 0;
};

class IfStatement : public Statement {
 public:
  virtual ~IfStatement() = 0;
};

class WhileStatement : public Statement {
 public:
  virtual ~WhileStatement() = 0;
};

class ForStatement : public Statement {
 public:
  virtual ~ForStatement() = 0;
};

class ReturnStatement : public Statement {
 public:
  virtual ~ReturnStatement() = 0;
};

class BreakStatement : public Statement {
 public:
  virtual ~BreakStatement() = 0;
};

class ContinueStatement : public Statement {
 public:
  virtual ~ContinueStatement() = 0;
};

class Expression : public Base {
 public:
  virtual ~Expression() = 0;
};

class AssignExpression : public Expression {
 public:
  virtual ~AssignExpression() = 0;
};

class OrExpression : public AssignExpression {
 public:
  virtual ~OrExpression() = 0;
};

class AndExpression : public OrExpression {
 public:
  virtual ~AndExpression() = 0;
};

class ComparativeExpression : public AndExpression {
 public:
  virtual ~ComparativeExpression() = 0;
};

class AdditiveExpression : public ComparativeExpression {
 public:
  virtual ~AdditiveExpression() = 0;
};

class MultiplicativeExpression : public AdditiveExpression {
 public:
  virtual ~MultiplicativeExpression() = 0;
};

class UnaryExpression : public MultiplicativeExpression {
 public:
  virtual ~UnaryExpression() = 0;
};

class PostfixExpression : public UnaryExpression {
 public:
  virtual ~PostfixExpression() = 0;
};

class ParameterList : public Base {
 public:
  virtual ~ParameterList() = 0;
};

class Parameter : public Base {
 public:
  virtual ~Parameter() = 0;
};

class PrimaryExpression : public PostfixExpression {
 public:
  virtual ~PrimaryExpression() = 0;
};

}  // namespace ast
}  // namespace klang

#endif  // KMC_KLANG_AST_HPP
