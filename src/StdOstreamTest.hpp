#pragma once

#include <ConsoleColorsConfig.hpp>
#include <OutputConfig.hpp>
#include <TestResult.hpp>
#include <iomanip>

namespace UTestInfrastructure {
namespace StdOstreamTest {
std::string AlignOnRightString(const std::string& str, size_t total_sz,
                               char filler) {
  std::string res;
  if (total_sz < str.size()) {
    res = str;
    return res;
  }
  res += std::string(total_sz - str.size(), filler);
  res += str;
  return res;
}
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
  o_stream << UTest::ConsoleColorsConfig::GetColorCode(
                  UTest::ConsoleColorsConfig::common_color)
           << "  | ";
  o_stream << UTest::ConsoleColorsConfig::GetColorCode(
                  UTest::ConsoleColorsConfig::test_start_color)
           << " [ " << std::setw(6) << std::left << UTEST_KEYWORD_TEST_START
           << " ] " << name << UTest::ConsoleColorsConfig::GetColorCode("reset")
           << std::endl;
}
void DisplayGroupStartOstream(std::ostream& o_stream,
                              const std::string& group_name) {
  o_stream << UTest::ConsoleColorsConfig::GetColorCode(
                  UTest::ConsoleColorsConfig::common_color)
           << '|'
           << AlignOnCenterString(' ' + group_name + ' ',
                                  UTest::OutputConfig::block_width - 2, '-')
           << "|\n"
           << "  v " << std::string(UTest::OutputConfig::block_width - 8, '~')
           << " v\n"
           << UTest::ConsoleColorsConfig::GetColorCode("reset");
}
void DisplayCommandResultOstream(std::ostream& o_stream,
                                 const UTest::CommandStatus& command_status) {
  o_stream << UTest::ConsoleColorsConfig::GetColorCode(
                  UTest::ConsoleColorsConfig::common_color)
           << "  | ";
  if (command_status.result == UTEST_KEYWORD_PASSED) {
    o_stream << UTest::ConsoleColorsConfig::GetColorCode(
        UTest::ConsoleColorsConfig::command_passed_color);
  } else if (command_status.result == UTEST_KEYWORD_FAILED ||
             command_status.result == UTEST_KEYWORD_EXCEPTION_FAILED) {
    o_stream << UTest::ConsoleColorsConfig::GetColorCode(
        UTest::ConsoleColorsConfig::command_failed_color);
  } else {
    o_stream << UTest::ConsoleColorsConfig::GetColorCode(
        UTest::ConsoleColorsConfig::command_fatal_failed_color);
  }
  o_stream << "   ~ " << std::setw(6) << std::right
           << ("[" + std::to_string(command_status.line) + "]") << " "
           << std::setw(UTest::OutputConfig::block_width - 16) << std::left
           << (command_status.type + '(' + command_status.arg_1 +
               (!command_status.arg_2.empty() ? ", " + command_status.arg_2
                                              : "") +
               ") ");
  o_stream << UTest::ConsoleColorsConfig::GetColorCode("reset");
  if (UTest::OutputConfig::is_command_failed_path_enabled &&
      command_status.result != UTEST_KEYWORD_PASSED) {
    o_stream << "in file: " << command_status.path << ":"
             << command_status.line;
  }
  o_stream << '\n';
}
void DisplayTestResultOstream(std::ostream& o_stream,
                              const UTest::TestStatus& test_status) {
  if (UTest::OutputConfig::is_always_detailed ||
      (UTest::OutputConfig::is_failed_detailed &&
       test_status.result != UTEST_KEYWORD_PASSED)) {
    for (const UTest::CommandStatus& command : test_status.commands_history) {
      DisplayCommandResultOstream(o_stream, command);
    }
  }
  o_stream << UTest::ConsoleColorsConfig::GetColorCode(
                  UTest::ConsoleColorsConfig::common_color)
           << "  | ";
  std::string path_tmp;
  if (test_status.result == UTEST_KEYWORD_PASSED) {
    o_stream << UTest::ConsoleColorsConfig::GetColorCode(
        UTest::ConsoleColorsConfig::test_passed_color);
  } else {
    o_stream << UTest::ConsoleColorsConfig::GetColorCode(
        UTest::ConsoleColorsConfig::test_failed_color);
    if (UTest::OutputConfig::is_test_failed_path_enabled) {
      path_tmp = "in file: " + test_status.path + ':' +
                 std::to_string(test_status.line);
    }
  }
  o_stream << " [ " << std::setw(6) << std::right << test_status.result << " ] "
           << UTest::ConsoleColorsConfig::GetColorCode("reset");
  o_stream << std::setw(UTest::OutputConfig::block_width - 16) << std::left
           << (std::to_string(test_status.execution_time.count()) + "s ")
           << path_tmp << '\n';
}
void DisplayGroupResultOstream(std::ostream& o_stream,
                               const UTest::TestGroupStatus& group_status) {
  o_stream << UTest::ConsoleColorsConfig::GetColorCode(
      UTest::ConsoleColorsConfig::common_color);
  o_stream << ("  ^ " + std::string(UTest::OutputConfig::block_width - 8, '~') +
               " ^\n");
  o_stream << UTest::ConsoleColorsConfig::GetColorCode(
                  UTest::ConsoleColorsConfig::common_color)
           << '|'
           << AlignOnCenterString(' ' + group_status.group_name + ' ',
                                  UTest::OutputConfig::block_width - 2, '-')
           << "|\n";
  std::string res_text;
  if (group_status.result == UTEST_KEYWORD_FAILED) {
    o_stream << UTest::ConsoleColorsConfig::GetColorCode(
        UTest::ConsoleColorsConfig::group_failed_color);
    res_text = UTEST_KEYWORD_FAILED;
  } else {
    o_stream << UTest::ConsoleColorsConfig::GetColorCode(
        UTest::ConsoleColorsConfig::group_passed_color);
    res_text = UTEST_KEYWORD_PASSED;
  }
  size_t tests_passed = 0;
  size_t tests_failed = 0;
  for (const UTest::TestStatus& test : group_status.tests_history) {
    if (test.result == UTEST_KEYWORD_PASSED) {
      ++tests_passed;
    } else {
      ++tests_failed;
    }
  }
  o_stream << ("|" + std::string(UTest::OutputConfig::block_width - 2, '-') +
               "|\n");
  o_stream << '|'
           << AlignOnCenterString(' ' + res_text + ' ',
                                  UTest::OutputConfig::block_width - 2, ' ')
           << "|\n";
  o_stream << ("|" + std::string(UTest::OutputConfig::block_width - 2, '-') +
               "|\n");
  o_stream << "| " << std::setw(UTest::OutputConfig::block_width - 4)
           << std::left
           << ("tests passed:   " +
               AlignOnRightString(std::to_string(tests_passed),
                                  UTest::OutputConfig::stats_symbols_count,
                                  '.'))
           << " |\n";
  o_stream << "| " << std::setw(UTest::OutputConfig::block_width - 4)
           << std::left
           << ("tests failed:   " +
               AlignOnRightString(std::to_string(tests_failed),
                                  UTest::OutputConfig::stats_symbols_count,
                                  '.'))
           << " |\n";
  o_stream << "| " << std::setw(UTest::OutputConfig::block_width - 4)
           << std::left
           << ("execution time: " +
               AlignOnRightString(
                   std::to_string(group_status.group_execution_time.count()),
                   UTest::OutputConfig::stats_symbols_count, '.') +
               " sec")
           << " |\n";
  o_stream << ("|" + std::string(UTest::OutputConfig::block_width - 2, '-') +
               "|\n");
  o_stream << UTest::ConsoleColorsConfig::GetColorCode("reset");
  o_stream << "\n\n";
}
}  // namespace StdOstreamTest
}  // namespace UTestInfrastructure

