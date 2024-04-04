#pragma once

#include <ConsoleColorsConfig.hpp>
#include <OutputConfig.hpp>
#include <TestResult.hpp>
#include <iomanip>

namespace StdOstreamTest {
size_t group_title_total_size = 50;
std::string AlignOnCenterString(const std::string& str, size_t total_sz,
                                char filler) {
  std::string res;
  if (total_sz < str.size()) {
    res = str;
    return res;
  }
  size_t cur_sz = total_sz - str.size();
  cur_sz /= 2;
  res = std::string(cur_sz, filler);
  res += str;
  res += std::string(total_sz - res.size(), filler);
  return res;
}
void DisplayTestStartOstream(std::ostream& o_stream, const std::string& group,
                             const std::string& name) {
  o_stream << ConsoleColorsConfig::GetColorCode(
                  ConsoleColorsConfig::common_color)
           << "  | ";
  o_stream << ConsoleColorsConfig::GetColorCode(
                  ConsoleColorsConfig::test_start_color)
           << " [ " << std::setw(6) << std::left << KEYWORD_TEST_START << " ] "
           << name << ConsoleColorsConfig::GetColorCode("reset") << std::endl;
}
void DisplayGroupStartOstream(std::ostream& o_stream,
                              const std::string& group_name) {
  o_stream << ConsoleColorsConfig::GetColorCode(
                  ConsoleColorsConfig::common_color)
           << '|'
           << AlignOnCenterString(' ' + group_name + ' ',
                                  group_title_total_size - 2, '-')
           << "|\n"
           << "  v " << std::string(group_title_total_size - 8, '~') << " v\n"
           << ConsoleColorsConfig::GetColorCode("reset");
}
void DisplayCommandResultOstream(std::ostream& o_stream,
                                 const CommandStatus& command_status) {
  o_stream << ConsoleColorsConfig::GetColorCode(
                  ConsoleColorsConfig::common_color)
           << "  | ";
  if (command_status.result == KEYWORD_PASSED) {
    o_stream << ConsoleColorsConfig::GetColorCode(
        ConsoleColorsConfig::command_passed_color);
  } else if (command_status.result == KEYWORD_FAILED ||
             command_status.result == KEYWORD_EXCEPTION_FAILED) {
    o_stream << ConsoleColorsConfig::GetColorCode(
        ConsoleColorsConfig::command_failed_color);
  } else {
    o_stream << ConsoleColorsConfig::GetColorCode(
        ConsoleColorsConfig::command_fatal_failed_color);
  }
  o_stream << " ~ " << std::setw(6) << std::right
           << ("[" + std::to_string(command_status.line) + "]") << " "
           << std::setw(group_title_total_size - 14) << std::left
           << (command_status.type + '(' + command_status.arg_1 +
               (!command_status.arg_2.empty() ? ", " + command_status.arg_2
                                              : "") +
               ") ");
  if (OutputConfig::is_command_failed_path_enabled &&
      command_status.result != KEYWORD_PASSED) {
    o_stream << command_status.path << ":" << command_status.line;
  }
  o_stream << '\n' << ConsoleColorsConfig::GetColorCode("reset");
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
  o_stream << ConsoleColorsConfig::GetColorCode(
                  ConsoleColorsConfig::common_color)
           << "  | ";
  if (test_status.result == KEYWORD_PASSED) {
    o_stream << ConsoleColorsConfig::GetColorCode(
        ConsoleColorsConfig::test_passed_color);
  } else {
    o_stream << ConsoleColorsConfig::GetColorCode(
        ConsoleColorsConfig::test_failed_color);
  }
  o_stream << " [ " << std::setw(6) << std::right << test_status.result << " ] "
           << ConsoleColorsConfig::GetColorCode("reset");
  o_stream << "time: " << test_status.execution_time.count() << "s\n";
}
void DisplayGroupResultOstream(std::ostream& o_stream,
                               const TestGroupStatus& group_status) {
  o_stream << ConsoleColorsConfig::GetColorCode(
      ConsoleColorsConfig::common_color);
  o_stream << ("  ^ " + std::string(group_title_total_size - 8, '~') + " ^\n");
  std::string res_text;
  if (group_status.result == KEYWORD_FAILED) {
    o_stream << ConsoleColorsConfig::GetColorCode(
        ConsoleColorsConfig::group_failed_color);
    res_text = KEYWORD_FAILED;
  } else {
    o_stream << ConsoleColorsConfig::GetColorCode(
        ConsoleColorsConfig::group_passed_color);
    res_text = KEYWORD_PASSED;
  }
  o_stream << ("|" + std::string(group_title_total_size - 2, '-') + "|\n");
  o_stream << ("|" +
               AlignOnCenterString(res_text, group_title_total_size - 2, ' ') +
               "|\n");
  o_stream << ("|" + std::string(group_title_total_size - 2, '-') + "|\n\n");
  o_stream << ConsoleColorsConfig::GetColorCode("reset");
  o_stream << AlignOnCenterString("", group_title_total_size, ' ') << "\n\n";
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
