#ifndef UNITTESTER_TEST_RESULT_CLASS_HPP
#define UNITTESTER_TEST_RESULT_CLASS_HPP

#include "../third_party/json.hpp"
#include "test_group_status_class.hpp"

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
  TestResult(const TestGroupStatus& group) { AddGroupStatus(group); }
};

const std::string TestResult::tests_str_ = "tests";
const std::string TestResult::res_str_ = "res";
const std::string TestResult::exec_str_ = "exec";
const std::string TestResult::arg_1_str_ = "arg_1";
const std::string TestResult::arg_2_str_ = "arg_2";
const std::string TestResult::type_str_ = "type";
const std::string TestResult::commands_str_ = "commands";

#endif  //UNITTESTER_TEST_RESULT_CLASS_HPP
