#ifndef UNITTESTER_TEST_STATUS_CLASS_HPP
#define UNITTESTER_TEST_STATUS_CLASS_HPP

//Includes to think about
#include <vector>
#include "command_status_class.hpp"

struct TestStatus {
  std::vector<CommandStatus>& commands_history;
  std::string result;
  TestStatus(std::vector<CommandStatus>& commands_history, std::string result)
      : commands_history(commands_history), result(result) {}
};

#endif  //UNITTESTER_TEST_STATUS_CLASS_HPP
