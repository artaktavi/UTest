#pragma once

#include <unordered_map>

#include "test_group_class.hpp"
#include "test_io_manager_class.hpp"

class TestRegistry {
  static std::unordered_map<std::string, TestGroup> test_groups_;
  static std::unordered_map<std::string, Test*> test_all_;
 public:

  static void RegisterTest(const std::string& name,
                           const std::string& group_name, Test* test) {
    //    !!!!
    //    add checking if test already there is by this address
    //    !!!!
    if (test_groups_.find(group_name) == test_groups_.end()) {
      test_groups_.insert({group_name, TestGroup(group_name)});
    }
    test_groups_.find(group_name)->second.AddTest(test);
    test_all_[name] = test;
  }
  static TestResult ExecuteTest(const std::string& test_name) noexcept {
    TestResult test_result;
    if (test_all_.find(test_name) != test_all_.end()) {
      TestStatus test_status_temp(test_all_[test_name]->Execute());
      TestIOManager::OutputTestStatus(test_status_temp);
      test_result.AddTestStatus(test_status_temp);
    } else {
      std::cerr << "ExecuteTest: there is no test known as " << test_name
                << std::endl;
    }
    return test_result;
  }
  static TestResult ExecuteTestGroup(const std::string& group_name) noexcept {
    TestResult test_result;
    if (test_groups_.find(group_name) != test_groups_.end()) {
      TestGroupStatus group_status_temp(
          test_groups_.find(group_name)->second.Execute());
      TestIOManager::OutputGroupStatus(group_status_temp);
      test_result.AddGroupStatus(group_status_temp);
    } else {
      std::cerr << "ExecuteTestGroup: there is no groups known as "
                << group_name << std::endl;
    }
    return test_result;
  }
  static TestResult ExecuteTestAll() noexcept {
    TestResult tests_result;
    for (std::pair<const std::string, TestGroup>& curr_group : test_groups_) {
      TestGroupStatus group_status_temp(curr_group.second.Execute());
      TestIOManager::OutputGroupStatus(group_status_temp);
      tests_result.AddGroupStatus(group_status_temp);
    }
    return tests_result;
  }
};

std::unordered_map<std::string, TestGroup> TestRegistry::test_groups_;
std::unordered_map<std::string, Test*> TestRegistry::test_all_;
