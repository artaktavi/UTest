#pragma once

#include <KeyWordsDefine.hpp>

#define EXPECT_TRUE(statement)                                          \
  line_temp_ = __LINE__;                                                \
  try {                                                                 \
    if (statement) {                                                    \
      UpdateStatus(CommandStatus("EXPECT_TRUE", line_temp_, #statement, \
                                 KEYWORD_PASSED));                      \
    } else {                                                            \
      UpdateStatus(CommandStatus("EXPECT_TRUE", line_temp_, #statement, \
                                 KEYWORD_FAILED));                      \
    }                                                                   \
  } catch (...) {                                                       \
    UpdateStatus(CommandStatus("EXPECT_TRUE", line_temp_, #statement,   \
                               KEYWORD_EXCEPTION_FAILED));              \
  }
