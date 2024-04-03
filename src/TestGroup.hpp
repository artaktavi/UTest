#pragma once

#include <TestClass.hpp>
#include <TestGroupStatus.hpp>

class TestGroup {
 private:
  std::string group_name_;
  std::vector<Test*> tests_;

 public:
  TestGroup() = delete;
  TestGroup(const TestGroup& other) = default;
  TestGroup(std::string name) : group_name_(std::move(name)) {}
  void AddTest(Test* test) { tests_.push_back(test); }
  TestGroupStatus Execute() {
    TestGroupStatus answer(group_name_);
    TestIOManager::OutputGroupStart(group_name_);
    const auto start_time = std::chrono::high_resolution_clock::now();
    for (Test* test : tests_) {
      answer.tests_history.push_back(test->Execute());
      if (answer.tests_history.back().result == KEYWORD_FAILED) {
        answer.result = KEYWORD_FAILED;
      }
    }
    const auto stop_time = std::chrono::high_resolution_clock::now();
    answer.group_execution_time = stop_time - start_time;
    TestIOManager::OutputGroupResult(answer);
    return answer;
  }
};
