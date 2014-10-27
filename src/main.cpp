#include <llvm/Support/CommandLine.h>

#include <llvm/Support/Debug.h>
#include <llvm/Support/PrettyStackTrace.h>
#include <llvm/Support/Signals.h>

#include <fstream>
#include <iostream>
#include <string>

#include "config.h"

#include "codegen.hpp"
#include "lexer.hpp"
#include "parser.hpp"

namespace /* unnamed namespace */ {
  llvm::cl::opt<std::string> OutputFile("o",
                                        llvm::cl::desc("<output file>"),
                                        llvm::cl::value_desc("filename"),
                                        llvm::cl::init("a.out"));
  llvm::cl::opt<std::string> InputFile(llvm::cl::Positional,
                                       llvm::cl::desc("<input file>"),
                                       llvm::cl::value_desc("filename"),
                                       llvm::cl::Required);
} // unnamed namespace

int main(int argc, char** argv) {
  llvm::sys::PrintStackTraceOnErrorSignal();
  llvm::PrettyStackTraceProgram X(argc, argv);
  llvm::EnableDebugBuffering = true;

  llvm::cl::SetVersionPrinter([](){ std::cout << PACKAGE_STRING << std::endl; });
  llvm::cl::ParseCommandLineOptions(argc, argv, "Command Line");

  std::cout << "Out :" << OutputFile << std::endl;
  std::cout << "In  :" << InputFile << std::endl;

  std::ifstream src(InputFile);
  if(!src.good()){
    std::cerr << "input file not exists" << std::endl;
    exit(-1);
  }
  bool success;
  klang::TokenVector tokens;
  std::tie(success, tokens) = klang::tokenize(src);
  if(!success) {
    std::cout << "someting wrong" << std::endl;
    if(tokens.size() != 0){
      std::cout << "near " << tokens[tokens.size()-1].str() << std::endl; // helper_lexer のshow 系をもってきても良いかもしれない
    } else {
      std::cout << "near first token" << std::endl;
    }
    exit(1);
  }

  klang::Parser parser(tokens);
  auto parse_translation_unit = parser.parse_translation_unit();
  if(parse_translation_unit == nullptr){
    std::cerr << "parse fail" << std::endl;
    exit(2);
  }

  klang::Codegen generator(std::move(parse_translation_unit));

  auto const& module = generator.gen();

  module->dump();
  return 0;
}
