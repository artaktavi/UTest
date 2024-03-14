#ifndef UNITTESTER_TEST_GROUP_STATUS_CLASS_HPP
#define UNITTESTER_TEST_GROUP_STATUS_CLASS_HPP

#include "test_class.hpp"
#include "test_status_class.hpp"

#include <vector>

struct TestGroupStatus {
  std::string group_name;
  std::vector<TestStatus>& tests_history;
  std::chrono::duration<double> group_execution_time;
  std::string result;
  TestGroupStatus() = delete;
  TestGroupStatus(std::string group_name,
                  std::vector<TestStatus>& tests_history,
                  std::chrono::duration<double> group_execution_time,
                  std::string result)
      : group_name(std::move(group_name)),
        tests_history(tests_history),
        group_execution_time(group_execution_time),
        result(std::move(result)) {}
  TestGroupStatus(const TestGroupStatus& other) = default;
};

#endif  //UNITTESTER_TEST_GROUP_STATUS_CLASS_HPP
