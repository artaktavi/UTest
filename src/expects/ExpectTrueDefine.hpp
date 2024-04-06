#pragma once

#include <KeyWordsDefine.hpp>

#define EXPECT_TRUE(statement)                                              \
  try {                                                                     \
    if (statement) {                                                        \
      UpdateStatus(UTest::CommandStatus("EXPECT_TRUE", __LINE__, __FILE__,  \
                                        #statement, UTEST_KEYWORD_PASSED)); \
    } else {                                                                \
      UpdateStatus(UTest::CommandStatus("EXPECT_TRUE", __LINE__, __FILE__,  \
                                        #statement, UTEST_KEYWORD_FAILED)); \
    }                                                                       \
  } catch (...) {                                                           \
    UpdateStatus(UTest::CommandStatus("EXPECT_TRUE", __LINE__, __FILE__,    \
                                      #statement,                           \
                                      UTEST_KEYWORD_EXCEPTION_FAILED));     \
  }
