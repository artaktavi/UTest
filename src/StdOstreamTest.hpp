#pragma once

#include <OutputConfig.hpp>
#include <ConsoleSettings.hpp>
#include <TestResult.hpp>
#include <iomanip>

namespace StdOstreamTest {
void DisplayTestStartOstream(std::ostream& o_stream, const std::string& group,
                             const std::string& name) {
  o_stream << "  |  "
           << ConsoleSettings::GetColorCode(ConsoleSettings::common_color)
           << " [ " << std::setw(6) << std::left << KEYWORD_TEST_START << " ] "
           << group << '.' << name << ConsoleSettings::GetColorCode("reset")
           << std::endl;
}
void DisplayGroupStartOstream(std::ostream& o_stream,
                              const std::string& group_name) {
  o_stream << ConsoleSettings::GetColorCode(ConsoleSettings::common_color)
           << "[ --- " << group_name << " --- ] "
           << "[ v ======================= ]\n"
           << ConsoleSettings::GetColorCode("reset");
  //  o_stream << "[ | ======================= ]\n";
}
void DisplayCommandResultOstream(std::ostream& o_stream,
                                 const CommandStatus& command_status) {
  o_stream << command_status.line << ": " << command_status.type << '('
           << command_status.arg_1;
  if (!command_status.arg_2.empty()) {
    o_stream << ", " << command_status.arg_2;
  }
  o_stream << ")  :  " << command_status.result << '\n';
}
void DisplayTestResultOstream(std::ostream& o_stream,
                              const TestStatus& test_status) {
  if (OutputConfig::is_always_detailed ||
      (OutputConfig::is_failed_detailed &&
       test_status.result != KEYWORD_PASSED)) {
    for (const CommandStatus& command : test_status.commands_history) {
      DisplayCommandResultOstream(o_stream, command);
    }
  }
  o_stream << "  |  ";
  if (test_status.result == KEYWORD_PASSED) {
    o_stream << ConsoleSettings::GetColorCode(
        ConsoleSettings::test_succeed_color);
  } else {
    o_stream << ConsoleSettings::GetColorCode(
        ConsoleSettings::test_failed_color);
  }
  o_stream << " [ " << std::setw(6) << std::right << test_status.result << " ] "
           << ConsoleSettings::GetColorCode("reset");
  o_stream << " time: " << test_status.execution_time.count() << "s\n";
}
void DisplayGroupResultOstream(std::ostream& o_stream,
                               const TestGroupStatus& group_status) {
  o_stream << ConsoleSettings::GetColorCode("reset");
  o_stream << "[ ^ ======================= ]\n\n";
}
}  // namespace StdOstreamTest

std::ostream& operator<<(std::ostream& o_stream,
                         const CommandStatus& command_status) {
  StdOstreamTest::DisplayCommandResultOstream(o_stream, command_status);
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream,
                         const TestStatus& test_status) {
  StdOstreamTest::DisplayTestStartOstream(o_stream, test_status.group_name,
                                          test_status.name);
  for (const CommandStatus& command : test_status.commands_history) {
    o_stream << command;
  }
  StdOstreamTest::DisplayTestResultOstream(o_stream, test_status);
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream,
                         const TestGroupStatus& group_status) {
  StdOstreamTest::DisplayGroupStartOstream(o_stream, group_status.group_name);
  for (const TestStatus& test : group_status.tests_history) {
    o_stream << test;
  }
  StdOstreamTest::DisplayGroupResultOstream(o_stream, group_status);
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
