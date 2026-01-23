# Unity Technical Plan

## 1) 엔진 버전
- Unity LTS 최신 버전 사용 권장
  - 예: 2022.3 LTS 이상

## 2) 주요 패키지
- URP (모바일 최적화)
- Input System
- TextMeshPro
- Cinemachine (카메라)
- Addressables (에셋 로딩)

## 3) 프로젝트 구조(예시)
- Assets/
  - Art/
    - Models/
    - Materials/
    - Textures/
  - Audio/
  - Prefabs/
  - Scenes/
  - Scripts/
    - Core/
    - Systems/
    - UI/
    - AI/
  - Data/
    - ScriptableObjects/
  - UI/

## 4) 성능 목표
- 모바일 기준 30~60fps
- 드로우콜 최소화(정적 배칭)
- 물리 오브젝트 최대 동시 200개 내외

## 5) 물리 설정
- Fixed Timestep: 0.02
- 충돌 레이어 분리(Book, Shelf, Player, NPC)
- 책은 Rigidbody + BoxCollider 기본

## 6) 빌드/배포
- PC: Windows 우선
- 모바일: Android 우선, iOS는 후순위
- Addressables로 리소스 로딩 최적화

## 7) 저장/데이터
- ScriptableObject로 데이터 정의
- JSON 저장(플랫폼 공통)

## 8) Ralph 방식 운영 지침(자율 실행 루프)

### 8.1 검증 루프(필수)
- Unity Cloud Build를 기본 검증 루프로 사용
- 빌드/테스트 로그를 자동 저장하여 재시도 근거로 활용
- 빌드 실패 시 로그를 기준으로 2~3회 재시도 후 중단

### 8.2 작업 단위/계약
- 목표/수용조건/제한 범위를 명시하고 작업 시작
- 예: "SuddenRush 이벤트 구현 + 테스트 통과"

### 8.3 자율 실행 범위
- 코드/데이터/UI까지 전부 포함
- 단, 씬 구조 변경은 변경 로그를 남김
- UI 수정은 모바일/PC 양쪽 스크린샷 검증 기준 포함

### 8.4 안전장치
- 재시도 횟수 제한: 3회
- 작업 시간 제한: 20~30분
- 변경 파일 범위 제한(해당 작업 범위 내)
- 테스트 실패 시 자동 중단
