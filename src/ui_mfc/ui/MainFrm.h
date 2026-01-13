#pragma once

#include <afxwin.h>

#include "CoreUiBridge.h"
#include "TimelineView.h"

class CMainFrame : public CFrameWnd {
 public:
  CMainFrame();

 protected:
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg LRESULT OnCoreUpdate(WPARAM wParam, LPARAM lParam);
  afx_msg void OnDestroy();
  DECLARE_MESSAGE_MAP()

 private:
  CoreUiBridge bridge_;
  CTimelineView timeline_view_;
};
