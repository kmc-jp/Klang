GTEST_DIR = gtest
GTEST_FLAGS = -I $(GTEST_DIR) -pthread -isystem
AM_CXXFLAGS = -O2 -std=c++11 -Wall -Wextra -I../src $(GTEST_FLAGS)

check_LIBRARIES = libhelperlexer.a libgtest-all.a
libhelperlexer_a_SOURCES = helper_lexer.hpp helper_lexer.cpp
libgtest_all_a_SOURCES = $(GTEST_DIR)/gtest-all.cc $(GTEST_DIR)/gtest.h

GTEST_FILES = helper_test_main.cpp $(GTEST_DIR)/gtest.h

TESTS = test_nothing test_sample1 test_lexer test_lexer_fail test_parser test_either
XFAIL_TESTS = test_lexer_fail

check_PROGRAMS = $(TESTS)
test_nothing_SOURCES = test_nothing.cpp # not using gtest
test_sample1_SOURCES = test_sample1.cpp $(GTEST_FILES) # using gtest
test_sample1_LDADD = libgtest-all.a

test_lexer_SOURCES = test_lexer.cpp $(GTEST_FILES)
test_lexer_LDADD = $(check_LIBRARIES) ../src/liblexer.a

test_lexer_fail_SOURCES = test_lexer_fail.cpp $(GTEST_FILES)
test_lexer_fail_LDADD = $(check_LIBRARIES) ../src/liblexer.a

test_parser_SOURCES = test_parser.cpp $(GTEST_FILES)
test_parser_LDADD = $(check_LIBRARIES) ../src/libparser.a ../src/liblexer.a

test_either_SOURCES = test_either.cpp $(GTEST_FILES)
test_either_LDADD = $(check_LIBRARIES)
