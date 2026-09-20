# 06. Timers & Counters

## 🎯 학습 목표
*   Timer0(8비트), Timer1(16비트), Timer2(8비트)의 구조 차이를 이해한다.
*   Normal, CTC 모드로 정확한 주기를 만들고 `_delay_ms()`의 한계를 넘어선다.
*   프리스케일러와 비교값으로부터 실제 주기를 계산한다.

## 💻 주요 레지스터
| 레지스터 | 역할 |
|---|---|
| `TCCR0A/B`, `TCCR1A/B` | 동작 모드(`WGM`), 프리스케일러(`CS`), 출력 비교 동작(`COM`) |
| `TCNT0`, `TCNT1` | 현재 계수값 |
| `OCR0A/B`, `OCR1A/B` | 비교 일치값 |
| `TIMSK0`, `TIMSK1` | 오버플로(`TOIE`) 및 비교 일치(`OCIE`) 인터럽트 허용 |

## 🧮 주기 계산
```
CTC 주기 = (OCRnA + 1) × 프리스케일 ÷ F_CPU
예) 16 MHz, 프리스케일 64, OCR0A = 249 → (250 × 64) / 16e6 = 1 ms
```

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `040_Timer0Overflow`, `71_Timer1Overflow` | 오버플로 기반 주기 생성 |
| `042_Timer0CTC`, `042_Timer0_CTC` | CTC 모드 |
| `70_Timer0_10mSec`, `75_Timer0_Sec0_5` | 10 ms / 0.5 s 정밀 주기 |
| `73_Timer1OCR`, `76_Timer1_Compare` | 16비트 비교 일치 |
| `78_Timer_with_LCD` | 타이머 기반 시계를 LCD에 표시 |
| `Timer0` | 기본 설정 실습 |

## 📌 참고
*   `_delay_ms()`는 CPU를 점유하는 바쁜 대기이다. 실제 시스템에서는 타이머 인터럽트로 만든 1 ms 틱을 쓴다.
*   Timer0을 아두이노 코어와 함께 쓰면 `millis()`가 어긋난다. 이 폴더는 코어를 쓰지 않으므로 그 제약이 없다.
