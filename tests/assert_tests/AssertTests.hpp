#include <AssertTrueTest.hpp>

void AssertTests() {
  TestResult res_1(TestRegistry::ExecuteTest("AssertTrueTest"));
  res_1.SerializeToJson("check.json");
  assert(
      res_1.GetTestGroupStatusMap().begin()->second.tests_history[0].result ==
      KEYWORD_PASSED);
  TestResult res_2(TestRegistry::ExecuteTest("AssertTrueTestBreak"));
  assert(
      res_2.GetTestGroupStatusMap().begin()->second.tests_history[0].result ==
      KEYWORD_FAILED);
  assert(AssertTrueTestBreakFailed == false);
  std::cout << " - AssertTests passed.\n";
}
