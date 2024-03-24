#include <AssertTrueDefine.hpp>
#include <ExpectTrueDefine.hpp>
#include <TestDefine.hpp>

int Fib(int num) {
  if (num < 2) {
    return num;
  }
  return Fib(num - 1) + Fib(num - 2);
}

int Fact(int num) {
  return num <= 1 ? num : Fact(num - 1 ) * num;
}

struct S {
  int a;
  int b;
  S() = default;
};

TEST(Fibonacci, Functions) {
  EXPECT_TRUE(Fib(1) == 1)
  EXPECT_TRUE(Fib(5) == 5)
  EXPECT_TRUE(Fib(20) == 6765)
}

TEST(Factorial, Functions) {
  ASSERT_TRUE(Fact(0) == 1)
  // assert above will be failed, so next expects won't be checked
  EXPECT_TRUE(Fact(4) == 24)
  EXPECT_TRUE(Fact(6) == 720)
}

TEST(SDefaultFields, Structs) {
  S s;
  EXPECT_TRUE(s.a == 0)
  EXPECT_TRUE(s.b == 0)
}

int main() {
  // get info from "Functions" tests group
  TestResult functions_tests = TestRegistry::ExecuteTestGroup("Functions");

  // saving them into json file
  functions_tests.SerializeToJson("example_2_functions.json");

  // get info from "Structs" tests group
  TestResult structs_tests = TestRegistry::ExecuteTestGroup("Structs");

  // saving into json file
  structs_tests.SerializeToJson("example_2_structs.json");

  // creating TestResult object from "example_2_structs.json"
  TestResult all_tests;
  all_tests.DeserializeFromJson("example_2_structs.json");

  // merging "Functions" tests group into "Structs"
  all_tests.Merge(functions_tests);

  // saving all tests we have
  all_tests.SerializeToJson("example_2_tests.json");

  return 0;
}