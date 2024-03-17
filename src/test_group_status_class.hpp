#ifndef UNITTESTER_TEST_GROUP_STATUS_CLASS_HPP
#define UNITTESTER_TEST_GROUP_STATUS_CLASS_HPP

#ifndef UNITTESTER_TEST_STATUS_CLASS_HPP
#include "test_status_class.hpp"
#endif

#include <vector>

struct TestGroupStatus {
  std::string group_name;
  std::vector<TestStatus> tests_history;
  std::chrono::duration<double> group_execution_time;
  std::string result = "succeed";
  TestGroupStatus() = delete;
  TestGroupStatus(const TestGroupStatus& other) = default;
  TestGroupStatus(std::string name) : group_name(std::move(name)) {}
};

#endif  //UNITTESTER_TEST_GROUP_STATUS_CLASS_HPP
