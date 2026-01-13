#include "UiModel.h"

void UiModel::AppendTransaction(const vssmon::VssTransaction& tx) {
  std::lock_guard<std::mutex> lock(mutex_);
  transactions_.push_back(tx);
}

std::vector<vssmon::VssTransaction> UiModel::Snapshot() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return transactions_;
}
