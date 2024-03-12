#ifndef UNITTESTER_ASSERT_TRUE_DEFINE_HPP
#define UNITTESTER_ASSERT_TRUE_DEFINE_HPP

#define ASSERT_TRUE(statement)                                              \
  line_temp_ = __LINE__;                                                    \
  try {                                                                     \
    if (statement) {                                                        \
      UpdateStatus(                                                         \
          CommandStatus("assert_true", line_temp_, #statement, "succeed")); \
    } else {                                                                \
      UpdateStatus(CommandStatus("assert_true", line_temp_, #statement,     \
                                 "fatal_failed"));                          \
      return;                                                               \
    }                                                                       \
  } catch (...) {                                                           \
    UpdateStatus(CommandStatus("assert_true", line_temp_, #statement,       \
                               "fatal_failed_exception"));                  \
    return;                                                                 \
  }

#endif  //UNITTESTER_ASSERT_TRUE_DEFINE_HPP
