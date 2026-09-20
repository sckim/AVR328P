# 00. Introduction

## 🎯 학습 목표
*   AVR 툴체인(avr-gcc, avrdude)과 Microchip Studio / PlatformIO 개발 환경을 구축한다.
*   `main()` 진입 전에 수행되는 초기화 과정과 `.data` / `.bss` 섹션의 의미를 이해한다.
*   레지스터를 다루는 데 필요한 비트 조작(bit twiddling) 관용구를 익힌다.

## 💻 핵심 관용구
```c
PORTB |=  (1 << PB5);   // 비트 세트
PORTB &= ~(1 << PB5);   // 비트 클리어
PORTB ^=  (1 << PB5);   // 비트 토글
if (PINB & (1 << PB0))  // 비트 검사
```

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `001_Template` | 새 프로젝트의 출발점이 되는 최소 골격 |
| `05_main` | `main()` 구조와 무한 루프 기본형 |
| `How_to_run_uC`, `1How_to_run_uC`, `2How_to_run_uC` | 빌드·업로드 절차 단계별 확인 |
| `30_BitTwidding` | 비트 마스크 연산 실습 |
| `Check_databss` | `.data` / `.bss` 섹션에 변수가 배치되는 모습 확인 |
| `Demo1`, `GccApplication1` | IDE가 생성한 기본 프로젝트 |

## 📌 참고
*   `F_CPU`는 실제 클록(기본 16 MHz, 내부 RC 사용 시 8 MHz 또는 1 MHz)과 반드시 일치시켜야 한다. 불일치하면 `_delay_ms()`와 UART 보율이 모두 어긋난다.
