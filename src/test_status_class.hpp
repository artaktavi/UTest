#ifndef UNITTESTER_TEST_STATUS_CLASS_HPP
#define UNITTESTER_TEST_STATUS_CLASS_HPP

//Includes to think about
#include <chrono>
#include <vector>
#include "command_status_class.hpp"

struct TestStatus {
  std::string name;
  std::string group_name;
  std::vector<CommandStatus> commands_history;
  std::chrono::duration<double> execution_time;
  std::string result;
  TestStatus() = delete;
  //  TestStatus(std::string name, std::string group,
  //             std::vector<CommandStatus>& commands_history,
  //             std::chrono::duration<double> execution_time, std::string result)
  //      : name(std::move(name)),
  //        group_name(std::move(group)),
  //        commands_history(commands_history),
  //        execution_time(execution_time),
  //        result(std::move(result)) {}
  TestStatus(std::string name, std::string group_name)
      : name(std::move(name)), group_name(std::move(group_name)) {}
  TestStatus(const TestStatus& other) = default;
};

#endif  //UNITTESTER_TEST_STATUS_CLASS_HPP
