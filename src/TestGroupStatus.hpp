#pragma once

#include <vector>

#include "TestStatus.hpp"

struct TestGroupStatus {
  std::string group_name;
  std::vector<TestStatus> tests_history;
  std::chrono::duration<double> group_execution_time;
  std::string result = "succeed";
  TestGroupStatus() = delete;
  TestGroupStatus(const TestGroupStatus& other) = default;
  TestGroupStatus(std::string name) : group_name(std::move(name)) {}
};
