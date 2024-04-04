#pragma once

#include <KeyWordsDefine.hpp>

#define ASSERT_TRUE(statement)                                               \
  line_temp_ = __LINE__;                                                     \
  try {                                                                      \
    if (statement) {                                                         \
      UpdateStatus(CommandStatus("ASSERT_TRUE", line_temp_, __FILE__,        \
                                 #statement, KEYWORD_PASSED));               \
    } else {                                                                 \
      UpdateStatus(CommandStatus("ASSERT_TRUE", line_temp_, __FILE__,        \
                                 #statement, KEYWORD_FATAL_FAILED));         \
      return;                                                                \
    }                                                                        \
  } catch (...) {                                                            \
    UpdateStatus(CommandStatus("ASSERT_TRUE", line_temp_, __FILE__,          \
                               #statement, KEYWORD_EXCEPTION_FATAL_FAILED)); \
    return;                                                                  \
  }
