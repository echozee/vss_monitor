#pragma once

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include "vssmon/model/transaction.h"

namespace vssmon {

class CoreFacade {
 public:
  using TransactionCallback = std::function<void(const VssTransaction&)>;

  CoreFacade();
  ~CoreFacade();

  bool Start();
  void Stop();
  void Subscribe(TransactionCallback callback);

 private:
  void RunSyntheticLoop();
  VssTransaction MakeSyntheticTransaction() const;

  std::vector<TransactionCallback> subscribers_;
  std::mutex subscriber_mutex_;
  std::thread worker_;
  std::atomic<bool> running_{false};
};

}  // namespace vssmon
