#include "codegen.hpp"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include "llvm/Support/Debug.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/TargetSelect.h"

#include <iostream>

int main(int argc, char** argv) {
  // llvm::InitializeNativeTarget();
  llvm::sys::PrintStackTraceOnErrorSignal();
  llvm::PrettyStackTraceProgram X(argc, argv);
  llvm::EnableDebugBuffering = true;

  llvm::LLVMContext& context = llvm::getGlobalContext();
  llvm::Module* module = new llvm::Module("top", context);
  llvm::IRBuilder<> builder(context);

  llvm::FunctionType* funcType =
      llvm::FunctionType::get(builder.getInt32Ty(), false);
  llvm::Function* mainFunc =
      llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

  llvm::Function* subFunc =
      llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "sub", module);

  llvm::BasicBlock* mainBlock =
      llvm::BasicBlock::Create(context, "entry", mainFunc);

  llvm::BasicBlock* subBlock =
      llvm::BasicBlock::Create(context, "entry", subFunc);

  {
      builder.SetInsertPoint(subBlock);
      llvm::Value* val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 42);
      builder.CreateRet(val);
  }
  {
      builder.SetInsertPoint(mainBlock);

      llvm::Value* payo = builder.CreateCall(subFunc, std::vector<llvm::Value*>(), "payo");

      builder.CreateRet(payo);
  }
  module->dump();

// klang::codegen::test();
  return 0;
}
