AM_CXXFLAGS = -O2 -std=c++11 -Wall -Wextra @LLVM_CPPFLAGS@

LDADD = @LLVM_LDFLAGS@ @CURSES_LIB@

bin_PROGRAMS = klang
klang_SOURCES = main.cpp
klang_LDADD = -L./ -lcodegen -lc++ @LLVM_LDFLAGS@ @CURSES_LIB@

noinst_LIBRARIES = liblexer.a libastdata.a libparser.a libcodegen.a
liblexer_a_SOURCES = lexer.cpp lexer.hpp
libastdata_a_SOURCES = memory.hpp ast.hpp ast.cpp ast_data.hpp ast_data.cpp
libparser_a_SOURCES = memory.hpp ast.hpp ast.cpp ast_data.hpp ast_data.cpp parser.hpp parser.cpp
libcodegen_a_SOURCES = codegen.hpp codegen.cpp
