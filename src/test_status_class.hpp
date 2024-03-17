#ifndef UNITTESTER_TEST_STATUS_CLASS_HPP
#define UNITTESTER_TEST_STATUS_CLASS_HPP

#include <chrono>
#include <vector>

#ifndef UNITTESTER_COMMAND_STATUS_CLASS_HPP
#include "command_status_class.hpp"
#endif

struct TestStatus {
  std::string name;
  std::string group_name;
  std::vector<CommandStatus> commands_history;
  std::chrono::duration<double> execution_time;
  std::string result;
  TestStatus() = delete;
  TestStatus(std::string name, std::string group_name)
      : name(std::move(name)), group_name(std::move(group_name)) {}
  TestStatus(const TestStatus& other) = default;
};

#endif  //UNITTESTER_TEST_STATUS_CLASS_HPP
