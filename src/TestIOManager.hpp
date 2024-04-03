#pragma once

#include <StdOstreamTest.hpp>

class TestIOManager {
  static bool o_stream_enabled_;
  static bool o_cerr_stream_enabled_;
  static bool o_json_file_enabled_;
  static TestResult general_test_output_;

 public:
//  static void SetCoutConsoleColor(const std::string& color) noexcept {
//
//  }
//  static void SetCerrConsoleColor(const std::string& color) noexcept {
//
//  }
  static void ToggleOStream() noexcept {
    o_stream_enabled_ = !o_stream_enabled_;
  }
  static void ToggleOCerrStream() noexcept {
    o_cerr_stream_enabled_ = !o_cerr_stream_enabled_;
  }
  static void SwitchStreams() noexcept {
    ToggleOStream();
    ToggleOCerrStream();
  }
  static void ToggleOJsonFile(const std::string& new_path = "") noexcept {
    o_json_file_enabled_ = !o_json_file_enabled_;
    if (!new_path.empty()) {
      SetOutputJsonFilePath(new_path);
    }
    if (!general_test_output_.IsAutoSaveEnabled()) {
      general_test_output_.ToggleAutoSave();
    }
  }
  static bool IsOStreamEnabled() noexcept {
    return o_stream_enabled_;
  }
  static bool IsOCerrStreamEnabled() noexcept {
    return o_cerr_stream_enabled_;
  }
  static bool IsOJsonFileEnabled() noexcept {
    return o_json_file_enabled_;
  }
  static void SetOutputJsonFilePath(const std::string& new_path) noexcept {
    general_test_output_.SetPathToAutoSave(new_path);
  }
  static void OutputTestStatus(const TestStatus& test_status) {
    if (o_stream_enabled_) {
      std::cout << test_status;
    }
    if (o_cerr_stream_enabled_) {
      std::cerr << test_status;
    }
    if (o_json_file_enabled_) {
      general_test_output_.AddTestStatus(test_status);
    }
  }
  static void OutputTestStart(const std::string& group, const std::string& name) {
    if (o_stream_enabled_) {
      std::cout << "  |  "
               << ConsoleSettings::GetColorCode(ConsoleSettings::common_color)
               << " [ " << std::setw(6) << std::left << KEYWORD_TEST_START
               << " ] " << group << '.' << name
               << ConsoleSettings::GetColorCode("reset") << std::endl;
    }
    if (o_cerr_stream_enabled_) {
      std::cerr << "  |  "
               << ConsoleSettings::GetColorCode(ConsoleSettings::common_color)
               << " [ " << std::setw(6) << std::left << KEYWORD_TEST_START
               << " ] " << group << '.' << name
               << ConsoleSettings::GetColorCode("reset") << std::endl;
    }
  }
  static void OutputGroupStatus(const TestGroupStatus& group_status) {
    if (o_stream_enabled_) {
      std::cout << group_status;
    }
    if (o_cerr_stream_enabled_) {
      std::cerr << group_status;
    }
    if (o_json_file_enabled_) {
      general_test_output_.AddGroupStatus(group_status);
    }
  }
  static void OutputGroupStart(const std::string& group_name) {
    if (o_stream_enabled_) {
      std::cout << ConsoleSettings::GetColorCode(ConsoleSettings::common_color) << "[ --- " << group_name
               << " --- ] " << "[ v ======================= ]\n";
      //  o_stream << "[ | ======================= ]\n";
   }
    if (o_cerr_stream_enabled_) {
      std::cout << ConsoleSettings::GetColorCode(ConsoleSettings::common_color) << "[ --- " << group_name
                << " --- ] " << "[ v ======================= ]\n";
      //  o_stream << "[ | ======================= ]\n";
    }
  }
};

TestResult TestIOManager::general_test_output_;
bool TestIOManager::o_stream_enabled_ = true;
bool TestIOManager::o_cerr_stream_enabled_ = false;
bool TestIOManager::o_json_file_enabled_ = false;
