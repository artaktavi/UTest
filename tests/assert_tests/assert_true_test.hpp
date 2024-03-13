#ifndef UNITTESTER_ASSERT_TRUE_TEST_HPP
#define UNITTESTER_ASSERT_TRUE_TEST_HPP

#include <cassert>
#include <iostream>
#include "../../src/asserts/assert_true_define.hpp"
#include "../../src/test_define.hpp"

TEST(AssertTrueTest, AssertTests) {
  ASSERT_TRUE((2 * 2) == 4)
}

bool AssertTrueTestBreakFailed = false;

TEST(AssertTrueTestBreak, AssertTests) {
  ASSERT_TRUE((2 * 2) != 4)
  AssertTrueTestBreakFailed = true;
}

#endif  //UNITTESTER_ASSERT_TRUE_TEST_HPP
