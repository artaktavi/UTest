#pragma once

#include <KeyWordsDefine.hpp>

#define ASSERT_EQUAL(left, right)                                              \
  try {                                                                        \
    if (left == right) {                                                       \
      UpdateStatus(UTest::CommandStatus("ASSERT_EQUAL", __LINE__, __FILE__,    \
                                        #left, #right, UTEST_KEYWORD_PASSED)); \
    } else {                                                                   \
      UpdateStatus(UTest::CommandStatus("ASSERT_EQUAL", __LINE__, __FILE__,    \
                                        #left, #right,                         \
                                        UTEST_KEYWORD_FATAL_FAILED));          \
      return;                                                                  \
    }                                                                          \
  } catch (...) {                                                              \
    UpdateStatus(UTest::CommandStatus("ASSERT_EQUAL", __LINE__, __FILE__,      \
                                      #left, #right,                           \
                                      UTEST_KEYWORD_EXCEPTION_FATAL_FAILED));  \
    return;                                                                    \
  }
