#ifndef UNITTESTER_EXPECT_TRUE_DEFINE_HPP
#define UNITTESTER_EXPECT_TRUE_DEFINE_HPP

#define EXPECT_TRUE(statement)                                              \
  line_temp_ = __LINE__;                                                    \
  try {                                                                     \
    if (statement) {                                                        \
      UpdateStatus(                                                         \
          CommandStatus("EXPECT_TRUE", line_temp_, #statement, "succeed")); \
    } else {                                                                \
      UpdateStatus(                                                         \
          CommandStatus("EXPECT_TRUE", line_temp_, #statement, "failed"));  \
    }                                                                       \
  } catch (...) {                                                           \
    UpdateStatus(CommandStatus("EXPECT_TRUE", line_temp_, #statement,       \
                               "failed_exception"));                        \
  }

#endif  //UNITTESTER_EXPECT_TRUE_DEFINE_HPP
