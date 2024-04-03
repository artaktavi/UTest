#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

namespace ConsoleColorsConfig {

  const std::unordered_map<std::string, std::string> console_colors = {
     {"reset", "\033[0m"},
     {"black", "\033[30m"},
     {"red", "\033[31m"},
     {"green", "\033[32m"},
     {"yellow", "\033[33m"},
     {"blue", "\033[34m"},
     {"magenta", "\033[35m"},
     {"cyan", "\033[36m"},
     {"white", "\033[37m"},
     {"brightblack", "\033[1m\033[30m"},
     {"brightred", "\033[1m\033[31m"},
     {"brightgreen", "\033[1m\033[32m"},
     {"brightyellow", "\033[1m\033[33m"},
     {"brightblue", "\033[1m\033[34m"},
     {"brightmagenta", "\033[1m\033[35m"},
     {"brightcyan", "\033[1m\033[36m"},
     {"brightwhite", "\033[1m\033[37m"}};
  std::string group_passed_color = "green";
  std::string group_failed_color = "red";
  std::string test_start_color = "blue";
  std::string test_passed_color = "green";
  std::string test_failed_color = "red";
  std::string common_color = "blue";
  std::string command_passed_color = "yellow";
  std::string command_failed_color = "red";
  std::string command_fatal_failed_color = "red";
  std::string GetColorCode(const std::string& color) noexcept {
    auto it = console_colors.find(color);
    if (it == console_colors.end()) {
      return {};
    }
    return it->second;
  }
}  // namespace ConsoleSettings
