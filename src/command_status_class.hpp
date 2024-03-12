#ifndef UNITTESTER_COMMAND_STATUS_CLASS_HPP
#define UNITTESTER_COMMAND_STATUS_CLASS_HPP

#include <string>

struct CommandStatus {
  std::string type;
  std::string line;
  std::string arg_1;
  std::string arg_2;
  std::string result;
  CommandStatus(const std::string& c_type, const std::string& c_line,
                const std::string& c_arg_1, const std::string& c_arg_2,
                const std::string& c_result)
      : type(c_type),
        line(c_line),
        arg_1(c_arg_1),
        arg_2(c_arg_2),
        result(c_result) {}
  CommandStatus(const std::string& c_type, const std::string& c_line,
                const std::string& c_arg_1, const std::string& c_result)
      : type(c_type), line(c_line), arg_1(c_arg_1), result(c_result) {}
};

#endif  //UNITTESTER_COMMAND_STATUS_CLASS_HPP
