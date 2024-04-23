#pragma once

#include <StdOstreamTest.hpp>

namespace UTestInfrastructure {

class TestIOManager {
  static UTest::TestResult general_test_output_;

 public:
  static void ToggleOJsonFile(const std::string& new_path = "") noexcept {
    UTest::OutputConfig::o_json_file_enabled =
        !UTest::OutputConfig::o_json_file_enabled;

    if (!new_path.empty()) {
      SetOutputJsonFilePath(new_path);
    }

    if (!general_test_output_.IsAutoSaveEnabled()) {
      general_test_output_.ToggleAutoSave();
    }
  }

  static void SetOutputJsonFilePath(const std::string& new_path) noexcept {
    general_test_output_.SetPathToAutoSave(new_path);
  }

  static void OutputTestResult(const UTest::TestStatus& test_status) {

    if (UTest::OutputConfig::o_cout_stream_enabled) {
      StdOstreamTest::DisplayTestResultOstream(std::cout, test_status);
    }

    if (UTest::OutputConfig::o_cerr_stream_enabled) {
      StdOstreamTest::DisplayTestResultOstream(std::cerr, test_status);
    }

    if (UTest::OutputConfig::o_json_file_enabled) {
      general_test_output_.AddTestStatus(test_status);
    }
  }

  static void OutputTestStart(const std::string& group,
                              const std::string& name) {

    if (UTest::OutputConfig::o_cout_stream_enabled) {
      StdOstreamTest::DisplayTestStartOstream(std::cout, group, name);
    }

    if (UTest::OutputConfig::o_cerr_stream_enabled) {
      StdOstreamTest::DisplayTestStartOstream(std::cerr, group, name);
    }
  }

  static void OutputGroupResult(const UTest::TestGroupStatus& group_status) {
    if (UTest::OutputConfig::o_cout_stream_enabled) {
      StdOstreamTest::DisplayGroupResultOstream(std::cout, group_status);
    }

    if (UTest::OutputConfig::o_cerr_stream_enabled) {
      StdOstreamTest::DisplayGroupResultOstream(std::cerr, group_status);
    }

    if (UTest::OutputConfig::o_json_file_enabled) {
      general_test_output_.AddGroupStatus(group_status);
    }
  }

  static void OutputGroupStart(const std::string& group_name) {
    if (UTest::OutputConfig::o_cout_stream_enabled) {
      StdOstreamTest::DisplayGroupStartOstream(std::cout, group_name);
    }

    if (UTest::OutputConfig::o_cerr_stream_enabled) {
      StdOstreamTest::DisplayGroupStartOstream(std::cerr, group_name);
    }
  }
};

UTest::TestResult TestIOManager::general_test_output_;

}  // namespace UTestInfrastructure