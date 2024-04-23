#pragma once

#include <TestRegistry.hpp>

#define TEST(test_name, test_group)                           \
  namespace UTestInfrastructure {                             \
                                                              \
  class TestClass##test_name : public Test {                  \
   public:                                                    \
    TestClass##test_name()                                    \
        : Test(#test_name, #test_group, __LINE__, __FILE__) { \
                                                              \
      TestRegistry::RegisterTest(#test_name, #test_group,     \
                                 dynamic_cast<Test*>(this));  \
    }                                                         \
                                                              \
    void TestBody() override;                                 \
  };                                                          \
                                                              \
  TestClass##test_name Test##test_name;                       \
  }                                                           \
                                                              \
  void UTestInfrastructure::TestClass##test_name::TestBody()
