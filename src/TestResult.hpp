#pragma once

#include <fstream>

#include <json.hpp>

#include <TestGroupStatus.hpp>

namespace UTest {
class TestResult {
  static const std::string TESTS_STR_;
  static const std::string RES_STR_;
  static const std::string EXEC_STR_;
  static const std::string GROUP_STR_;
  static const std::string ARG_1_STR_;
  static const std::string ARG_2_STR_;
  static const std::string TYPE_STR_;
  static const std::string COMMANDS_STR_;
  static const std::string LINE_STR_;
  static const std::string PATH_STR_;
  nlohmann::json json_storage_;
  std::string path_to_auto_save_ = "unit_tester_report.json";
  bool auto_save_enabled_ = false;
  /*
  TestStatus ConstructTestStatus(nlohmann::json::const_iterator& it) const {
    TestStatus new_test_status(it.key(), it.value()[GROUP_STR_]);
    new_test_status.result = it.value()[RES_STR_];
    new_test_status.execution_time =
        std::chrono::duration<double>(it.value()[EXEC_STR_]);
    for (auto& command : it.value()[COMMANDS_STR_].items()) {
      new_test_status.commands_history.emplace_back(
          command.value()[TYPE_STR_], stoi(command.key()),
          command.value()[ARG_1_STR_], command.value()[ARG_2_STR_],
          command.value()[RES_STR_]);
    }
    return new_test_status;
  }
  TestGroupStatus ConstructTestGroupStatus(const nlohmann::json::const_iterator& it) const {
    TestGroupStatus new_group_status(it.key());

  }
  */

 public:
  void ToggleAutoSave() { auto_save_enabled_ = !auto_save_enabled_; }
  bool IsAutoSaveEnabled() const { return auto_save_enabled_; }
  void SetPathToAutoSave(const std::string& path) { path_to_auto_save_ = path; }
  void AddTestStatus(const TestStatus& test) {
    if (json_storage_.find(test.group_name) == json_storage_.end()) {
      json_storage_[test.group_name][RES_STR_] = UTEST_KEYWORD_UNDEFINED_RESULT;
      json_storage_[test.group_name][EXEC_STR_] = 0.0;
    }
    json_storage_[test.group_name][TESTS_STR_][test.name][RES_STR_] =
        test.result;
    json_storage_[test.group_name][TESTS_STR_][test.name][EXEC_STR_] =
        test.execution_time.count();
    json_storage_[test.group_name][TESTS_STR_][test.name][GROUP_STR_] =
        test.group_name;
    json_storage_[test.group_name][TESTS_STR_][test.name][PATH_STR_] =
        test.path;
    json_storage_[test.group_name][TESTS_STR_][test.name][LINE_STR_] =
        test.line;
    for (const CommandStatus& command : test.commands_history) {
      std::string command_line_tmp = std::to_string(command.line);
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [command_line_tmp][TYPE_STR_] = command.type;
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [command_line_tmp][RES_STR_] = command.result;
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [command_line_tmp][ARG_1_STR_] = command.arg_1;
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [command_line_tmp][ARG_2_STR_] = command.arg_2;
      json_storage_[test.group_name][TESTS_STR_][test.name][COMMANDS_STR_]
                   [command_line_tmp][PATH_STR_] = command.path;
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
  void SerializeToJson(std::string path = "") const {
    if (path.empty()) {
      path = path_to_auto_save_;
    }
    std::ofstream new_file(path, std::ios::out);
    new_file << json_storage_;
    new_file << std::flush;
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
        TestStatus test_temp(test.key(), group_name, test.value()[LINE_STR_],
                             test.value()[PATH_STR_]);
        test_temp.result = test.value()[RES_STR_];
        test_temp.execution_time =
            std::chrono::duration<double>(test.value()[EXEC_STR_]);
        for (auto& command : test.value()[COMMANDS_STR_].items()) {
          test_temp.commands_history.emplace_back(
              command.value()[TYPE_STR_], stoi(command.key()),
              command.value()[PATH_STR_], command.value()[ARG_1_STR_],
              command.value()[ARG_2_STR_], command.value()[RES_STR_]);
        }
        answer.at(group_name).tests_history.push_back(test_temp);
        // answer.at(group_name).tests_history.push_back(std::move(ConstructTestGroupStatus(test)));
      }
    }
    return answer;
  }
  //  TestGroupStatus GetTestGroupStatus(const std::string& group_name) const {
  //    auto it = json_storage_.find(group_name);
  //    if (it != json_storage_.end()) {
  //      it.value();
  //    } else {
  //      std::cerr << "Error: UTest: TestResult: GetTestGroupStatus: there is no "
  //                   "group with given name"
  //                << std::endl;
  //    }
  //  }
  //  TestStatus GetTestStatus(const std::string& test_name) const {}
  TestResult& operator=(const TestResult& other) {
    json_storage_ = other.json_storage_;
    return *this;
  }
  TestResult() = default;
  TestResult(const std::string& path_to_json) {
    DeserializeFromJson(path_to_json);
  }
  TestResult(const TestResult& other) = default;
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
const std::string TestResult::GROUP_STR_ = "group_name";
const std::string TestResult::LINE_STR_ = "line";
const std::string TestResult::PATH_STR_ = "path";
}  // namespace UTest