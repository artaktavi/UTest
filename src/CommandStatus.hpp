#pragma once

#include <string>

struct CommandStatus {
  std::string type;
  uint32_t line;
  std::string arg_1;
  std::string arg_2;
  std::string result;
  std::string path;
  CommandStatus(std::string c_type, uint32_t c_line, std::string path, std::string c_arg_1,
                std::string c_arg_2, std::string c_result)
      : type(std::move(c_type)),
        line(c_line),
        arg_1(std::move(c_arg_1)),
        arg_2(std::move(c_arg_2)),
        result(std::move(c_result)), path(std::move(path)) {}
  CommandStatus(std::string c_type, uint32_t c_line, std::string path, std::string c_arg_1,
                std::string c_result)
      : type(std::move(c_type)),
        line(c_line),
        arg_1(std::move(c_arg_1)),
        result(std::move(c_result)), path(std::move(path)) {}
};
