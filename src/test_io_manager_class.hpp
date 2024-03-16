#ifndef UNITTESTER_TEST_IO_MANAGER_CLASS_HPP
#define UNITTESTER_TEST_IO_MANAGER_CLASS_HPP

#include "std_cout_test.hpp"
#include "../third_party/json.hpp"
#include "test_registry_class.hpp"

class TestIOManager {
  static bool O_STREAM_ENABLED;
  static bool O_CERR_STREAM_ENABLED;
  static bool O_JSONFILE_ENABLED;
  static std::string out_jsonfile_path_;

 public:
  static void ToggleOStream() noexcept { O_STREAM_ENABLED = !O_STREAM_ENABLED; }
  static void ToggleOCerrStream() noexcept {
    O_CERR_STREAM_ENABLED = !O_CERR_STREAM_ENABLED;
  }
  static void ToggleOJsonFile() noexcept {
    O_JSONFILE_ENABLED = !O_JSONFILE_ENABLED;
  }
  static void SetOutputJsonFilePath(const std::string& new_path) noexcept {
    out_jsonfile_path_ = new_path;
  }
};

bool TestIOManager::O_STREAM_ENABLED = true;
bool TestIOManager::O_CERR_STREAM_ENABLED = false;
bool TestIOManager::O_JSONFILE_ENABLED = false;
std::string TestIOManager::out_jsonfile_path_ = "tests_result.json";

#endif  //UNITTESTER_TEST_IO_MANAGER_CLASS_HPP
