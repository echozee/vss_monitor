#pragma once

#include <afxwin.h>

#include "UiModel.h"

class CTimelineView : public CWnd {
 public:
  void SetModel(UiModel* model);

 protected:
  afx_msg void OnPaint();

  DECLARE_MESSAGE_MAP()

 private:
  UiModel* model_ = nullptr;
};
