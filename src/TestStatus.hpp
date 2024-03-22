#pragma once

#include <chrono>
#include <vector>

#include "CommandStatus.hpp"

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
