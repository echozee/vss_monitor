# UI 와이어프레임 (VSS Activity Monitor)

이 문서는 MFC UI의 구조와 동작을 정의하는 행동 와이어프레임입니다. 명시적 변경이 없으면 이 구조를 따른다.

## 1. 메인 창 레이아웃
- 상단: 메뉴/툴바, 필터/컨트롤(시간범위, 볼륨, 결과, 프로세스, Start/Stop)
- 중단: 탭 영역(Timeline | Transactions | Process | Raw Events)
- 하단: 상태 표시줄

## 2. 타임라인 탭(주요 뷰)
- 목적: 스윔레인으로 "누가 언제 무엇을 했는가" 시각화
- 레인: Requester 후보(이름+PID), vssvc.exe, volsnap, writers
- 글리프: 포인트 이벤트=채워진 원, 구간 이벤트=채워진 사각형
- 인터랙션: 휠 확대/축소, 드래그 팬, 클릭 선택(하이라이트), Hover 툴팁
- 툴팁 예: 시간, 작업, 볼륨, 트랜잭션 ID, 추정 Requester/Confidence, Evidence

## 3. 트랜잭션 탭
- 목적: 트랜잭션 요약 테이블 제공
- 컬럼: 시작 시각, 작업, 볼륨, Requester(추정), Confidence, 결과
- 더블클릭 시 타임라인으로 포커스/하이라이트

## 4. 프로세스 탭
- 목적: 단일 프로세스 관점에서 VSS 활동 조회
- 표시: 프로세스 정보(경로/사용자), 활동 히스토리, Confidence Breakdown

## 5. Raw Events 탭(개발자 모드)
- 목적: 원본 ETW 이벤트 노출
- 기본 비활성, 메뉴에서 Developer Mode로 활성화
- 열: Timestamp, Provider, EventId, PID, Message

## 6. UI 동작 규칙
- Requester 표시는 항상 "추정"임을 명시하고 Confidence/Evidence를 노출
- 타임라인이 기준 뷰이며 리스트 선택과 동기화

## 7. 비목표
- 픽셀 단위 시각 디자인, 애니메이션, 커스텀 테마는 범위 밖
