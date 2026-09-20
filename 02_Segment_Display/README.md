# 02. Segment Display

## 🎯 학습 목표
*   7-세그먼트의 공통 애노드 / 공통 캐소드 구조를 이해하고 세그먼트 패턴 테이블을 설계한다.
*   다중 자릿수를 시분할 구동(multiplexing)하여 잔상 효과로 동시에 표시한다.
*   시프트 레지스터 74LS595로 출력 핀을 확장한다.

## 🛠 주요 부품
*   7-세그먼트 모듈, 전류 제한 저항, 74LS595 시프트 레지스터

## 💻 핵심 기법
*   세그먼트 패턴은 `const uint8_t seg[10] PROGMEM`으로 플래시에 두고 `pgm_read_byte()`로 읽는다.
*   자릿수 전환 주기는 자릿수 × 전환 주파수 ≥ 50 Hz가 되도록 잡아야 깜박임이 보이지 않는다.
*   74LS595는 SER / SRCLK / RCLK 세 신호로 구동한다. 비트뱅잉 또는 SPI를 쓴다.

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `40_One7Segments`, `7Segments`, `14_7Segments`, `15_7Segments`, `013_7Segments` | 한 자리 표시 기본형 |
| `45_Four7Segments`, `015_Four7Segments`, `46_Four7Segments_short` | 네 자리 시분할 구동 |
| `47_Four7Segments_Input` | 입력값을 받아 표시 |
| `48_Four7Segments_itoa` | 정수를 자릿수로 분해하여 표시 |
| `42_Six7Segments` | 여섯 자리 확장 |
| `74LS595`, `74LS595_Test`, `500_74LS595` | 시프트 레지스터 기본 (`500_74LS595`는 `09_Simple_Sensors`와 중복이어서 이쪽만 남겼다) |
| `500_74LS596_two` | 시프트 레지스터 직렬 연결(캐스케이드) |

## 📌 참고
*   시분할 구동은 타이머 인터럽트로 옮기는 편이 안정적이다. `06_Timers_Counters`와 함께 보면 좋다.
