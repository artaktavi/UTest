#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

struct ConsoleColor {
  static const std::unordered_map<std::string, std::string> console_colors_;
  static std::string group_succeed_color_;
  static std::string group_failed_color_;
  static std::string test_succeed_color_;
  static std::string test_failed_color_;
  static std::string GetColorCode(const std::string& color) noexcept {
    auto it = console_colors_.find(color);
    if (it == console_colors_.end()) {
      return std::string();
    }
    return it->second;
  }
};

std::string ConsoleColor::group_succeed_color_ = "green";
std::string ConsoleColor::group_failed_color_ = "boldred";
std::string ConsoleColor::test_succeed_color_ = "green";
std::string ConsoleColor::test_failed_color_ = "red";
const std::unordered_map<std::string, std::string> ConsoleColor::console_colors_ = {
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
    {"boldwhite", "\033[1m\033[37m"}
};