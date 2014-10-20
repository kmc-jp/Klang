#include <llvm/Support/CommandLine.h>

#include <iostream>
#include <string>

#include "config.h"

namespace /* unnamed namespace */ {
  using namespace llvm::cl;
  llvm::cl::opt<std::string> OutputFile("o", desc("Optput file name"),
                                        value_desc("filename"), init("a.out"));
} // unnamed namespace

int main(int argc, char** argv) {
  SetVersionPrinter([](){ std::cout << PACKAGE_STRING << std::endl; });
  llvm::cl::ParseCommandLineOptions(argc, argv, "CL");

  std::cout << OutputFile << std::endl;

  return 0;
}
