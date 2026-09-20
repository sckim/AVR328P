# 14. Advanced Internal

## 🎯 학습 목표
*   워치독 타이머로 시스템 행(hang)을 감지하고 자동 복구한다.
*   부트로더의 역할과 BOOTSZ / BOOTRST 퓨즈의 의미를 이해한다.
*   그래픽 LCD에 문자와 비트맵 이미지를 출력한다.

## 💻 주요 레지스터
| 레지스터 | 역할 |
|---|---|
| `WDTCSR` | `WDE` 리셋 허용, `WDIE` 인터럽트 허용, `WDP3:0` 타임아웃 주기 |
| `MCUSR` | 리셋 원인 — `PORF`, `EXTRF`, `BORF`, `WDRF` |
| `SPMCSR` | 플래시 자가 기록(부트로더에서 사용) |

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `900_Wachdog`, `Watchdog` | 워치독 타이머 설정과 `wdt_reset()` |
| `Bootloader` | 자가 기록 방식 부트로더 |
| `056_GLCD_Img` | 그래픽 LCD 비트맵 출력 |
| `057_GLCD_Text` | 그래픽 LCD 문자 출력 |

## 📌 참고
*   워치독은 리셋 후에도 활성 상태가 유지된다. 시작 즉시 `MCUSR`을 읽어 지우고 `wdt_disable()`을 호출한 뒤 재설정해야 무한 리셋 루프에 빠지지 않는다.
*   `900_Wachdog`은 철자 오류(Wachdog)가 있는 구버전이다. `Watchdog` 쪽이 Microchip Studio 솔루션에 등록된 프로젝트이다.
*   부트로더 작업은 퓨즈 비트를 다룬다. 잘못 설정하면 ISP 없이는 복구할 수 없다.
