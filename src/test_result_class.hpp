#ifndef UNITTESTER_TEST_RESULT_CLASS_HPP
#define UNITTESTER_TEST_RESULT_CLASS_HPP

#include "../third_party/json.hpp"
#include "test_group_status_class.hpp"
#include <fstream>

class TestResult {
  static const std::string tests_str_;
  static const std::string res_str_;
  static const std::string exec_str_;
  static const std::string arg_1_str_;
  static const std::string arg_2_str_;
  static const std::string type_str_;
  static const std::string commands_str_;
  nlohmann::json json_storage_;

 public:
  void AddTestStatus(const TestStatus& test) {
    json_storage_[test.group_name][tests_str_][test.name][res_str_] =
        test.result;
    json_storage_[test.group_name][tests_str_][test.name][exec_str_] =
        test.execution_time.count();
    for (const CommandStatus& command : test.commands_history) {
      json_storage_[test.group_name][tests_str_][test.name][commands_str_]
                   [std::to_string(command.line)][type_str_] = command.type;
      json_storage_[test.group_name][tests_str_][test.name][commands_str_]
                   [std::to_string(command.line)][res_str_] = command.result;
      json_storage_[test.group_name][tests_str_][test.name][commands_str_]
                   [std::to_string(command.line)][arg_1_str_] = command.arg_1;
      json_storage_[test.group_name][tests_str_][test.name][commands_str_]
                   [std::to_string(command.line)][arg_2_str_] = command.arg_2;
    }
  }
  void AddGroupStatus(const TestGroupStatus& group) {
    json_storage_[group.group_name][res_str_] = group.result;
    json_storage_[group.group_name][exec_str_] =
        group.group_execution_time.count();
    for (const TestStatus& test : group.tests_history) {
      AddTestStatus(test);
    }
  }
  void Merge(const TestResult& other) {
    json_storage_.merge_patch(other.json_storage_);
  }
  void SerializeToJson(const std::string& path) {
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
  std::unordered_map<std::string, TestGroupStatus> GetTestGroupStatusMap() {
    std::unordered_map<std::string, TestGroupStatus> answer;
    for (auto& group : json_storage_.items()) {
      std::string group_name = group.key();
      answer.insert({group_name, TestGroupStatus(group_name)});
      answer.at(group_name).group_execution_time =
          std::chrono::duration<double>(group.value()[exec_str_]);
      answer.at(group_name).result = group.value()[res_str_];
      for (auto& test : group.value()[tests_str_].items()) {
        TestStatus test_temp(test.key(), group_name);
        test_temp.result = test.value()[res_str_];
        test_temp.execution_time =
            std::chrono::duration<double>(test.value()[exec_str_]);
        for (auto& command : test.value()[commands_str_].items()) {
          test_temp.commands_history.emplace_back(
              command.value()[type_str_], stoi(command.key()),
              command.value()[arg_1_str_], command.value()[arg_2_str_],
              command.value()[res_str_]);
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
};

const std::string TestResult::tests_str_ = "tests";
const std::string TestResult::res_str_ = "res";
const std::string TestResult::exec_str_ = "exec";
const std::string TestResult::arg_1_str_ = "arg_1";
const std::string TestResult::arg_2_str_ = "arg_2";
const std::string TestResult::type_str_ = "type";
const std::string TestResult::commands_str_ = "commands";

#endif  //UNITTESTER_TEST_RESULT_CLASS_HPP
