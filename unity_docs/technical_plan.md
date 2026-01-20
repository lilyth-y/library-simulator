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
