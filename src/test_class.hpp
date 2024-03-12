#ifndef UNITTESTER_TEST_CLASS_HPP
#define UNITTESTER_TEST_CLASS_HPP

class Test {
  virtual void TestBody() = 0;
 public:
  virtual void Execute() final {
    TestBody();
  }
  Test() = default;
  Test(const Test& other) = delete;
};

#endif  //UNITTESTER_TEST_CLASS_HPP
