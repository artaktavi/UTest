#pragma once

#include <StdOstreamTest.hpp>

class TestIOManager {
  static TestResult general_test_output_;

 public:
  static void ToggleOStream() noexcept {
    OutputConfig::o_cout_stream_enabled = !OutputConfig::o_cout_stream_enabled;
  }
  static void ToggleOCerrStream() noexcept {
    OutputConfig::o_cerr_stream_enabled = !OutputConfig::o_cerr_stream_enabled;
  }
  static void SwitchStreams() noexcept {
    ToggleOStream();
    ToggleOCerrStream();
  }
  static void ToggleOJsonFile(const std::string& new_path = "") noexcept {
    OutputConfig::o_json_file_enabled = !OutputConfig::o_json_file_enabled;
    if (!new_path.empty()) {
      SetOutputJsonFilePath(new_path);
    }
    if (!general_test_output_.IsAutoSaveEnabled()) {
      general_test_output_.ToggleAutoSave();
    }
  }
  static bool IsOStreamEnabled() noexcept {
    return OutputConfig::o_cout_stream_enabled;
  }
  static bool IsOCerrStreamEnabled() noexcept {
    return OutputConfig::o_cerr_stream_enabled;
  }
  static bool IsOJsonFileEnabled() noexcept {
    return OutputConfig::o_json_file_enabled;
  }
  static void SetOutputJsonFilePath(const std::string& new_path) noexcept {
    general_test_output_.SetPathToAutoSave(new_path);
  }
  static void OutputTestResult(const TestStatus& test_status) {
    if (OutputConfig::o_cout_stream_enabled) {
      StdOstreamTest::DisplayTestResultOstream(std::cout, test_status);
    }
    if (OutputConfig::o_cerr_stream_enabled) {
      StdOstreamTest::DisplayTestResultOstream(std::cerr, test_status);
    }
    if (OutputConfig::o_json_file_enabled) {
      general_test_output_.AddTestStatus(test_status);
    }
  }
  static void OutputTestStart(const std::string& group,
                              const std::string& name) {
    if (OutputConfig::o_cout_stream_enabled) {
      StdOstreamTest::DisplayTestStartOstream(std::cout, group, name);
    }
    if (OutputConfig::o_cerr_stream_enabled) {
      StdOstreamTest::DisplayTestStartOstream(std::cerr, group, name);
    }
  }
  static void OutputGroupResult(const TestGroupStatus& group_status) {
    if (OutputConfig::o_cout_stream_enabled) {
      StdOstreamTest::DisplayGroupResultOstream(std::cout, group_status);
    }
    if (OutputConfig::o_cerr_stream_enabled) {
      StdOstreamTest::DisplayGroupResultOstream(std::cerr, group_status);
    }
    if (OutputConfig::o_json_file_enabled) {
      general_test_output_.AddGroupStatus(group_status);
    }
  }
  static void OutputGroupStart(const std::string& group_name) {
    if (OutputConfig::o_cout_stream_enabled) {
      StdOstreamTest::DisplayGroupStartOstream(std::cout, group_name);
    }
    if (OutputConfig::o_cerr_stream_enabled) {
      StdOstreamTest::DisplayGroupStartOstream(std::cerr, group_name);
    }
  }
};

TestResult TestIOManager::general_test_output_;
