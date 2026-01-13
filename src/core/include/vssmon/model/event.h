#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace vssmon {

struct VssEvent {
  std::chrono::system_clock::time_point timestamp;
  std::string provider;
  std::uint32_t event_id{};
  std::string op_type;
  std::optional<std::string> volume_id;
  std::optional<std::string> activity_id;
  std::optional<std::uint32_t> pid;
  std::vector<std::pair<std::string, std::string>> raw_fields;
};

}  // namespace vssmon
