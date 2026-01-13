#include "TimelineView.h"

BEGIN_MESSAGE_MAP(CTimelineView, CWnd)
  ON_WM_PAINT()
END_MESSAGE_MAP()

void CTimelineView::SetModel(UiModel* model) { model_ = model; }

void CTimelineView::OnPaint() {
  CPaintDC dc(this);
  CRect client;
  GetClientRect(&client);

  dc.FillSolidRect(&client, RGB(250, 250, 250));

  CPen axis_pen(PS_SOLID, 1, RGB(180, 180, 180));
  auto* old_pen = dc.SelectObject(&axis_pen);
  int axis_y = client.top + 24;
  dc.MoveTo(client.left + 40, axis_y);
  dc.LineTo(client.right - 10, axis_y);
  dc.SelectObject(old_pen);

  if (!model_) {
    return;
  }

  auto snapshot = model_->Snapshot();
  CPen tx_pen(PS_SOLID, 1, RGB(0, 120, 215));
  CBrush tx_brush(RGB(0, 120, 215));
  old_pen = dc.SelectObject(&tx_pen);
  auto* old_brush = dc.SelectObject(&tx_brush);

  const int lane_height = 28;
  const int lane_top = client.top + 40;
  const int lane_spacing = 16;

  for (size_t i = 0; i < snapshot.size(); ++i) {
    int lane = static_cast<int>(i % 4);
    int y = lane_top + lane * (lane_height + lane_spacing);
    int x1 = client.left + 60 + static_cast<int>((i % 8) * 60);
    CRect rect(x1, y, x1 + 44, y + 12);
    dc.Rectangle(&rect);

    const auto& tx = snapshot[i];
    CString label(tx.op_type.c_str());
    dc.TextOutW(rect.left, rect.bottom + 2, label);
  }

  dc.SelectObject(old_pen);
  dc.SelectObject(old_brush);
}
