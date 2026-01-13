# Repository Guidelines

## 프로젝트 구조 및 모듈 구성
- 현재 코드는 최소 스켈레톤이며 설계/요구사항은 `docs/`에 정리됨.
- 솔루션: `src/VssActivityMonitor.sln`; 빌드 산출물은 `src/Build/$(Configuration)$(Platform)/`.
- 코어: `src/core/`(헤더 `include/vssmon/`, 소스 `src/`), MFC UI: `src/ui_mfc/ui/`, 테스트: `src/tests/`.
- 기타: `third_party/` 외부 의존성, `tools/` 개발 스크립트, `docs/codex/` 태스크 정의.

## 빌드 · 테스트 · 개발 명령
- 도구체인: Visual Studio 2026, x64, MSVC v143+, 최신 Windows 10/11 SDK, MFC(동적 링크).
- IDE 빌드: VS에서 솔루션 열기 → x64/Debug or Release → Build Solution.
- CLI 빌드(개발자 명령 프롬프트):
```
& "C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe" src\VssActivityMonitor.sln /p:Configuration=Release /p:Platform=x64
```
- 산출물 위치: `src/Build/Releasex64/` 또는 `src/Build/Debugx64/`.

## 코딩 스타일 · 네이밍
- 언어: C++20 권장(Core는 C++17 호환). 탭/스페이스 혼용 금지, 모듈 내 일관성 유지.
- 네이밍: 타입/클래스 PascalCase, 헤더/소스 snake_case(`etw_session.h`, `correlator.cpp`).
- RAII로 핸들/리소스 관리, UI는 유니코드 API 사용.

## 테스트 가이드
- 프레임워크: GoogleTest 예정(`src/tests/`).
- 파일/케이스 명명: 대상 유닛 기준(`correlator_tests.cpp` 등).
- 실행: VS 테스트 프로젝트 실행 또는 `ctest --output-on-failure`(추가되면)로 동작 확인.

## 커밋 · PR 가이드
- 커밋 메시지는 범위+행동 위주(`core: add ETW normalizer` 등). 태스크 파일에 지정된 메시지 우선.
- PR: 변경 요약, 관련 이슈/태스크 링크, UI 변경 시 스크린샷, 수행한 테스트 명시.

## 구성/안전 메모
- 대상 OS: Windows 10/11. Toolset v143+, MFC/ATL 구성요소 설치.
- ETW Provider/필드 가변성을 고려해 방어적 파싱과 널 체크 유지.
