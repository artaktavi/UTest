#ifndef UNITTESTER_TEST_CLASS_HPP
#define UNITTESTER_TEST_CLASS_HPP

class Test {
  virtual void TestBody() = 0;
 public:
  Test() = default;
  Test(const Test& other) = default;
  Test& operator=(const Test& other) {
    return *this;
  }
};

#endif  //UNITTESTER_TEST_CLASS_HPP
