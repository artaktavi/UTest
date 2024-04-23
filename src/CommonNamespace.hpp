#pragma once

#include <TestDefine.hpp>

namespace UTest {

TestResult ExecuteTest(const std::string& test_name) noexcept {
  return UTestInfrastructure::TestRegistry::ExecuteTest(test_name);
}

TestResult ExecuteTestGroup(const std::string& group_name) noexcept {
  return UTestInfrastructure::TestRegistry::ExecuteTestGroup(group_name);
}

TestResult ExecuteTestAll() noexcept {
  return UTestInfrastructure::TestRegistry::ExecuteTestAll();
}

void ToggleOStream() noexcept {
  OutputConfig::o_cout_stream_enabled = !OutputConfig::o_cout_stream_enabled;
}

void ToggleOCerrStream() noexcept {
  OutputConfig::o_cerr_stream_enabled = !OutputConfig::o_cerr_stream_enabled;
}

void SwitchStreams() noexcept {
  ToggleOStream();
  ToggleOCerrStream();
}

void ToggleOJsonFile(const std::string& new_path = "") noexcept {
  UTestInfrastructure::TestIOManager::ToggleOJsonFile(new_path);
}

bool IsOStreamEnabled() noexcept {
  return OutputConfig::o_cout_stream_enabled;
}

bool IsOCerrStreamEnabled() noexcept {
  return OutputConfig::o_cerr_stream_enabled;
}

bool IsOJsonFileEnabled() noexcept {
  return OutputConfig::o_json_file_enabled;
}

void SetOutputJsonFilePath(const std::string& new_path) noexcept {
  UTestInfrastructure::TestIOManager::SetOutputJsonFilePath(new_path);
}

}  // namespace UTest
