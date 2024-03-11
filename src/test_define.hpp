#ifndef UNITTESTER_TEST_DEFINE_HPP
#define UNITTESTER_TEST_DEFINE_HPP

#include "test_registry.hpp"

#define TEST(test_name, test_group)                                            \
class test_name : Test {                                                     \
  public:                                                                     \
    test_name() {                                                              \
      TestRegistry::AddTest(std::string(#test_name), std::string(#test_group), \
                            std::dynamic_cast<Test*>(this));                                            \
    }                                                                          \
    void TestBody() override;                                                  \
};                                                                              \
test_name Test##test_name;                                                     \
void test_name::TestBody()

#endif  //UNITTESTER_TEST_DEFINE_HPP
