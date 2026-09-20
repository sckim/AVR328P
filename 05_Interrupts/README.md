# 05. Interrupts

## 🎯 학습 목표
*   인터럽트 벡터 테이블과 `ISR()` 매크로의 동작을 이해한다.
*   외부 인터럽트(INT0/INT1)와 핀 변화 인터럽트(PCINT)의 차이를 구분한다.
*   ISR을 짧게 유지하고 `volatile` 변수로 메인 루프와 통신하는 방법을 익힌다.

## 💻 주요 레지스터
| 레지스터 | 역할 |
|---|---|
| `EICRA` | INT0/INT1의 트리거 조건 — Low / 변화 / 하강 / 상승 에지 |
| `EIMSK` | `INT0`, `INT1` 개별 허용 |
| `PCICR`, `PCMSK0:2` | 핀 변화 인터럽트 그룹 및 핀별 허용 |
| `SREG` 의 `I` 비트 | 전역 인터럽트 허용 — `sei()` / `cli()` |

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `027_Interrupt`, `27_Interrupt`, `28_Interrupt` | 외부 인터럽트 기본형 |
| `028_PCInterrupt`, `028_PC_Interrupt`, `29_Interrupts` | 핀 변화 인터럽트 |
| `041_Timer0Overflow_Int` | 타이머 오버플로 인터럽트 |
| `043_Timer0CTC_Int`, `043_Timer0_CTC_int` | CTC 비교 일치 인터럽트 |
| `044_Timer0Overflow_Int_module` | ISR과 응용 로직의 모듈 분리 |

## 📌 참고
*   ISR 안에서는 `_delay_ms()`나 `printf`를 쓰지 않는다.
*   ISR과 메인 루프가 공유하는 변수는 반드시 `volatile`로 선언한다. 2바이트 이상이면 읽는 동안 `cli()`로 보호해야 한다.
*   INT0/INT1은 지정한 두 핀(PD2, PD3)에만 있고, PCINT는 거의 모든 핀에 있으나 어느 핀이 바뀌었는지는 직접 판별해야 한다.
