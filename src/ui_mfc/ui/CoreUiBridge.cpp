#include "CoreUiBridge.h"

CoreUiBridge::CoreUiBridge() = default;

CoreUiBridge::~CoreUiBridge() { Stop(); }

bool CoreUiBridge::Start() {
  bool started = core_.Start();
  if (!started) {
    return false;
  }

  core_.Subscribe([this](const vssmon::VssTransaction& tx) {
    model_.AppendTransaction(tx);
    if (HWND hwnd = notify_hwnd_.load()) {
      ::PostMessage(hwnd, kUiUpdateMessage, 0, 0);
    }
  });
  return true;
}

void CoreUiBridge::Stop() { core_.Stop(); }

void CoreUiBridge::SetNotifyHwnd(HWND hwnd) { notify_hwnd_.store(hwnd); }
