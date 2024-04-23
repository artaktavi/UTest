#pragma once

#include <vector>

#include <TestStatus.hpp>

namespace UTest {

struct TestGroupStatus {
  std::string group_name;
  std::vector<TestStatus> tests_history;
  std::chrono::duration<double> group_execution_time;
  std::string result = UTEST_KEYWORD_PASSED;

  TestGroupStatus() = delete;

  TestGroupStatus(const TestGroupStatus& other) = default;

  TestGroupStatus(std::string name) : group_name(std::move(name)) {}

  TestGroupStatus(TestGroupStatus&& other) noexcept
      : group_name(std::move(other.group_name)),
        tests_history(std::move(other.tests_history)),
        group_execution_time(other.group_execution_time),
        result(std::move(other.result)) {}
};

}  // namespace UTest