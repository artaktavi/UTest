#pragma once

#include <cassert>
#include <iostream>
#include <TestDefine.hpp>
#include <AssertTrueDefine.hpp>

TEST(AssertTrueTest, AssertTests) {
  ASSERT_TRUE((2 * 2) == 4)
}

bool AssertTrueTestBreakFailed = false;

TEST(AssertTrueTestBreak, AssertTests) {
  ASSERT_TRUE((2 * 2) != 4)
  AssertTrueTestBreakFailed = true;
}