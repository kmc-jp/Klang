#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace klang {
namespace codegen {
  void test() {
    llvm::LLVMContext& context = llvm::getGlobalContext();
    llvm::Module* module = new llvm::Module("top", context);
    llvm::IRBuilder<> builder(context);

    llvm::FunctionType* funcType =
      llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function* mainFunc =
      llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

    module->dump();
  }
} // namespace codegen
} // namespace klang
