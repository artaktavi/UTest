
#ifndef UNITTESTER_TEST_REGISTRY_HPP
#define UNITTESTER_TEST_REGISTRY_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "test_class.hpp"

class TestRegistry {
 public:
  static std::unordered_map<std::string, std::unordered_map<std::string, Test*>>
      test_groups_;
  static std::unordered_map<std::string, Test*> test_all_;

  static void AddTest(const std::string& test_name,
                      const std::string& test_group, Test* test) {
    //    !!!!
    //    add checking if test already there is by this address
    //    !!!!
        test_groups_[test_group][test_name] = test;
        test_all_[test_name] = test;
  }
  static void ExecuteTest(const std::string& test_name) noexcept {
        test_all_[test_name]->Execute();
  }
  static void ExecuteTestGroup(const std::string& test_group) noexcept {}
  static void ExecuteTestAll() noexcept {}
};

std::unordered_map<std::string, std::unordered_map<std::string, Test*>>
    TestRegistry::test_groups_;
std::unordered_map<std::string, Test*> TestRegistry::test_all_;

#endif  //UNITTESTER_TEST_REGISTRY_HPP
