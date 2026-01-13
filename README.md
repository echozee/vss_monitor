# VSS Activity Monitor (MFC)

Windows VSS 활동을 수집·시각화하여 스냅샷 작업과 Requester 추정을 빠르게 파악하는 도구입니다. 설계/요구사항은 docs/ 하위 PRD와 Architecture, UI-Wireframe에 정리되어 있습니다.

## 구조
- `docs/` 요구사항 및 아키텍처 문서
- `src/core/` ETW 수집/상관분석 코어 라이브러리(C++)
- `src/ui_mfc/` MFC 기반 UI
- `src/tests/` GoogleTest 준비용 테스트 프로젝트
- `third_party/`, `tools/` 외부 의존성과 스크립트

## 빌드(계획)
Visual Studio 2026, x64, MSVC v143+, 최신 Windows SDK. 솔루션: `src/VssActivityMonitor.sln`.
