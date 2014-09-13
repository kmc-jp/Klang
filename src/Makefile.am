AM_CXXFLAGS = -O2 -std=c++11 -Wall -Wextra

bin_PROGRAMS = klang
klang_SOURCES = main.cpp

noinst_LIBRARIES = liblexer.a libastdata.a libparser.a
liblexer_a_SOURCES = lexer.cpp lexer.hpp
libastdata_a_SOURCES = memory.hpp ast.hpp ast_data.cpp ast_data.hpp
libparser_a_SOURCES = ast_data.hpp parser.cpp parser.hpp
