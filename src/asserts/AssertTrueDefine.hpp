#pragma once

#include <KeyWordsDefine.hpp>

#define ASSERT_TRUE(statement)                                                \
  try {                                                                       \
    if (statement) {                                                          \
      UpdateStatus(UTest::CommandStatus("ASSERT_TRUE", __LINE__, __FILE__,    \
                                        #statement, UTEST_KEYWORD_PASSED));   \
    } else {                                                                  \
      UpdateStatus(UTest::CommandStatus("ASSERT_TRUE", __LINE__, __FILE__,    \
                                        #statement,                           \
                                        UTEST_KEYWORD_FATAL_FAILED));         \
      return;                                                                 \
    }                                                                         \
  } catch (...) {                                                             \
    UpdateStatus(UTest::CommandStatus("ASSERT_TRUE", __LINE__, __FILE__,      \
                                      #statement,                             \
                                      UTEST_KEYWORD_EXCEPTION_FATAL_FAILED)); \
    return;                                                                   \
  }
