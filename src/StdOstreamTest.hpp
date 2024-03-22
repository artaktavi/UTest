#pragma once

#include <ostream>

#include "TestResult.hpp"

std::ostream& operator<<(std::ostream& o_stream,
                         const CommandStatus& command_status) {
  o_stream << command_status.line << ": " << command_status.type << '('
           << command_status.arg_1;
  if (!command_status.arg_2.empty()) {
    o_stream << ", " << command_status.arg_2;
  }
  o_stream << ")  :  " << command_status.result << '\n';
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream,
                         const TestStatus& test_status) {
  o_stream << test_status.group_name << '.' << test_status.name << " : "
           << test_status.result << " with "
           << test_status.execution_time.count() << "s\n";
  for (const CommandStatus& command : test_status.commands_history) {
    o_stream << command;
  }
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream,
                         const TestGroupStatus& group_status) {
  o_stream << "--- [" << group_status.group_name
           << "] --- : " << group_status.result << " with "
           << group_status.group_execution_time.count() << "s\n";
  for (const TestStatus& test : group_status.tests_history) {
    o_stream << test;
  }
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream, const TestResult& test_res) {
  std::unordered_map<std::string, TestGroupStatus> test_map(
      std::move(test_res.GetTestGroupStatusMap()));
  for (auto& pair : test_map) {
    o_stream << pair.second;
  }
  return o_stream;
}
