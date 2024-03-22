#pragma once

#include <string>

struct CommandStatus {
  std::string type;
  int line;
  std::string arg_1;
  std::string arg_2;
  std::string result;
  CommandStatus(std::string c_type, int c_line, std::string c_arg_1,
                std::string c_arg_2, std::string c_result)
      : type(std::move(c_type)),
        line(c_line),
        arg_1(std::move(c_arg_1)),
        arg_2(std::move(c_arg_2)),
        result(std::move(c_result)) {}
  CommandStatus(std::string c_type, int c_line, std::string c_arg_1,
                std::string c_result)
      : type(std::move(c_type)),
        line(c_line),
        arg_1(std::move(c_arg_1)),
        result(std::move(c_result)) {}
};
