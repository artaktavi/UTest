#include <UTest.hpp>

#define UNREACHABLE \
  abort();

int64_t Fib(int64_t num) {
  if (num < 2) {
    return num;
  }
  int64_t prev = 0;
  int64_t last = 1;
  --num;
  while (num > 0) {
    last += prev;
    prev = last - prev;
    --num;
  }
  return last;
}

int64_t Fact(int64_t num) {
  if (num < 2) {
    return 1;
  }
  int64_t tmp = 1;
  for (int64_t ind = 2; ind <= num; ++ind) {
    tmp *= ind;
  }
  return tmp;
}

struct S {
  int32_t a;
  int32_t b;
  S() = default;
};

TEST(Fibonacci, Functions) {
  EXPECT_TRUE(Fib(1) == 1)
  EXPECT_TRUE(Fib(5) == 5)
  EXPECT_TRUE(Fib(20) == 6765)
}

TEST(Factorial, Functions) {
  EXPECT_TRUE(false)
  // expect above will be failed, but it won't affect the code below
  ASSERT_TRUE(false)
  // assert above will be failed, so next expects won't be checked
  UNREACHABLE
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
  UTest::TestResult functions_tests = UTest::ExecuteTestGroup("Functions");

  // saving them into json file
  functions_tests.SerializeToJson("example_2_functions.json");

  // get info from "Structs" tests group
  UTest::TestResult structs_tests = UTest::ExecuteTestGroup("Structs");

  // saving into json file
  structs_tests.SerializeToJson("example_2_structs.json");

  // creating UTest::TestResult object from "example_2_structs.json"
  UTest::TestResult all_tests;
  all_tests.DeserializeFromJson("example_2_structs.json");

  // merging "Functions" tests group into "Structs"
  all_tests.Merge(functions_tests);

  // saving all tests we have
  all_tests.SerializeToJson("example_2_tests.json");

  return 0;
}