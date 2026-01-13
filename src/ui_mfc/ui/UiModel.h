#pragma once

#include <mutex>
#include <vector>

#include "vssmon/model/transaction.h"

class UiModel {
 public:
  void AppendTransaction(const vssmon::VssTransaction& tx);
  std::vector<vssmon::VssTransaction> Snapshot() const;

 private:
  mutable std::mutex mutex_;
  std::vector<vssmon::VssTransaction> transactions_;
};
