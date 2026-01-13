#include "MainFrm.h"

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
  ON_WM_CREATE()
  ON_WM_SIZE()
  ON_WM_DESTROY()
  ON_MESSAGE(kUiUpdateMessage, OnCoreUpdate)
END_MESSAGE_MAP()

CMainFrame::CMainFrame() {
  CString class_name = AfxRegisterWndClass(
      CS_HREDRAW | CS_VREDRAW, ::LoadCursor(nullptr, IDC_ARROW),
      reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);
  Create(class_name, _T("VSS Activity Monitor"));
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1) {
    return -1;
  }

  CString view_class = AfxRegisterWndClass(CS_DBLCLKS, ::LoadCursor(nullptr, IDC_ARROW),
                                           reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);
  CRect rect(0, 0, 400, 300);
  if (!timeline_view_.Create(view_class, _T("TimelineView"),
                             WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                             rect, this, 1001)) {
    return -1;
  }

  timeline_view_.SetModel(&bridge_.model());
  bridge_.SetNotifyHwnd(m_hWnd);
  bridge_.Start();

  return 0;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) {
  CFrameWnd::OnSize(nType, cx, cy);
  if (timeline_view_.GetSafeHwnd()) {
    timeline_view_.MoveWindow(0, 0, cx, cy);
  }
}

LRESULT CMainFrame::OnCoreUpdate(WPARAM /*wParam*/, LPARAM /*lParam*/) {
  if (timeline_view_.GetSafeHwnd()) {
    timeline_view_.Invalidate();
  }
  return 0;
}

void CMainFrame::OnDestroy() {
  bridge_.Stop();
  CFrameWnd::OnDestroy();
}
