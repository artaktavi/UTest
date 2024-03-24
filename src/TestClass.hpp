#pragma once

#include <iostream>
#include <algorithm>
#include <set>

#include <TestStatus.hpp>

class Test {
 private:
  std::string name_;
  std::string group_;
  std::vector<CommandStatus>* commands_vec_ = nullptr;
  bool is_passed_temp_ = true;
  virtual void TestBody() = 0;

 protected:
  int line_temp_ = 0;  // necessary for memorization of __LINE__ in commands
  static const std::set<std::string> FAILED_STRINGS;
  void UpdateStatus(const CommandStatus& command_result) {
    if (FAILED_STRINGS.find(command_result.result) != FAILED_STRINGS.end()) {
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

const std::set<std::string> Test::FAILED_STRINGS = {
    "failed", "failed_exception", "fatal_failed", "fatal_failed_exception"};
