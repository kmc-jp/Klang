#ifndef KMC_KLANG_CODEGEN_HPP
#define KMC_KLANG_CODEGEN_HPP

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "memory.hpp"

#include "parser.hpp"

namespace klang {

class Codegen {
public:
  Codegen(ast::TranslationUnitPtr&&);
  std::unique_ptr<llvm::Module> gen();
private:
  ast::TranslationUnitPtr tup_;
  llvm::FunctionType* get_func_type(llvm::IRBuilder<>&,
                                    llvm::LLVMContext&,
                                    ast::TypePtr const&,
                                    ast::ArgumentListPtr const&);
};

}  // namespace klang

#endif  // KMC_KLANG_CODEGEN_HPP
