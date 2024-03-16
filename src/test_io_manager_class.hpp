#ifndef UNITTESTER_TEST_IO_MANAGER_CLASS_HPP
#define UNITTESTER_TEST_IO_MANAGER_CLASS_HPP

#include "std_ostream_test.hpp"
#include "test_result_class.hpp"

class TestIOManager {
  static bool O_STREAM_ENABLED;
  static bool O_CERR_STREAM_ENABLED;
  static bool O_JSONFILE_ENABLED;
  static TestResult general_test_output_;

 public:
  static void ToggleOStream() noexcept {
    O_STREAM_ENABLED = !O_STREAM_ENABLED;
  }
  static void ToggleOCerrStream() noexcept {
    O_CERR_STREAM_ENABLED = !O_CERR_STREAM_ENABLED;
  }
  static void SwitchStreams() noexcept {
    ToggleOStream();
    ToggleOCerrStream();
  }
  static void ToggleOJsonFile(const std::string& new_path = "") noexcept {
    O_JSONFILE_ENABLED = !O_JSONFILE_ENABLED;
    if (!new_path.empty()) {
      SetOutputJsonFilePath(new_path);
    }
    if (!general_test_output_.IsAutoSaveEnabled()) {
      general_test_output_.ToggleAutoSave();
    }
  }
  static bool IsOStreamEnabled() noexcept {
    return O_STREAM_ENABLED;
  }
  static bool IsOCerrStreamEnabled() noexcept {
    return O_CERR_STREAM_ENABLED;
  }
  static bool IsOJsonFileEnabled() noexcept {
    return O_JSONFILE_ENABLED;
  }
  static void SetOutputJsonFilePath(const std::string& new_path) noexcept {
    general_test_output_.SetPathToAutoSave(new_path);
  }
  static void OutputTestStatus(const TestStatus& test_status) {
    if (O_STREAM_ENABLED) {
      std::cout << test_status;
    }
    if (O_CERR_STREAM_ENABLED) {
      std::cerr << test_status;
    }
    if (O_JSONFILE_ENABLED) {
      general_test_output_.AddTestStatus(test_status);
    }
  }
  static void OutputGroupStatus(const TestGroupStatus& group_status) {
    if (O_STREAM_ENABLED) {
      std::cout << group_status;
    }
    if (O_CERR_STREAM_ENABLED) {
      std::cerr << group_status;
    }
    if (O_JSONFILE_ENABLED) {
      general_test_output_.AddGroupStatus(group_status);
    }
  }
};

TestResult TestIOManager::general_test_output_;
bool TestIOManager::O_STREAM_ENABLED = true;
bool TestIOManager::O_CERR_STREAM_ENABLED = false;
bool TestIOManager::O_JSONFILE_ENABLED = false;

#endif  //UNITTESTER_TEST_IO_MANAGER_CLASS_HPP
