#include "vssmon/core_facade.h"

#include <chrono>
#include <atomic>
#include <iomanip>
#include <sstream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

namespace vssmon {

CoreFacade::CoreFacade() = default;
CoreFacade::~CoreFacade() { Stop(); }

bool CoreFacade::Start() {
  bool expected = false;
  if (!running_.compare_exchange_strong(expected, true)) {
    return false;  // already running
  }
  worker_ = std::thread([this]() { RunSyntheticLoop(); });
  return true;
}

void CoreFacade::Stop() {
  bool expected = true;
  if (!running_.compare_exchange_strong(expected, false)) {
    running_ = false;
  }
  if (worker_.joinable()) {
    worker_.join();
  }
}

void CoreFacade::Subscribe(TransactionCallback callback) {
  std::lock_guard<std::mutex> lock(subscriber_mutex_);
  subscribers_.push_back(std::move(callback));
}

void CoreFacade::RunSyntheticLoop() {
  while (running_) {
    VssTransaction tx = MakeSyntheticTransaction();

    std::vector<TransactionCallback> callbacks;
    {
      std::lock_guard<std::mutex> lock(subscriber_mutex_);
      callbacks = subscribers_;
    }

    for (auto& cb : callbacks) {
      if (cb) {
        cb(tx);
      }
    }

    std::this_thread::sleep_for(1s);
  }
}

VssTransaction CoreFacade::MakeSyntheticTransaction() const {
  static std::atomic<std::uint64_t> counter{1};
  const auto now = std::chrono::system_clock::now();

  VssEvent create_event{};
  create_event.timestamp = now;
  create_event.provider = "vssvc";
  create_event.event_id = 100u;
  create_event.op_type = "SnapshotCreate";
  create_event.volume_id = std::string{"C:"};
  create_event.pid = 4321u;
  create_event.raw_fields.push_back({"detail", "synthetic"});

  RequesterCandidate requester{};
  requester.pid = 4321u;
  requester.process_name = "backup_tool.exe";
  requester.confidence_score = 0.82;
  requester.evidence = {"time proximity", "known requester"};

  VssTransaction tx{};
  {
    std::ostringstream oss;
    oss << "tx-" << counter.fetch_add(1);
    tx.tx_id = oss.str();
  }
  tx.start_time = now;
  tx.end_time = now + 250ms;
  tx.op_type = "Snapshot";
  tx.volumes = {"C:"};
  tx.result = "Success";
  tx.requester_candidates.push_back(std::move(requester));
  tx.events.push_back(std::move(create_event));

  return tx;
}

}  // namespace vssmon
