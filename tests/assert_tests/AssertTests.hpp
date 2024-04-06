#include <AssertTrueTest.hpp>

void AssertTests() {
  UTest::TestResult res_1(UTest::ExecuteTest("AssertTrueTest"));
  res_1.SerializeToJson("check.json");
  assert(
      res_1.GetTestGroupStatusMap().begin()->second.tests_history[0].result ==
      UTEST_KEYWORD_PASSED);
  UTest::TestResult res_2(UTest::ExecuteTest("AssertTrueTestBreak"));
  assert(
      res_2.GetTestGroupStatusMap().begin()->second.tests_history[0].result ==
      UTEST_KEYWORD_FAILED);
  assert(AssertTrueTestBreakFailed == false);
  std::cout << " - AssertTests passed.\n";
}
