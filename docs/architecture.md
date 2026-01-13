# Architecture

## Solution Layout
- Solution: `VssActivityMonitor.sln`
- Projects: `VssMon.Core` (Static Lib/DLL ready), `VssMon.UiMfc` (MFC EXE), `VssMon.Tests` (Console/GoogleTest).

## Recommended Build Environment
- Visual Studio 최신(2026 시점) / MSVC toolset v143 이상
- Windows SDK: 최신(10/11 SDK)
- C++ 표준: Core는 C++17 호환, C++20 권장
- UI: MFC (유니코드)

## Folder Structure (예시)
```
repo/
  docs/
    PRD.md
    Architecture.md
    UI-Wireframe.md
  src/
    core/
      include/vssmon/
        model/
          event.h
          transaction.h
          process.h
        etw/
          etw_session.h
          etw_consumer.h
          providers.h
        correlate/
          correlator.h
          scoring.h
        util/
          win_handle.h
          scope_guard.h
          time.h
      src/
        etw/
        correlate/
        model/
        util/
      VssMon.Core.vcxproj
    ui_mfc/
      res/
      ui/
        MainFrm.h/.cpp
        VssTimelineView.h/.cpp
        TransactionListView.h/.cpp
        ProcessDetailView.h/.cpp
        RawEventView.h/.cpp
      VssMon.UiMfc.vcxproj
    tests/
      VssMon.Tests.vcxproj
  third_party/
  tools/
    dev_scripts/
```

## 핵심 클래스 책임
- `EtwSession`: ETW 세션 생성/시작/중지(RAII)
- `EtwConsumer`: 이벤트 콜백 수신 → 내부 큐 전달
- `EventNormalizer`: Provider별 raw 이벤트 → 공통 `VssEvent`로 정규화
- `Correlator`: 시간창/ActivityId/Client-Server 호출관계 기반으로 `VssTransaction` 생성/갱신, Requester 후보 스코어링
- `CoreFacade`: UI가 쓰기 쉬운 단일 인터페이스(Start/Stop/Subscribe)

## MFC UI 구성 (Mock 기준)
- 메인 프레임: 2행 Splitter
  - 상단: 필터/컨트롤(시간범위, 볼륨, 결과, 프로세스 필터, Live/Pause)
  - 하단: TabCtrl
    - Timeline(스윔레인)
    - Transactions List
    - Process Drilldown
    - Raw Events(개발자 모드)
