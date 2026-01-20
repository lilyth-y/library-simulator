# System Specifications

이 문서는 Unity 구현을 기준으로 게임 요소의 상세 명세를 정의한다.

---

## 1) 데이터 모델

### 1.1 BookData
- id: string (고유 식별자)
- title: string
- categoryId: int
- status: enum { Normal, DamagedLabel, DamagedBarcode }
- weight: float (스택 안정성 계산)
- designatedShelfId: int
- isRelocated: bool

### 1.2 ShelfData
- id: int
- categoryId: int
- capacity: int
- stabilityBase: float (기본 안정성)
- slots: List<BookId>

### 1.3 PatronData
- id: string
- type: enum { Normal, Noisy, Messy }
- state: enum { Idle, MoveToShelf, Interact, Alerted, Leave }
- rudeness: float (0~100)
- patience: float (seconds)

### 1.4 TaskData
- id: string
- description: string
- timeLimit: float
- rewardCoins: int
- rewardReputation: int

---

## 2) 상호작용 시스템

### 2.1 입력 규칙
- PC: 클릭/드래그
- 모바일: 탭(선택), 드래그(이동), 길게 탭(정보)

### 2.2 집기/놓기
- Raycast로 대상 감지
- 대상이 Book이면 PickUp 상태로 전환
- 물리 핸들(또는 Kinematic + Spring)을 사용해 손 위치에 추적
- 놓기 시:
  - 선반 슬롯 우선 배치
  - 비정렬 배치 시 안정성 점수 감소

### 2.3 책 상태 확인/수리
- Inspect: UI 팝업으로 상태 표시
- Repair: 수리대 상호작용 시 status -> Normal
- 수리 시간: 2~4초(튜닝 가능)

---

## 3) 물리/스택 안정성

### 3.1 안정성 계산
- 스택 책들의 중심(CoM)을 계산
- CoM이 바닥 책의 중심에서 Threshold 거리 이내면 안정

### 3.2 파라미터
- stabilityThreshold: float (기본 0.15m)
- heightThreshold: int (기본 8권)
- weightFactor: float (기본 1.0)

### 3.3 붕괴 트리거
- heightThreshold 초과 또는
- CoM 이탈 시
- 붕괴 시 일정 반경에 힘을 가해 책을 흩트림

---

## 4) 서가/정리 규칙

### 4.1 정렬 규칙
- categoryId가 일치하면 "정렬됨"
- 불일치 시:
  - 손님 만족도 소폭 감소
  - 검색 PC에서 경고 표시

### 4.2 슬롯 규칙
- 선반마다 슬롯 수 고정
- 슬롯 초과 시:
  - 임시 스택 생성
  - 안정성 페널티 적용

---

## 5) 손님 AI

### 5.1 기본 루프
1. 입장
2. 목표(읽기/반납/문의) 선택
3. 이동 후 상호작용
4. 상태 전이(만족/소란/퇴장)

### 5.2 소란 패턴
- 일정 확률로 책 위치를 뒤섞음
- 소란 상태가 길어지면 평판 감소
- 플레이어가 "조용히" 상호작용 시 진정

---

## 6) 업무/퀘스트 시스템

### 6.1 생성 규칙
- 60~90초 간격으로 랜덤 생성
- 난이도에 따라 보상 증가

### 6.2 실패 조건
- 제한 시간 초과
- 반납 큐 초과(지속 발생 시 게임 오버)

---

## 7) 도서관 PC

### 7.1 검색
- 제목/카테고리 검색
- 결과 클릭 시 안내 표시(해당 선반 강조)

### 7.2 라벨 재발급
- 상태가 DamagedLabel일 때만 가능
- 재발급 시 코인 소모

---

## 8) 저장/로드

### 8.1 저장 항목
- 돈, 평판, 시설 레벨
- 각 책의 상태 및 위치(선반/임시 스택)
- 당일 진행 상태

### 8.2 저장 방식
- 모바일: PlayerPrefs + JSON 파일
- PC: 로컬 JSON 파일

---

## 9) 수용 기준(예시)
- 책 집기/놓기가 60fps 환경에서 부드럽게 동작
- 서가 붕괴가 1초 내 시각적 피드백 제공
- PC/모바일 모두 동일한 업무 루프 체험 가능
