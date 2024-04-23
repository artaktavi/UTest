#pragma once

#include <KeyWordsDefine.hpp>

#define EXPECT_EQUAL(left, right)                                              \
  try {                                                                        \
    if (left == right) {                                                       \
      UpdateStatus(UTest::CommandStatus("EXPECT_EQUAL", __LINE__, __FILE__,    \
                                        #left, #right, UTEST_KEYWORD_PASSED)); \
    } else {                                                                   \
      UpdateStatus(UTest::CommandStatus("EXPECT_EQUAL", __LINE__, __FILE__,    \
                                        #left, #right, UTEST_KEYWORD_FAILED)); \
    }                                                                          \
  } catch (...) {                                                              \
    UpdateStatus(UTest::CommandStatus("EXPECT_EQUAL", __LINE__, __FILE__,      \
                                      #left, #right,                           \
                                      UTEST_KEYWORD_EXCEPTION_FAILED));        \
    throw;                                                                     \
  }
