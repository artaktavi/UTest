#ifndef UNITTESTER_TEST_IO_MANAGER_CLASS_HPP
#define UNITTESTER_TEST_IO_MANAGER_CLASS_HPP

#include <fstream>
#include <iostream>
#include "../third_party/json.hpp"
#include "test_registry_class.hpp"

std::ostream& operator<<(std::ostream& out_stream,
                         const CommandStatus& command_status) {
  out_stream << command_status.line << ": " << command_status.type << '('
             << command_status.arg_1;
  if (!command_status.arg_2.empty()) {
    out_stream << ", " << command_status.arg_2;
  }
  out_stream << ")  :  " << command_status.result << '\n';
  return out_stream;
}

std::ostream& operator<<(std::ostream& out_stream,
                         const TestStatus& test_status) {
  out_stream << test_status.group_name << '.' << test_status.name << " : "
             << test_status.result << " with "
             << test_status.execution_time.count() << "s\n";
  for (const CommandStatus& command : test_status.commands_history) {
    out_stream << command;
  }
  return out_stream;
}

std::ostream& operator<<(std::ostream& out_stream,
                         const TestGroupStatus& group_status) {
  out_stream << group_status.group_name << " : " << group_status.result
             << " with " << group_status.group_execution_time.count() << "s\n";
  for (const TestStatus& test : group_status.tests_history) {
    out_stream << test;
  }
  return out_stream;
}

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
  static void SerializeToJsonFile(const std::string& path,
      const std::vector<TestGroupStatus>& test_groups) {
    nlohmann::json new_json;
    for (const TestGroupStatus& group : test_groups) {
      new_json[group.group_name]["res"] = group.result;
      new_json[group.group_name]["exec"] = group.group_execution_time.count();
      for (const TestStatus& test : group.tests_history) {
        new_json[group.group_name]["tests"][test.name]["res"] = test.result;
        new_json[group.group_name]["tests"][test.name]["exec"] = test.execution_time.count();
        for (const CommandStatus& command : test.commands_history) {
          new_json[group.group_name]["tests"][test.name]["commands"][std::to_string(command.line)]["type"] = command.type;
          new_json[group.group_name]["tests"][test.name]["commands"][std::to_string(command.line)]["res"] = command.result;
          new_json[group.group_name]["tests"][test.name]["commands"][std::to_string(command.line)]["arg_1"] = command.arg_1;
          new_json[group.group_name]["tests"][test.name]["commands"][std::to_string(command.line)]["arg_2"] = command.arg_2;
        }
      }
    }
    std::ofstream new_file(path);
    new_file << new_json;
    new_file.close();
  }
  static std::vector<TestGroupStatus> DeserializeFromJsonFile(
      const std::string& json_file_path) noexcept {
    
  }
};

bool TestIOManager::O_STREAM_ENABLED = true;
bool TestIOManager::O_CERR_STREAM_ENABLED = false;
bool TestIOManager::O_JSONFILE_ENABLED = false;
std::string TestIOManager::out_jsonfile_path_ = "tests_result.json";

#endif  //UNITTESTER_TEST_IO_MANAGER_CLASS_HPP
