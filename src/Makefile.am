AM_CXXFLAGS = -O2 -std=c++11 -Wall -Wextra

bin_PROGRAMS = klang
klang_SOURCES = main.cpp

noinst_LIBRARIES = liblexer.a libastdata.a
liblexer_a_SOURCES = lexer.cpp lexer.hpp
libastdata_a_SOURCES = memory.hpp ast.hpp ast.cpp ast_data.cpp ast_data.hpp
