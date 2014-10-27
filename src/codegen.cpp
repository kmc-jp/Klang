#include "codegen.hpp"

#include <llvm/IR/LLVMContext.h>

#include "ast_data.hpp"

namespace klang {

Codegen::Codegen(ast::TranslationUnitPtr&& tup): tup_(std::move(tup)) {}

std::unique_ptr<llvm::Module> Codegen::gen() {
  using std::begin;
  using std::end;
  llvm::LLVMContext& context = llvm::getGlobalContext();
  std::unique_ptr<llvm::Module> module(new llvm::Module("top", context));
  llvm::IRBuilder<> builder(context);

  auto tuD = dynamic_cast<klang::ast::TranslationUnitData*>(tup_.get());
  assert(tuD != nullptr);
  auto const& funcs = tuD->functions();
  for(auto it = begin(funcs); it != end(funcs); ++it){
    klang::ast::FunctionDefinitionData* fdD = dynamic_cast<klang::ast::FunctionDefinitionData*>(it->get());
    assert(fuD != nullptr);
    std::unique_ptr<llvm::FunctionType> funcType = get_func_type(builder,
                                                                 fdD->return_type(),
                                                                 fdD->arguments());
    auto const& idPtr = fdD->function_name();
    auto idD = dynamic_cast<klang::ast::IdentifierData*>(idPtr.get());
    assert(idD != nullptr);
    std::string functionName = idD->identifier_name();
    auto func = llvm::Function::Create(funcType.get(),
                                       llvm::Function::ExternalLinkage,
                                       functionName,
                                       module.get());
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(context, "entry", func);
        builder.SetInsertPoint(block);
        llvm::Value* val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 42);
        builder.CreateRet(val);
    }
  }
  return module;
}

std::unique_ptr<llvm::FunctionType> Codegen::get_func_type(llvm::IRBuilder<>& builder,
                                                           ast::TypePtr const&,
                                                           ast::ArgumentListPtr const& arg){
  // Type はint しかない
  auto int32 = builder.getInt32Ty();
  auto alD = dynamic_cast<klang::ast::ArgumentListData*>(arg.get());
  assert(alD != nullptr);
  std::vector<llvm::Type*> argVec(alD->arguments().size(), int32); // alD->arguments() が最悪ポイント
  
  return std::unique_ptr<llvm::FunctionType>(
      llvm::FunctionType::get(int32, argVec, false)); // false: 全ての関数は可変長引数ではない
}

}  // namespace klang
