#ifndef UNITTESTER_TEST_REGISTRY_CLASS_HPP
#define UNITTESTER_TEST_REGISTRY_CLASS_HPP

// Should think about includes and transfer them to common namespace
#include <string>
#include <unordered_map>
#include "test_class.hpp"
#include "test_group_class.hpp"
#include "test_result_class.hpp"

class TestRegistry {
 public:
  static std::unordered_map<std::string, TestGroup> test_groups_;
  static std::unordered_map<std::string, Test*> test_all_;

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
      test_result.AddTestStatus(test_all_[test_name]->Execute());
    } else {
      std::cerr << "ExecuteTest: there is no test known as "
                << test_name << std::endl;
    }
    return test_result;
  }
  static TestResult ExecuteTestGroup(const std::string& group_name) noexcept {
    TestResult test_result;
    if (test_groups_.find(group_name) != test_groups_.end()) {
      test_result.AddGroupStatus(
          test_groups_.find(group_name)->second.Execute());
    } else {
      std::cerr << "ExecuteTestGroup: there is no groups known as "
                << group_name << std::endl;
    }
    return test_result;
  }
  static TestResult ExecuteTestAll() noexcept {
    TestResult tests_result;
    for (std::pair<const std::string, TestGroup>& curr_group : test_groups_) {
      tests_result.AddGroupStatus(curr_group.second.Execute());
    }
    return tests_result;
  }
};

std::unordered_map<std::string, TestGroup> TestRegistry::test_groups_;
std::unordered_map<std::string, Test*> TestRegistry::test_all_;

#endif  //UNITTESTER_TEST_REGISTRY_CLASS_HPP