#pragma once

#include <chrono>
#include <vector>

#include <CommandStatus.hpp>

struct TestStatus {
  std::string name;
  std::string group_name;
  std::vector<CommandStatus> commands_history;
  std::chrono::duration<double> execution_time;
  std::string result;
  TestStatus() = delete;
  TestStatus(std::string name, std::string group_name)
      : name(std::move(name)), group_name(std::move(group_name)) {}
  TestStatus(std::string name) : name(std::move(name)) {}
  TestStatus(const TestStatus& other) = default;
  TestStatus(TestStatus&& other) noexcept
      : name(std::move(other.name)),
        group_name(std::move(other.group_name)),
        commands_history(std::move(other.commands_history)),
        execution_time(other.execution_time),
        result(std::move(other.result)) {}
};