std::ostream& operator<<(std::ostream& o_stream,
                         const UTest::CommandStatus& command_status) {
  UTestInfrastructure::StdOstreamTest::DisplayCommandResultOstream(
      o_stream, command_status);
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream,
                         const UTest::TestStatus& test_status) {
  UTestInfrastructure::StdOstreamTest::DisplayTestStartOstream(
      o_stream, test_status.group_name, test_status.name);
  UTestInfrastructure::StdOstreamTest::DisplayTestResultOstream(o_stream,
                                                                test_status);
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream,
                         const UTest::TestGroupStatus& group_status) {
  UTestInfrastructure::StdOstreamTest::DisplayGroupStartOstream(
      o_stream, group_status.group_name);
  for (const UTest::TestStatus& test : group_status.tests_history) {
    o_stream << test;
  }
  UTestInfrastructure::StdOstreamTest::DisplayGroupResultOstream(o_stream,
                                                                 group_status);
  return o_stream;
}

std::ostream& operator<<(std::ostream& o_stream,
                         const UTest::TestResult& test_res) {
  std::unordered_map<std::string, UTest::TestGroupStatus> test_map(
      std::move(test_res.GetTestGroupStatusMap()));
  for (auto& pair : test_map) {
    o_stream << pair.second;
  }
  return o_stream;
}
