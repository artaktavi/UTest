#pragma once

#include <algorithm>
#include <iostream>
#include <set>

#include <KeyWordsDefine.hpp>
#include <TestIOManager.hpp>
#include <TestStatus.hpp>

namespace UTestInfrastructure {
class Test {
 private:
  std::string name_;
  std::string group_;
  uint32_t line_;
  std::string path_;
  std::vector<UTest::CommandStatus>* commands_vec_ = nullptr;
  bool is_passed_temp_ = true;
  virtual void TestBody() = 0;

 protected:
  static const std::set<std::string> FAILED_STRINGS;
  void UpdateStatus(const UTest::CommandStatus& command_result) {
    if (FAILED_STRINGS.find(command_result.result) != FAILED_STRINGS.end()) {
      is_passed_temp_ = false;
    }
    if (commands_vec_ == nullptr) {
      std::cerr << "Test : UpdateStatus : no vector to push command status\n";
    } else {
      commands_vec_->push_back(command_result);
    }
  }
  Test(std::string name, std::string group, uint32_t line, std::string path)
      : name_(std::move(name)),
        group_(std::move(group)),
        line_(line),
        path_(std::move(path)) {}

 public:
  Test(const Test& other) = delete;
  UTest::TestStatus Execute() {
    is_passed_temp_ = true;
    TestIOManager::OutputTestStart(group_, name_);
    UTest::TestStatus answer(name_, group_, line_, path_);
    commands_vec_ = &answer.commands_history;
    const auto start_time = std::chrono::high_resolution_clock::now();
    TestBody();
    const auto stop_time = std::chrono::high_resolution_clock::now();
    answer.execution_time = stop_time - start_time;
    answer.result =
        is_passed_temp_ ? UTEST_KEYWORD_PASSED : UTEST_KEYWORD_FAILED;
    commands_vec_ = nullptr;
    TestIOManager::OutputTestResult(answer);
    return answer;
  }
};

const std::set<std::string> Test::FAILED_STRINGS = {
    UTEST_KEYWORD_FAILED, UTEST_KEYWORD_EXCEPTION_FAILED,
    UTEST_KEYWORD_FATAL_FAILED, UTEST_KEYWORD_EXCEPTION_FATAL_FAILED};

}  // namespace UTestInfrastructure
