# UI 와이어프레임

## 레이아웃
- 메인 프레임: 2행 Splitter
  - 상단: 필터/컨트롤(시간범위, 볼륨, 결과, 프로세스 문자열 필터, Live/Pause)
  - 하단: TabCtrl로 탭 구성

## 탭 구성
- Timeline: 스윔레인(프로세스/vssvc/volsnap/writers)
- Transactions List: 트랜잭션 테이블(시간/작업/볼륨/Requester/결과/Confidence)
- Process Drilldown: 프로세스별 히스토리 + Confidence breakdown
- Raw Events: 개발자 모드 뷰

## 타임라인 표시 규칙
- 시간 흐름: 좌→우, 구간 표시
- Point event: 채워진 원, Span event: 채워진 사각형
- Lane 헤더: 프로세스 이름 + PID(가능 시)
- 선택 시 하이라이트, Hover 시 tooltip 표시

## 상호작용
- 마우스 휠: 확대/축소
- 마우스 드래그: 수평 팬
- 클릭: 이벤트 선택 후 메인 프레임에 알림

## 스레딩 지침
- Core는 워커 스레드에서 이벤트 발행
- UI 업데이트는 PostMessage로 처리(크로스 스레드 직접 호출 금지)

## 리소스 관리
- 모든 GDI 객체는 RAII로 관리
- UI 스레드 블로킹 금지; 폭주 시에도 안정적 동작 목표
