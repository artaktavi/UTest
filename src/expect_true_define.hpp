#ifndef UNITTESTER_EXPECT_TRUE_DEFINE_HPP
#define UNITTESTER_EXPECT_TRUE_DEFINE_HPP

#define EXPECT_TRUE(statement)                                                 \
  int line = __LINE__;                                                         \
  try {                                                                        \
    if (statement) {                                                           \
      UpdateStatus(CommandStatus("expect_true", line, #statement, "succeed")); \
    } else {                                                                   \
      UpdateStatus(CommandStatus("expect_true", line, #statement, "failed"));  \
    }                                                                          \
  } catch (...) {                                                              \
    UpdateStatus(                                                              \
        CommandStatus("expect_true", line, #statement, "failed_exception"));   \
  }

#endif  //UNITTESTER_EXPECT_TRUE_DEFINE_HPP
