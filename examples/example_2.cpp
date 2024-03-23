#include "AssertTrueDefine.hpp"
#include "ExpectTrueDefine.hpp"
#include "TestDefine.hpp"

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
  EXPECT_TRUE(Fact(4) == 24)
  EXPECT_TRUE(Fact(6) == 720)
}

TEST(SDefaultFields, Structs) {
  S s;
  EXPECT_TRUE(s.a == 0)
  EXPECT_TRUE(s.b == 0)
}

int main() {
  TestResult functions_tests = TestRegistry::ExecuteTestGroup("Functions");
  functions_tests.SerializeToJson("example_2_functions.json");
  TestResult structs_tests = TestRegistry::ExecuteTestGroup("Structs");
  structs_tests.SerializeToJson("example_2_structs.json");
  TestResult all_tests = structs_tests;
  all_tests.Merge(functions_tests);
  all_tests.SerializeToJson("example_2_tests.json");
  return 0;
}