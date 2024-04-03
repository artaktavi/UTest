#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

namespace ConsoleSettings {

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
      {"boldblack", "\033[1m\033[30m"},
      {"boldred", "\033[1m\033[31m"},
      {"boldgreen", "\033[1m\033[32m"},
      {"boldyellow", "\033[1m\033[33m"},
      {"boldblue", "\033[1m\033[34m"},
      {"boldmagenta", "\033[1m\033[35m"},
      {"boldcyan", "\033[1m\033[36m"},
      {"boldwhite", "\033[1m\033[37m"}};
   bool is_failed_detailed = false;
   bool is_always_detailed = false;
   std::string group_succeed_color = "green";
   std::string group_failed_color = "boldred";
   std::string test_succeed_color = "green";
   std::string test_failed_color = "red";
   std::string common_color = "blue";
   std::string GetColorCode(const std::string& color) noexcept {
     auto it = console_colors.find(color);
     if (it == console_colors.end()) {
       return {};
     }
     return it->second;
   }
}  // namespace ConsoleSettings
