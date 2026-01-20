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

### 1.5 LibraryState
- dayPhase: enum { Open, Normal, Rush, WrapUp }
- chaos: float (0~100)
- reputation: int
- activeEvent: enum { None, SuddenRush, ShelfCollapse, PatronRiot, QueueOverflow }
- eventCooldownSeconds: float

### 1.6 DifficultyConfig
- dayIndex: int
- difficultyTier: int
- tierStepDays: int (기본 3)
- intervalScalePerTier: float (기본 0.95)
- misbehaviorBonusPerTier: float (기본 0.05)
- suddenRushBonusPerTier: float (기본 0.05)
- intervalScaleMin: float (기본 0.75)
- suddenRushChanceMax: float (기본 0.60)
- difficultyTierMax: int (기본 7)
- challengeMode: bool (기본 false)

### 1.7 StaffData
- id: string
- role: enum { Organizer, Reception, Repair }
- hireCost: int
- dailyUpkeep: int
- efficiency: float (작업 속도 보정)
- isUnlocked: bool

### 1.8 FacilityData
- id: string
- type: enum { BookTruck, SearchDesk, ReturnBox, RepairDesk, FloorExpansion }
- level: int
- unlockCost: int
- unlockRequirement: string (평판/일수 조건)
- effectDesc: string

### 1.9 BuildingState
- floorCount: int
- unlockedFacilities: List<FacilityId>
- hiredStaff: List<StaffId>

### 1.10 AchievementData
- id: string
- title: string
- description: string
- isHidden: bool
- conditionTag: string
- rewardType: enum { None, Cosmetic, Coins }
- rewardValue: int

### 1.11 HiddenElementData
- id: string
- type: enum { RarePatron, SecretBook, HiddenShelf, LoreNote }
- discoverHint: string
- spawnChance: float
- conditions: string
- isDiscovered: bool

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

## 6) 혼잡도/긴장도 시스템

### 6.1 혼잡도(Chaos)
- 반납 큐 초과, 잘못된 배치, 서가 붕괴, 소란 손님으로 상승
- 업무 완료, 정리/수리 완료 시 감소
- 기본 범위: 0~100

### 6.2 임계치 효과
- 40 이상: 업무 생성 간격 -10%
- 70 이상: 소형 사건 발생 확률 증가
- 85 이상: 연쇄 사건 가능(하루 최대 1회)

### 6.3 안전장치
- activeEvent는 동시에 1개만 유지
- 대형 사건 후 20~30초 쿨다운
- 5분 세션 기준, 대형 사건 간 최소 60초 간격

### 6.4 UI 표현(수치 비공개)
- 혼잡도는 등급으로 변환해 표시(숫자 비공개)
- 등급 예시:
  - 0~24: Calm
  - 25~49: Busy
  - 50~74: Crowded
  - 75~100: Overload

---

## 7) 하루 타이머/페이싱 (5분)

### 7.1 하루 길이
- dayLengthSeconds: 300

### 7.2 페이즈
- Open: 30s (완화, 업무 0~1개)
- Normal: 150s (기본 업무 페이스)
- Rush: 90s (업무 증가 + 사건 1회)
- WrapUp: 30s (신규 업무 중단, 정리/정산)
- Normal 구간에서도 돌발 러시(20~30s) 발생 가능

### 7.3 업무 생성 속도
- Normal: 45~60초 간격
- Rush: 25~35초 간격
- SuddenRush: 15~25초 간격
- WrapUp: 신규 생성 중단
- 1일 업무 수 목표: 5~7개
- 실제 간격 = 기준 간격 * difficultyIntervalScale

### 7.4 사건 예산
- 대형 사건: 1회/일 (Rush 구간에 배치)
- 돌발 러시(SuddenRush): 0~1회/일
  - 발생 확률: 35%/일 + (tier-1) * 5% (최대 60%)
  - 조건: chaos >= 50
- 돌발 러시 변주: "허위 평온" 연출
  - 대사: "오늘 유난히 사람이 없네요.."
  - 85%: 10~20초 후 러시로 전환
  - 15%: 실제 한산(60~90초 고객 유입 감소)
- 소형 사건: 혼잡도 높을 때 1~2회
- 연쇄 사건: chaos >= 85, 15% 확률, 하루 최대 1회
- 사건은 동시에 중첩되지 않음

---

## 8) 난이도 스케일링

