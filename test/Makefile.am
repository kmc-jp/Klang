GTEST_DIR = gtest
GTEST_FLAGS = -I $(GTEST_DIR) -pthread -isystem
AM_CXXFLAGS = -O2 -std=c++11 -Wall -Wextra -I../src $(GTEST_FLAGS)

noinst_LIBRARIES = libhelperlexer.a libgtest-all.a
libhelperlexer_a_SOURCES = helper_lexer.cpp helper_lexer.hpp
libgtest_all_a_SOURCES = $(GTEST_DIR)/gtest-all.cc $(GTEST_DIR)/gtest.h

TESTS = test_nothing test_sample1
check_PROGRAMS = $(TESTS)
test_nothing_SOURCES = test_nothing.cpp # not using gtest
test_sample1_SOURCES = test_sample1.cpp $(GTEST_DIR)/gtest.h # using gtest
test_sample1_LDADD = libgtest-all.a
