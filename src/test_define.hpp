#ifndef UNITTESTER_TEST_DEFINE_HPP
#define UNITTESTER_TEST_DEFINE_HPP

#include "test_registry.hpp"

#define TEST(test_name, test_group)                     \
  class test_name : public Test {                       \
   public:                                              \
    test_name() {                                       \
      TestRegistry::AddTest(#test_name, #test_group,    \
                            dynamic_cast<Test*>(this)); \
    }                                                   \
    void TestBody() override;                           \
  };                                                    \
  test_name Test##test_name;                            \
  void test_name::TestBody()

#endif  //UNITTESTER_TEST_DEFINE_HPP
