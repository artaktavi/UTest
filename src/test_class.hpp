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
#include <chrono>
#include <set>
#include <vector>

class Test {
 private:
  std::string name_;
  std::string group_;
  std::vector<CommandStatus>* commands_vec_ = nullptr;
  bool is_passed_temp_ = true;
  virtual void TestBody() = 0;

 protected:
  int line_temp_ = 0;  // necessary for memorization of __LINE__ in commands
  static const std::set<std::string> failed_strings;
  void UpdateStatus(const CommandStatus& command_result) {
    //    std::cout << "Command type: " << command_result.type << '\n'
    //              << "Command arg_1: " << command_result.arg_1 << '\n'
    //              << "Command arg_2: " << command_result.arg_2 << '\n'
    //              << "Result: " << command_result.result << '\n'
    //              << "Line: " << command_result.line << std::endl;
    if (failed_strings.find(command_result.result) != failed_strings.end()) {
      is_passed_temp_ = false;
    }
    if (commands_vec_ == nullptr) {
      std::cerr << "Test : UpdateStatus : no vector to push command status";
    } else {
      commands_vec_->push_back(command_result);
    }
  }
  Test(std::string name, std::string group)
      : name_(std::move(name)), group_(std::move(group)) {}

 public:
  Test(const Test& other) = delete;
  TestStatus Execute() {
    is_passed_temp_ = true;
    TestStatus answer(name_, group_);
    commands_vec_ = &answer.commands_history;
    const auto start_time = std::chrono::high_resolution_clock::now();
    TestBody();
    const auto stop_time = std::chrono::high_resolution_clock::now();
    answer.execution_time = stop_time - start_time;
    answer.result = is_passed_temp_ ? "succeed" : "failed";
    commands_vec_ = nullptr;
    return answer;
  }
};

const std::set<std::string> Test::failed_strings = {
    "failed", "failed_exception", "fatal_failed", "fatal_failed_exception"};

#endif  //UNITTESTER_TEST_CLASS_HPP