### 8.1 난이도 단계
- difficultyTierBase = floor((dayIndex - 1) / tierStepDays) + 1
- 기본 모드: difficultyTier = min(difficultyTierBase, difficultyTierMax)
- 도전 모드: difficultyTier = difficultyTierBase (상한 없음)

### 8.2 스케일링 규칙(매운맛 A)
- difficultyIntervalScale = max(intervalScaleMin, intervalScalePerTier^(tier-1))
- 소란/실수 확률 증가 = (tier-1) * misbehaviorBonusPerTier
- 돌발 러시 확률 증가 = (tier-1) * suddenRushBonusPerTier
- 상한 적용으로 급격한 난이도 상승 방지

### 8.3 회복 여지 유지
- 업무/정리 완료 시 chaos 감소 폭 고정(난이도에 영향 없음)
- 하루 정산 시 chaos 40~60% 리셋

---

## 9) 업무/퀘스트 시스템

### 9.1 생성 규칙
- 페이즈에 따라 25~60초 간격으로 랜덤 생성
- 난이도에 따라 보상 증가

### 9.2 실패 조건
- 제한 시간 초과
- 반납 큐 초과(지속 발생 시 게임 오버)

---

## 10) 업그레이드/해금 시스템

### 10.1 해금 흐름
- 하루 정산 화면에서 코인/평판으로 해금
- 해금 선택은 하루에 1개 제한(초기 기준)

### 10.2 직원 해금
- Organizer: 주변 책 자동 정리(속도 느림)
- Reception: 손님 문의 처리(업무 1개 자동 완료)
- Repair: 손상 책 수리 보조(수리 시간 감소)

### 10.3 시설 해금
- BookTruck: 한 번에 3~5권 운반, 이동 속도 약간 감소
- SearchDesk: 책 위치 안내/선반 강조 기능 강화
- FloorExpansion: 층 수 증가, 수용량 증가, 업무량도 증가

### 10.4 해금 트리(예시)
| 단계 | 해금 요소 | 비용(코인) | 조건 | 효과 |
| --- | --- | --- | --- | --- |
| 1 | BookTruck | 120 | Day 2 또는 평판 8 | 운반 +3권, 이동 -5% |
| 2 | SearchDesk | 180 | Day 3 또는 평판 12 | 검색 힌트 강화 |
| 3 | Organizer | 250 | Day 4 또는 평판 18 | 자동 정리 보조 |
| 4 | ReturnBox Lv1 | 220 | Day 5 또는 평판 22 | 반납 큐 +2 |
| 5 | RepairDesk | 260 | Day 6 또는 평판 26 | 수리 시간 -20% |
| 6 | FloorExpansion | 350 | Day 7 또는 평판 32 | 2층 개방 |
| 7 | Reception | 320 | Day 9 또는 평판 40 | 문의 1건 자동 처리 |

### 10.5 밸런싱 메모
- 비용/조건은 초기 가이드이며 플레이 테스트로 조정
- 해금은 하루 1개 제한을 유지

---

## 11) 업적/숨김 요소

### 11.1 업적
- 조건 태그 기반으로 트리거
- 달성 시 작은 토스트 + 코스메틱 또는 코인 보상
- 히든 업적은 실루엣만 표시

### 11.2 숨김 요소
- 희귀 손님/비밀 장서/숨겨진 서가/일기장 수집
- 발생 확률은 비공개, 힌트만 제공
- 발견 시 컬렉션에 기록, 다음 발견 확률 소폭 감소

---

## 12) 도서관 PC

### 12.1 검색
- 제목/카테고리 검색
- 결과 클릭 시 안내 표시(해당 선반 강조)

### 12.2 라벨 재발급
- 상태가 DamagedLabel일 때만 가능
- 재발급 시 코인 소모

---

## 13) 저장/로드

### 13.1 저장 항목
- 돈, 평판, 시설 레벨
- 각 책의 상태 및 위치(선반/임시 스택)
- 당일 진행 상태
- 업적 해금 상태, 숨김 요소 발견 상태

### 13.2 저장 방식
- 모바일: PlayerPrefs + JSON 파일
- PC: 로컬 JSON 파일

---

## 14) 수용 기준(예시)
- 책 집기/놓기가 60fps 환경에서 부드럽게 동작
- 서가 붕괴가 1초 내 시각적 피드백 제공
- PC/모바일 모두 동일한 업무 루프 체험 가능
