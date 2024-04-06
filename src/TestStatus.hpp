#pragma once

#include <chrono>
#include <vector>

#include <CommandStatus.hpp>

namespace UTest {
struct TestStatus {
  std::string name;
  std::string group_name;
  std::vector<CommandStatus> commands_history;
  std::chrono::duration<double> execution_time;
  std::string result;
  uint32_t line;
  std::string path;
  TestStatus() = delete;
  TestStatus(std::string name, std::string group_name, uint32_t line,
             std::string path)
      : name(std::move(name)),
        group_name(std::move(group_name)),
        line(line),
        path(std::move(path)) {}
  TestStatus(std::string name) : name(std::move(name)) {}
  TestStatus(const TestStatus& other) = default;
  TestStatus(TestStatus&& other) noexcept = default;
};
}  // namespace UTest