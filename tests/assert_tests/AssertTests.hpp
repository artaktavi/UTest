#include <AssertTrueTest.hpp>

void AssertTests() {
  UTest::TestResult res_1(
      UTestInfrastructure::TestRegistry::ExecuteTest("AssertTrueTest"));
  res_1.SerializeToJson("check.json");
  assert(
      res_1.GetTestGroupStatusMap().begin()->second.tests_history[0].result ==
      UTEST_KEYWORD_PASSED);
  UTest::TestResult res_2(
      UTestInfrastructure::TestRegistry::ExecuteTest("AssertTrueTestBreak"));
  assert(
      res_2.GetTestGroupStatusMap().begin()->second.tests_history[0].result ==
      UTEST_KEYWORD_FAILED);
  assert(AssertTrueTestBreakFailed == false);
  std::cout << " - AssertTests passed.\n";
}
