#ifndef UNITTESTER_COMMAND_STATUS_CLASS_HPP
#define UNITTESTER_COMMAND_STATUS_CLASS_HPP

#include <string>

struct CommandStatus {
  std::string type;
  int line;
  std::string arg_1;
  std::string arg_2;
  std::string result;
  CommandStatus(std::string c_type, int c_line, std::string c_arg_1,
                std::string c_arg_2, std::string c_result)
      : type(c_type),
        line(c_line),
        arg_1(c_arg_1),
        arg_2(c_arg_2),
        result(c_result) {}
  CommandStatus(std::string c_type, int c_line, std::string c_arg_1,
                std::string c_result)
      : type(c_type), line(c_line), arg_1(c_arg_1), result(c_result) {}
};

#endif  //UNITTESTER_COMMAND_STATUS_CLASS_HPP