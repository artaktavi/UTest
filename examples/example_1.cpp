#include <AssertTrueDefine.hpp>
#include <ExpectTrueDefine.hpp>
#include <TestDefine.hpp>

#include <deque>

TEST(DequePtrInvalidation, DequeTests) {
  std::deque<int32_t> deq;
  const int32_t MOD = 42;
  const size_t NEW_DEQUE_SIZE = 1e8;
  deq.push_back(MOD);
  const int32_t& ref = deq[0];
  for (size_t i = 0; i < NEW_DEQUE_SIZE; ++i) {
    deq.push_back(static_cast<int32_t>(i + 1) % MOD);
  }
  ASSERT_TRUE(!deq.empty())
  // if deq is empty code below won't be executed
  const int32_t& new_ref = deq[0];
  ASSERT_TRUE(new_ref == ref)
}

TEST(DequeSize, DequeTests) {
  std::deque<int32_t> deq;
  const size_t NEW_DEQUE_SIZE = 1e8;
  for (size_t i = 0; i < NEW_DEQUE_SIZE; ++i) {
    deq.push_back(static_cast<int32_t>(i + 1));
  }
  ASSERT_TRUE(deq.size() == NEW_DEQUE_SIZE)
}

TEST(IntPlus, IntTests) {
  ASSERT_TRUE(2 + 2 == 5)
}

int main() {
  // you can run tests by their group:
  std::cout << "--------- Tests by groups ------------\n";
  TestRegistry::ExecuteTestGroup("DequeTests");

  // or you can run tests by individually by:
  std::cout << "-------- Tests by individual ---------\n";
  TestRegistry::ExecuteTest("DequeSize");
  TestRegistry::ExecuteTest("DequePtrInvalidation");

  // or run absolutely all tests:
  std::cout << "------------- All tests --------------\n";
  TestRegistry::ExecuteTestAll();
  return 0;
}