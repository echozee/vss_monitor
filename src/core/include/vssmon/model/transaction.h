#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "vssmon/model/event.h"

namespace vssmon {

struct RequesterCandidate {
  std::uint32_t pid{};
  std::string process_name;
  double confidence_score{};  // 0.0 ~ 1.0
  std::vector<std::string> evidence;
};

struct VssTransaction {
  std::string tx_id;
  std::chrono::system_clock::time_point start_time;
  std::optional<std::chrono::system_clock::time_point> end_time;
  std::string op_type;
  std::vector<std::string> volumes;
  std::string result;
  std::vector<RequesterCandidate> requester_candidates;
  std::vector<VssEvent> events;
};

}  // namespace vssmon
