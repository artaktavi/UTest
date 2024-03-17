#ifndef UNITTESTER_TEST_DEFINE_HPP
#define UNITTESTER_TEST_DEFINE_HPP

#ifndef UNITTESTER_TEST_REGISTRY_CLASS_HPP
#include "test_registry_class.hpp"
#endif

#define TEST(test_name, test_group)                          \
  class test_name : public Test {                            \
   public:                                                   \
    test_name() : Test(#test_name, #test_group) {            \
      TestRegistry::RegisterTest(#test_name, #test_group,    \
                                 dynamic_cast<Test*>(this)); \
    }                                                        \
    void TestBody() override;                                \
  };                                                         \
  test_name Test##test_name;                                 \
  void test_name::TestBody()

#endif  //UNITTESTER_TEST_DEFINE_HPP
