#ifndef UNITTESTER_TEST_CLASS_HPP
#define UNITTESTER_TEST_CLASS_HPP

#ifndef UNITTESTER_COMMAND_STATUS_CLASS_HPP
#include "command_status_class.hpp"
#endif

#ifndef UNITTESTER_TEST_STATUS_CLASS_HPP
#include "test_status_class.hpp"
#endif

// TEST INCLUDE
//#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

class Test {
 private:
  virtual void TestBody() = 0;
  std::vector<CommandStatus> command_history_;
  bool is_passed_ = true;

 protected:
  void UpdateStatus(CommandStatus command_result) {
    //    std::cout << "Command type: " << command_result.type << '\n'
    //              << "Command arg_1: " << command_result.arg_1 << '\n'
    //              << "Command arg_2: " << command_result.arg_2 << '\n'
    //              << "Result: " << command_result.result << '\n'
    //              << "Line: " << command_result.line << std::endl;
    if (failed_strings.find(command_result.result) != failed_strings.end()) {
      is_passed_ = false;
    }
    command_history_.push_back(command_result);
  }

 public:
  static const std::set<std::string> failed_strings;
  virtual TestStatus Execute() final {
    TestBody();
    return TestStatus(command_history_, is_passed_ ? "succeed" : "failed");
  }
  Test() = default;
  Test(const Test& other) = delete;
};

const std::set<std::string> Test::failed_strings = {
    "failed", "failed_exception", "fatal_failed", "fatal_failed_exception"};

#endif  //UNITTESTER_TEST_CLASS_HPP
