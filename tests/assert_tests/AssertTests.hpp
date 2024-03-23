#include <AssertTrueTest.hpp>

void AssertTests() {
  TestResult res_1(TestRegistry::ExecuteTest("AssertTrueTest"));
  res_1.SerializeToJson("check.json");
  assert(
      res_1.GetTestGroupStatusMap().begin()->second.tests_history[0].result ==
      "succeed");
  TestResult res_2(TestRegistry::ExecuteTest("AssertTrueTestBreak"));
  assert(
      res_2.GetTestGroupStatusMap().begin()->second.tests_history[0].result ==
      "failed");
  assert(AssertTrueTestBreakFailed == false);
  std::cout << "AssertTests passed.\n";
}
