#pragma once

#include <KeyWordsDefine.hpp>

#define EXPECT_TRUE(statement)                                                \
  try {                                                                       \
    if (statement) {                                                          \
      UpdateStatus(CommandStatus("EXPECT_TRUE", __LINE__, __FILE__,           \
                                 #statement, KEYWORD_PASSED));                \
    } else {                                                                  \
      UpdateStatus(CommandStatus("EXPECT_TRUE", __LINE__, __FILE__,           \
                                 #statement, KEYWORD_FAILED));                \
    }                                                                         \
  } catch (...) {                                                             \
    UpdateStatus(CommandStatus("EXPECT_TRUE", __LINE__, __FILE__, #statement, \
                               KEYWORD_EXCEPTION_FAILED));                    \
  }
