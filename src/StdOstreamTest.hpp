#pragma once

#include <ConsoleSettings.hpp>
#include <TestResult.hpp>
#include <iomanip>

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
  o_stream << "  |  ";
  if (test_status.result == KEYWORD_PASSED) {
    o_stream << ConsoleSettings::GetColorCode(
        ConsoleSettings::test_succeed_color);
  } else {
    o_stream << ConsoleSettings::GetColorCode(
        ConsoleSettings::test_failed_color);
  }
  o_stream << " [ " << std::setw(6) << std::right << test_status.result
           << " ] " << ConsoleSettings::GetColorCode("reset");
  o_stream << " time: " << test_status.execution_time.count() << "s\n";
  if (ConsoleSettings::is_always_detailed ||
      (ConsoleSettings::is_failed_detailed &&
       test_status.result != KEYWORD_PASSED)) {
    for (const CommandStatus& command : test_status.commands_history) {
      o_stream << command;
    }
  }
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream,
                         const TestGroupStatus& group_status) {

  o_stream << ConsoleSettings::GetColorCode("reset");
  for (const TestStatus& test : group_status.tests_history) {
    o_stream << test;
  }
  o_stream << "[ ^ ======================= ]\n\n";
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
