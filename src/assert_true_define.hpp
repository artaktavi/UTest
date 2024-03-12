#ifndef UNITTESTER_ASSERT_TRUE_DEFINE_HPP
#define UNITTESTER_ASSERT_TRUE_DEFINE_HPP

#define ASSERT_TRUE(statement)                                                 \
  int line = __LINE__;                                                         \
  try {                                                                        \
    if (statement) {                                                           \
      UpdateStatus(CommandStatus("assert_true", line, #statement, "succeed")); \
    } else {                                                                   \
      UpdateStatus(                                                            \
          CommandStatus("assert_true", line, #statement, "fatal_failed"));     \
      return;                                                                  \
    }                                                                          \
  } catch (...) {                                                              \
    UpdateStatus(CommandStatus("assert_true", line, #statement,                \
                               "fatal_failed_exception"));                     \
    return;                                                                    \
  }

#endif  //UNITTESTER_ASSERT_TRUE_DEFINE_HPP
