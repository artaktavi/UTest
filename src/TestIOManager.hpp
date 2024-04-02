#pragma once

#include <StdOstreamTest.hpp>

class TestIOManager {
  static const std::unordered_map<std::string, std::string> console_colors_;
  static bool o_stream_enabled_;
  static bool o_cerr_stream_enabled_;
  static bool o_json_file_enabled_;
  static TestResult general_test_output_;

 public:
  static void SetCoutConsoleColor(const std::string& color) noexcept {
    auto it = console_colors_.find(color);
    if (it == console_colors_.end()) {
      std::cout << "SetConsoleColor: wrong argument";
      return;
    }
    std::cout << (it->second);
  }
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
};

TestResult TestIOManager::general_test_output_;
bool TestIOManager::o_stream_enabled_ = true;
bool TestIOManager::o_cerr_stream_enabled_ = false;
bool TestIOManager::o_json_file_enabled_ = false;
const std::unordered_map<std::string, std::string> TestIOManager::console_colors_ = {
    {"reset", "\033[0m"},
    {"black", "\033[30m"},
    {"red", "\033[31m"},
    {"green", "\033[32m"},
    {"yellow", "\033[33m"},
    {"blue", "\033[34m"},
    {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},
    {"white", "\033[37m"},
    {"boldblack", "\033[1m\033[30m"},
    {"boldred", "\033[1m\033[31m"},
    {"boldgreen", "\033[1m\033[32m"},
    {"boldyellow", "\033[1m\033[33m"},
    {"boldblue", "\033[1m\033[34m"},
    {"boldmagenta", "\033[1m\033[35m"},
    {"boldcyan", "\033[1m\033[36m"},
    {"boldwhite", "\033[1m\033[37m"}
};