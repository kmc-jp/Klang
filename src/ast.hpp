#ifndef KMC_KLANG_AST_HPP
#define KMC_KLANG_AST_HPP

#include <memory>

namespace klang {

class BaseAst;
class IdentifierAst;
class TypeAst;
class IntegerLiteralAst;
class ProgramAst;
class FunctionDefinitionAst;
class ArgumentListAst;
class ArgumentAst;
class StatementAst;
class CompoundStatementAst;
class ExpressionStatementAst;
class VariableDefinitionStatementAst;
class VariableDefinitionAst;
class IfStatementAst;
class WhileStatementAst;
class ForStatementAst;
class ReturnStatementAst;
class BreakStatementAst;
class ContinueStatementAst;
class ExpressionAst;
class AssignExpressionAst;
class OrExpressionAst;
class AndExpressionAst;
class ComparativeExpressionAst;
class AdditiveExpressionAst;
class MultiplicativeExpressionAst;
class UnaryExpressionAst;
class PostfixExpressionAst;
class ParameterListAst;
class ParameterAst;
class PrimaryExpressionAst;

using AstPtr = std::unique_ptr<BaseAst>;
using IdentifierPtr = std::unique_ptr<IdentifierAst>;
using TypePtr = std::unique_ptr<TypeAst>;
using IntegerLiteralPtr = std::unique_ptr<IntegerLiteralAst>;
using ProgramPtr = std::unique_ptr<ProgramAst>;
using FunctionDefinitionPtr = std::unique_ptr<FunctionDefinitionAst>;
using ArgumentListPtr = std::unique_ptr<ArgumentListAst>;
using ArgumentPtr = std::unique_ptr<ArgumentAst>;
using StatementPtr = std::unique_ptr<StatementAst>;
using CompoundStatementPtr = std::unique_ptr<CompoundStatementAst>;
using ExpressionStatementPtr = std::unique_ptr<ExpressionStatementAst>;
using VariableDefinitionStatementPtr =
    std::unique_ptr<VariableDefinitionStatementAst>;
using VariableDefinitionPtr = std::unique_ptr<VariableDefinitionAst>;
using IfStatementPtr = std::unique_ptr<IfStatementAst>;
using WhileStatementPtr = std::unique_ptr<WhileStatementAst>;
using ForStatementPtr = std::unique_ptr<ForStatementAst>;
using ReturnStatementPtr = std::unique_ptr<ReturnStatementAst>;
using BreakStatementPtr = std::unique_ptr<BreakStatementAst>;
using ContinueStatementPtr = std::unique_ptr<ContinueStatementAst>;
using ExpressionPtr = std::unique_ptr<ExpressionAst>;
using AssignExpressionPtr = std::unique_ptr<AssignExpressionAst>;
using OrExpressionPtr = std::unique_ptr<OrExpressionAst>;
using AndExpressionPtr = std::unique_ptr<AndExpressionAst>;
using ComparativeExpressionPtr = std::unique_ptr<ComparativeExpressionAst>;
using AdditiveExpressionPtr = std::unique_ptr<AdditiveExpressionAst>;
using MultiplicativeExpressionPtr =
    std::unique_ptr<MultiplicativeExpressionAst>;
using UnaryExpressionPtr = std::unique_ptr<UnaryExpressionAst>;
using PostfixExpressionPtr = std::unique_ptr<PostfixExpressionAst>;
using ParameterListPtr = std::unique_ptr<ParameterListAst>;
using ParameterPtr = std::unique_ptr<ParameterAst>;
using PrimaryExpressionPtr = std::unique_ptr<PrimaryExpressionAst>;

class BaseAst {
 public:
  virtual ~BaseAst() = 0;
};

class IdentifierAst : public BaseAst {
 public:
  virtual ~IdentifierAst() = 0;
};

class TypeAst : public BaseAst {
 public:
  virtual ~TypeAst() = 0;
};

class IntegerLiteralAst : public BaseAst {
 public:
  virtual ~IntegerLiteralAst() = 0;
};

class ProgramAst : public BaseAst {
 public:
  virtual ~ProgramAst() = 0;
};

class FunctionDefinitionAst : public BaseAst {
 public:
  virtual ~FunctionDefinitionAst() = 0;
};

class ArgumentListAst : public BaseAst {
 public:
  virtual ~ArgumentListAst() = 0;
};

class ArgumentAst : public BaseAst {
 public:
  virtual ~ArgumentAst() = 0;
};

class StatementAst : public BaseAst {
 public:
  virtual ~StatementAst() = 0;
};

class CompoundStatementAst : public StatementAst {
 public:
  virtual ~CompoundStatementAst() = 0;
};

class ExpressionStatementAst : public StatementAst {
 public:
  virtual ~ExpressionStatementAst() = 0;
};

class VariableDefinitionStatementAst : public StatementAst {
 public:
  virtual ~VariableDefinitionStatementAst() = 0;
};

class VariableDefinitionAst : public BaseAst {
 public:
  virtual ~VariableDefinitionAst() = 0;
};

class IfStatementAst : public StatementAst {
 public:
  virtual ~IfStatementAst() = 0;
};

class WhileStatementAst : public StatementAst {
 public:
  virtual ~WhileStatementAst() = 0;
};

class ForStatementAst : public StatementAst {
 public:
  virtual ~ForStatementAst() = 0;
};

class ReturnStatementAst : public StatementAst {
 public:
  virtual ~ReturnStatementAst() = 0;
};

class BreakStatementAst : public StatementAst {
 public:
  virtual ~BreakStatementAst() = 0;
};

class ContinueStatementAst : public StatementAst {
 public:
  virtual ~ContinueStatementAst() = 0;
};

class ExpressionAst : public BaseAst {
 public:
  virtual ~ExpressionAst() = 0;
};

class AssignExpressionAst : public ExpressionAst {
 public:
  virtual ~AssignExpressionAst() = 0;
};

class OrExpressionAst : public AssignExpressionAst {
 public:
  virtual ~OrExpressionAst() = 0;
};

class AndExpressionAst : public OrExpressionAst {
 public:
  virtual ~AndExpressionAst() = 0;
};

class ComparativeExpressionAst : public AndExpressionAst {
 public:
  virtual ~ComparativeExpressionAst() = 0;
};

class AdditiveExpressionAst : public ComparativeExpressionAst {
 public:
  virtual ~AdditiveExpressionAst() = 0;
};

class MultiplicativeExpressionAst : public AdditiveExpressionAst {
 public:
  virtual ~MultiplicativeExpressionAst() = 0;
};

class UnaryExpressionAst : public MultiplicativeExpressionAst {
 public:
  virtual ~UnaryExpressionAst() = 0;
};

class PostfixExpressionAst : public UnaryExpressionAst {
 public:
  virtual ~PostfixExpressionAst() = 0;
};

class ParameterListAst : public BaseAst {
 public:
  virtual ~ParameterListAst() = 0;
};

class ParameterAst : public BaseAst {
 public:
  virtual ~ParameterAst() = 0;
};

class PrimaryExpressionAst : public PostfixExpressionAst {
 public:
  virtual ~PrimaryExpressionAst() = 0;
};

}  // namespace klang

#endif  // KMC_KLANG_AST_HPP
