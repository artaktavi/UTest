#ifndef UNITTESTER_TEST_CLASS_HPP
#define UNITTESTER_TEST_CLASS_HPP

#ifndef UNITTESTER_COMMAND_STATUS_CLASS_HPP
#include "command_status_class.hpp"
#endif

// TEST INCLUDE
//#include <iostream>

class Test {
 private:
  virtual void TestBody() = 0;

 protected:
  void UpdateStatus(CommandStatus command_result) {
//    std::cout << "Command type: " << command_result.type << '\n'
//              << "Command arg_1: " << command_result.arg_1 << '\n'
//              << "Command arg_2: " << command_result.arg_2 << '\n'
//              << "Result: " << command_result.result << '\n'
//              << "Line: " << command_result.line << std::endl;
  }

 public:
  virtual void Execute() final { TestBody(); }
  Test() = default;
  Test(const Test& other) = delete;
};

#endif  //UNITTESTER_TEST_CLASS_HPP
