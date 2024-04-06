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
  // let's enable all tests auto-saving:
  UTest::ToggleOJsonFile(); // enabled
  UTest::SetOutputJsonFilePath("auto_save_tests.json"); // set the path
  // also it's possible to toggle json saving and set the path in one command:
  // TestIOManager::ToggleOJsonFile("auto_save_tests.json");

  // please note that TestIOManager saves tests result into his buffer
  // automatically only while TestIOManager::IsOJsonFileEnabled();
  // (but saves into file anyway in case it was enabled at least once)

  // now if we execute tests, they will be automatically displayed with cout
  // we can change it by TestIOManager::ToggleOStream();
  UTest::ToggleOStream(); // no output with cout
  UTest::ToggleOCerrStream(); // output with cerr enabled

  std::cerr << "---------- Tests in cerr ----------\n";
  UTest::ExecuteTestAll(); // we will see results in cerr

  UTest::SwitchStreams(); // toggled cerr and toggled cout

  std::cout << "---------- Tests in cout ----------\n";
  UTest::ExecuteTestAll(); // we will see results in cout

  UTest::ToggleOStream(); // cout output disabled

  std::cout << "--------- No tests output ---------\n";
  UTest::ExecuteTestAll();

  // now, after executing main.cpp global objects destructors will be invoked
  // after that results made by executing tests will be saved
  // in "auto_save_tests.json"
  return 0;
}