# PRD: VSS Activity Monitor (MFC)

## 목적
Windows에서 발생하는 VSS 관련 활동을 수집/시각화하여 "무슨 VSS 작업이 언제 발생했는지"와 "Requester(요청 프로세스)가 누구인지(추정)"를 분석가가 빠르게 파악하도록 한다.

## 목표 사용자
EDR/보안 개발자, 침해분석가, IT 운영자

## 핵심 가치
VSS는 vssvc.exe 중심으로 동작해 Requester 식별이 어렵다 → ETW/프로세스/COM-RPC 상관을 결합해 Confidence 기반 추정을 제공.

## 범위
- 포함: ETW 기반 실시간 수집, 이벤트 정규화, 트랜잭션 단위 묶기, Requester 후보 추정 + 근거 표시, MFC UI(타임라인/리스트/드릴다운/Raw)
- 제외: 커널 드라이버 개발, 원격(네트워크) 수집, Requester 100% 확정 기능

## 기능 요구사항
- FR-1: 실시간 모니터링 시작/중지
- FR-2: VSS 작업 유형 표시 (Snapshot Create/Delete, Enumerate Writers, Error/Timeout 등)
- FR-3: 트랜잭션 뷰 (시작/종료, 볼륨, 결과, 이벤트 카운트)
- FR-4: Requester 추정 (후보 프로세스 Top N + Confidence 0~1, Evidence 목록)
- FR-5: 필터 (시간범위/볼륨/결과/프로세스 문자열/known tools only)
- FR-6: Raw 이벤트 뷰(개발자 모드)

## 비기능 요구사항
- NFR-1: 장시간 실행 시 메모리/핸들 누수 없음
- NFR-2: UI 스레드 블로킹 금지(수집/상관분석은 백그라운드)
- NFR-3: 이벤트 폭주 시에도 안정적(큐/드롭/백프레셔 정책)
- NFR-4: Windows 2026 환경에서 빌드/실행

## 데이터 모델(요약)
- `VssEvent`: timestamp, provider, event_id, op_type, volume_id, activity_id(가능 시), pid(가능 시), raw_fields…
- `VssTransaction`: tx_id, start/end, op_type, volumes[], result, requester_candidates[{pid, score, evidence[]}], events[]

## UI 요구사항
- 타임라인: 스윔레인(프로세스/vssvc/volsnap/writers) + 구간 표시
- 리스트: 트랜잭션 테이블(시간/작업/볼륨/Requester/결과/Conf)
- 드릴다운: 프로세스별 히스토리 + Confidence breakdown

## 리스크/제약
- Requester PID는 원천적으로 누락될 수 있음 → Confidence/Evidence 기반으로 표기(“추정” 명시)
- ETW Provider/필드가 OS 버전에 따라 달라질 수 있음 → 모듈화/방어적 파싱

## 마일스톤
- M1: Core ETW 수집+정규화(로그 파일로 dump)
- M2: Correlator로 트랜잭션 묶기 + Requester 스코어링
- M3: MFC UI(Transactions List + Raw) 연결
- M4: Timeline/Drilldown 추가 + 안정화(누수/성능)
