#ifndef UNITTESTER_STD_COUT_TEST_HPP
#define UNITTESTER_STD_COUT_TEST_HPP

#include <ostream>
#include "test_registry_class.hpp"

std::ostream& operator<<(std::ostream& out_stream,
                         const CommandStatus& command_status) {
  out_stream << command_status.line << ": " << command_status.type << '('
             << command_status.arg_1;
  if (!command_status.arg_2.empty()) {
    out_stream << ", " << command_status.arg_2;
  }
  out_stream << ")  :  " << command_status.result << '\n';
  return out_stream;
}

std::ostream& operator<<(std::ostream& out_stream,
                         const TestStatus& test_status) {
  out_stream << test_status.group_name << '.' << test_status.name << " : "
             << test_status.result << " with "
             << test_status.execution_time.count() << "s\n";
  for (const CommandStatus& command : test_status.commands_history) {
    out_stream << command;
  }
  return out_stream;
}

std::ostream& operator<<(std::ostream& out_stream,
                         const TestGroupStatus& group_status) {
  out_stream << group_status.group_name << " : " << group_status.result
             << " with " << group_status.group_execution_time.count() << "s\n";
  for (const TestStatus& test : group_status.tests_history) {
    out_stream << test;
  }
  return out_stream;
}

#endif  //UNITTESTER_STD_COUT_TEST_HPP
