#ifndef UNITTESTER_TEST_REGISTRY_CLASS_HPP
#define UNITTESTER_TEST_REGISTRY_CLASS_HPP

// Should think about includes and transfer them to common namespace
#include <string>
#include <unordered_map>
#include "test_class.hpp"

class TestRegistry {
 public:
  static std::unordered_map<std::string, std::unordered_map<std::string, Test*>>
      test_groups_;
  static std::unordered_map<std::string, Test*> test_all_;

  static void RegisterTest(const std::string& test_name,
                           const std::string& test_group, Test* test) {
    //    !!!!
    //    add checking if test already there is by this address
    //    !!!!
    test_groups_[test_group][test_name] = test;
    test_all_[test_name] = test;
  }
  static void ExecuteTest(const std::string& test_name,
                          bool detailed = false) noexcept {
    test_all_[test_name]->Execute();
  }
  static void ExecuteTestGroup(const std::string& test_group,
                               bool detailed = false) noexcept {
    for (std::pair<std::string, Test*> curr_test : test_groups_[test_group]) {
      curr_test.second->Execute();
    }
  }
  static void ExecuteTestAll(bool detailed = false) noexcept {
    for (std::pair<std::string, Test*> curr_test : test_all_) {
      TestStatus curr_test_res(curr_test.second->Execute());
      std::cout << "TEST: " << curr_test.first << " " << curr_test_res.result
                << " with " << curr_test_res.execution_time.count() << "s\n";
      // OR to customize time ratio:
      //                << std::chrono::duration_cast<std::chrono::microseconds>(
      //                       curr_test_res.execution_time).count() << "micros\n";
    }
  }
};

std::unordered_map<std::string, std::unordered_map<std::string, Test*>>
    TestRegistry::test_groups_;
std::unordered_map<std::string, Test*> TestRegistry::test_all_;

#endif  //UNITTESTER_TEST_REGISTRY_CLASS_HPP