# Agent Rules

- 모든 작업은 docs/codex/*.task에 정의된 단계별로 진행한다. 각 .task는 하나의 독립된 개발 스텝이며 병합하지 않는다.
- 의존성 순서: PRD > Architecture > 개별 TASK. 변경 시 상위 문서를 우선한다.
- 코드/문서 변경 시 최소 단위로 커밋하고, .task에 명시된 커밋 메시지를 사용한다.
- Core와 UI는 분리: Core는 UI 헤더에 의존하지 않고, UI는 Core 공개 API만 사용한다.
- 스레딩: 수집/상관분석은 백그라운드, UI 업데이트는 PostMessage 등으로 처리한다.
