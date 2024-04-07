#pragma once

namespace UTest {
namespace OutputConfig {
bool o_cout_stream_enabled = true;
bool o_cerr_stream_enabled = false;
bool o_json_file_enabled = false;
bool is_failed_detailed = true;
bool is_always_detailed = false;
bool is_command_failed_path_enabled = false;
bool is_test_failed_path_enabled = true;
size_t block_width = 50;
size_t stats_symbols_count = 16;
}  // namespace OutputConfig
}  // namespace UTest