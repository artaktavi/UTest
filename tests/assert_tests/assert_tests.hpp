#ifndef UNITTESTER_ASSERT_TESTS_HPP
#define UNITTESTER_ASSERT_TESTS_HPP

#include "assert_true_test.hpp"

void AssertTests() {
  TestStatus res_1(TestRegistry::ExecuteTest("AssertTrueTest"));
  assert(res_1.result == "succeed");
  TestStatus res_2(TestRegistry::ExecuteTest("AssertTrueTestBreak"));
  assert(res_2.result == "failed");
  assert(AssertTrueTestBreakFailed == false);
  std::cout << "AssertTests passed.\n";
}

#endif  //UNITTESTER_ASSERT_TESTS_HPP
