#pragma once

#include <atomic>
#include <memory>
#include <optional>
#include <windows.h>

#include "UiModel.h"
#include "vssmon/core_facade.h"

constexpr UINT kUiUpdateMessage = WM_APP + 1;

class CoreUiBridge {
 public:
  CoreUiBridge();
  ~CoreUiBridge();

  bool Start();
  void Stop();
  void SetNotifyHwnd(HWND hwnd);
  UiModel& model() { return model_; }

 private:
  void EmitSynthetic();

  vssmon::CoreFacade core_;
  UiModel model_;
  std::atomic<HWND> notify_hwnd_{nullptr};
};
