#ifndef UNITTESTER_TEST_GROUP_CLASS_HPP
#define UNITTESTER_TEST_GROUP_CLASS_HPP

#include "test_class.hpp"
#include "test_group_status_class.hpp"

#include <vector>

class TestGroup {
 private:
  std::string group_name_;
  std::vector<Test*> tests_;
  std::vector<TestStatus> tests_history_;
  bool is_passed_ = true;

 public:
  TestGroup() = delete;
  TestGroup(const TestGroup& other) = default;
  TestGroup(std::string name) : group_name_(std::move(name)) {}
  void AddTest(Test* test) { tests_.push_back(test); }
  TestGroupStatus Execute() {
    tests_history_.clear();
    is_passed_ = true;
    const auto start_time = std::chrono::high_resolution_clock::now();
    for (Test* test : tests_) {
      tests_history_.push_back(test->Execute());
      if (tests_history_.back().result == "failed") {
        is_passed_ = false;
      }
    }
    const auto stop_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> group_execution_time =
        stop_time - start_time;
    return {group_name_, tests_history_, group_execution_time,
            is_passed_ ? "succeed" : "failed"};
  }
};

#endif  //UNITTESTER_TEST_GROUP_CLASS_HPP
