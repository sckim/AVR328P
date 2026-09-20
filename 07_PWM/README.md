# 07. PWM

## 🎯 학습 목표
*   Fast PWM, Phase-correct PWM, CTC 토글 방식의 파형 차이와 용도를 구분한다.
*   `OCRnx` 값으로 듀티비를, `TOP` 값과 프리스케일러로 주파수를 결정하는 원리를 이해한다.
*   하드웨어 PWM과 소프트웨어 PWM(비트뱅잉)의 장단점을 비교한다.

## 🛠 주요 부품
*   LED, DC 모터, RC 서보, 부저

## 💻 주요 레지스터
| 레지스터 | 역할 |
|---|---|
| `TCCR0A/B`, `TCCR1A/B` | `WGM` 파형 모드, `COM` 출력 극성, `CS` 프리스케일러 |
| `OCR0A/B`, `OCR1A/B` | 듀티비 결정 |
| `ICR1` | Timer1에서 `TOP`을 지정해 주파수를 자유롭게 설정 |

## 🧮 주파수 계산
```
Fast PWM  : f = F_CPU / (프리스케일 × (TOP + 1))
Phase-correct : f = F_CPU / (2 × 프리스케일 × TOP)
```

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `080_PWM`, `81_PWM`, `82_PWM` | PWM 출력 기본형 |
| `045_PWM_Timer0FPWM`, `082_PWM_Timer0FPWM`, `088_FastPWM` | Timer0 Fast PWM |
| `082_PWM_Timer0PWM`, `082_PWM_Timer1PWM` | Phase-correct PWM |
| `082_PWM_Timer1FPWM` | Timer1 16비트 Fast PWM |
| `082_PWM_Timer0CTC` | CTC 토글 방식 |
| `080_PWM_bitbang`, `080_PWM_bitbang_v2` | 타이머 없이 소프트웨어로 만든 PWM |
| `081_PWM_Timer0Interrupt2` | 인터럽트 기반 PWM |
| `081_PWM_Dual` | 2채널 동시 출력 |
| `082_PWM_ADC` | 가변저항 입력으로 듀티비 제어 |
| `083_PWM_SetRC_UART` | UART 명령으로 RC 서보 펄스폭 설정 |

## 📌 참고
*   RC 서보는 20 ms 주기에 1~2 ms 펄스폭이 필요하다. Timer1 + `ICR1`로 `TOP`을 잡는 방식이 정확하다.
*   DC 모터 구동에는 드라이버 IC(L298N, TB6612 등)가 필요하다. MCU 핀을 직접 연결하지 않는다.
*   `080_PWM_bitbang_v2`, `081_PWM_Timer0Interrupt2`, `81_PWM`, `82_PWM`은 `04_ADC`에 있던 것을 이 폴더로 옮겼다.
*   `081_PWM_Timer0Interrupt`은 `05_Interrupts/044_Timer0Overflow_Int_module`과 내용이 같아 `_to_delete`로 옮겼다.
