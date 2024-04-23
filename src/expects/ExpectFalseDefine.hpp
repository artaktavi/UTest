#pragma once

#include <KeyWordsDefine.hpp>

#define EXPECT_FALSE(statement)                                             \
  try {                                                                     \
    if (!(statement)) {                                                     \
      UpdateStatus(UTest::CommandStatus("EXPECT_FALSE", __LINE__, __FILE__, \
                                        #statement, UTEST_KEYWORD_PASSED)); \
    } else {                                                                \
      UpdateStatus(UTest::CommandStatus("EXPECT_FALSE", __LINE__, __FILE__, \
                                        #statement, UTEST_KEYWORD_FAILED)); \
    }                                                                       \
  } catch (...) {                                                           \
    UpdateStatus(UTest::CommandStatus("EXPECT_FALSE", __LINE__, __FILE__,   \
                                      #statement,                           \
                                      UTEST_KEYWORD_EXCEPTION_FAILED));     \
    throw;                                                                  \
  }
