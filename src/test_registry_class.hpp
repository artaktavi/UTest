#ifndef UNITTESTER_TEST_REGISTRY_CLASS_HPP
#define UNITTESTER_TEST_REGISTRY_CLASS_HPP

// Should think about includes and transfer them to common namespace
#include <string>
#include <unordered_map>
#include "test_class.hpp"
#include "test_group_class.hpp"

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
  static TestStatus ExecuteTest(const std::string& test_name,
                                bool detailed = false) noexcept {
    return test_all_[test_name]->Execute();
  }
  static TestGroupStatus ExecuteTestGroup(const std::string& group_name,
                                          bool detailed = false) noexcept {
    if (test_groups_.find(group_name) != test_groups_.end()) {
      return test_groups_.find(group_name)->second.Execute();
    } else {
      std::cerr << "ExecuteTestGroup: there is no groups known as "
                << group_name << std::endl;
    }
  }
  static std::vector<TestGroupStatus> ExecuteTestAll(
      bool detailed = false) noexcept {
    std::vector<TestGroupStatus> tests_result;
    tests_result.reserve(test_groups_.size());
    for (std::pair<const std::string, TestGroup>& curr_group : test_groups_) {
      tests_result.push_back(curr_group.second.Execute());
    }
    return tests_result;
  }
};

std::unordered_map<std::string, TestGroup> TestRegistry::test_groups_;
std::unordered_map<std::string, Test*> TestRegistry::test_all_;

#endif  //UNITTESTER_TEST_REGISTRY_CLASS_HPP