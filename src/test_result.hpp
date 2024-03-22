#pragma once

#include <fstream>

// Make this include normal
#include "../third_party/json.hpp"
#include "test_group_status.hpp"

class TestResult {
  static const std::string TESTS_STR_;
  static const std::string RES_STR_;
  static const std::string EXEC_STR_;
  static const std::string ARG_1_STR_;
  static const std::string ARG_2_STR_;
  static const std::string TYPE_STR_;
  static const std::string COMMANDS_STR_;
  nlohmann::json json_storage_;
  std::string path_to_auto_save_ = "unit_tester_report.json";
  bool auto_save_enabled_ = false;

 public:
  void ToggleAutoSave() {
    auto_save_enabled_ = !auto_save_enabled_;
  }
  bool IsAutoSaveEnabled() {
    return auto_save_enabled_;
  }
  void SetPathToAutoSave(const std::string& path) {
    path_to_auto_save_ = path;
  }
  void AddTestStatus(const TestStatus& test) {
    json_storage_[test.group_name][TESTS_STR_][test.name][RES_STR_] =
        test.result;
    json_storage_[test.group_name][TESTS_STR_][test.name][EXEC_STR_] =
        test.execution_time.count();
    for (const CommandStatus& command : test.commands_history) {
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [std::to_string(command.line)][TYPE_STR_] = command.type;
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [std::to_string(command.line)][RES_STR_] = command.result;
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [std::to_string(command.line)][ARG_1_STR_] = command.arg_1;
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [std::to_string(command.line)][ARG_2_STR_] = command.arg_2;
    }
  }
  void AddGroupStatus(const TestGroupStatus& group) {
    json_storage_[group.group_name][RES_STR_] = group.result;
    json_storage_[group.group_name][EXEC_STR_] =
        group.group_execution_time.count();
    for (const TestStatus& test : group.tests_history) {
      AddTestStatus(test);
    }
  }
  void Merge(const TestResult& other) {
    json_storage_.merge_patch(other.json_storage_);
  }
  void SerializeToJson(const std::string& path) const {
    std::ofstream new_file(path);
    new_file << json_storage_;
    new_file.close();
  }
  void DeserializeFromJson(const std::string& path) {
    std::ifstream json_input_file(path);
    if (json_input_file.fail()) {
      std::cerr << "DeserializeFromJson : Incorrect path to file" << '\n';
      return;
    }
    json_storage_ = nlohmann::json::parse(json_input_file);
  }
  TestResult& operator=(const TestResult& other) {
    json_storage_ = other.json_storage_;
    return *this;
  }
  std::unordered_map<std::string, TestGroupStatus> GetTestGroupStatusMap()
      const {
    std::unordered_map<std::string, TestGroupStatus> answer;
    for (auto& group : json_storage_.items()) {
      std::string group_name = group.key();
      answer.insert({group_name, TestGroupStatus(group_name)});
      answer.at(group_name).group_execution_time =
          std::chrono::duration<double>(group.value()[EXEC_STR_]);
      answer.at(group_name).result = group.value()[RES_STR_];
      for (auto& test : group.value()[TESTS_STR_].items()) {
        TestStatus test_temp(test.key(), group_name);
        test_temp.result = test.value()[RES_STR_];
        test_temp.execution_time =
            std::chrono::duration<double>(test.value()[EXEC_STR_]);
        for (auto& command : test.value()[COMMANDS_STR_].items()) {
          test_temp.commands_history.emplace_back(
              command.value()[TYPE_STR_], stoi(command.key()),
              command.value()[ARG_1_STR_], command.value()[ARG_2_STR_],
              command.value()[RES_STR_]);
        }
        answer.at(group_name).tests_history.push_back(test_temp);
      }
    }
    return answer;
  }
  TestResult() = default;
  TestResult(const std::string& path_to_json) {
    DeserializeFromJson(path_to_json);
  }
  TestResult(const TestGroupStatus& group) { AddGroupStatus(group); }
  TestResult(const TestStatus& test) { AddTestStatus(test); }
  ~TestResult() {
    if (auto_save_enabled_) {
      SerializeToJson(path_to_auto_save_);
    }
  }
};

const std::string TestResult::TESTS_STR_ = "tests";
const std::string TestResult::RES_STR_ = "res";
const std::string TestResult::EXEC_STR_ = "exec";
const std::string TestResult::ARG_1_STR_ = "arg_1";
const std::string TestResult::ARG_2_STR_ = "arg_2";
const std::string TestResult::TYPE_STR_ = "type";
const std::string TestResult::COMMANDS_STR_ = "commands";
