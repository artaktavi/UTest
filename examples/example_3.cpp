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
  TestIOManager::ToggleOJsonFile(); // enabled
  TestIOManager::SetOutputJsonFilePath("auto_save_tests.json"); // set the path
  // also it's possible to toggle json saving and set the path in one command:
  // TestIOManager::ToggleOJsonFile("auto_save_tests.json");

  // please note that TestIOManager saves tests result into his buffer
  // automatically only while TestIOManager::IsOJsonFileEnabled();
  // (but saves into file anyway in case it was enabled at least once)

  // now if we execute tests, they will be automatically displayed with cout
  // we can change it by TestIOManager::ToggleOStream();
  TestIOManager::ToggleOStream(); // no output with cout
  TestIOManager::ToggleOCerrStream(); // output with cerr enabled

  std::cerr << "---------- Tests in cerr ----------\n";
  TestRegistry::ExecuteTestAll(); // we will see results in cerr

  TestIOManager::SwitchStreams(); // toggled cerr and toggled cout

  std::cout << "---------- Tests in cout ----------\n";
  TestRegistry::ExecuteTestAll(); // we will see results in cout

  TestIOManager::ToggleOStream(); // cout output disabled

  std::cout << "--------- No tests output ---------\n";
  TestRegistry::ExecuteTestAll();

  // now, after executing main.cpp global objects destructors will be invoked
  // after that results made by executing tests will be saved
  // in "auto_save_tests.json"
  return 0;
}