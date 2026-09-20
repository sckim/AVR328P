# _to_delete — 중복 프로젝트 격리 목록

2026-09-19. `02_AVR_C_Development` 전체(프로젝트 165개)를 **파일명을 무시하고 소스 내용 해시의 다중집합**으로 비교하여, 내용이 완전히 같은 프로젝트를 하나만 남기고 이곳으로 옮겼다. 삭제한 것이 아니므로 `mv`로 되돌릴 수 있다.

## 이동 내역

| 이동한 폴더 | 유지한 쪽 | 판정 근거 | 유지 쪽을 고른 이유 |
|---|---|---|---|
| `15_Integrated_Projects/MainPro328F` | `15_Integrated_Projects/MainPro328F_v6` | 소스 12개 전부 바이트 일치 | `_v6`에만 `MainPro328.atsln`, `.srec`, 의존성 파일이 더 있다 |
| `15_Integrated_Projects/sensor-interface1` | `15_Integrated_Projects/Sensors` | 소스 12개 전부 바이트 일치 | 파일 구성이 완전히 동일하여 이름이 명확한 쪽을 남겼다 |
| `07_PWM/081_PWM_Timer0Interrupt` | `05_Interrupts/044_Timer0Overflow_Int_module` | 유일 소스가 내용 일치 (`PWM.c` ↔ `main.c`, 파일명만 다름) | 코드 내용이 Timer0 오버플로 인터럽트 모듈이므로 05단원이 본적이다 |
| `09_Simple_Sensors/016_74LS595` | `02_Segment_Display/500_74LS595` | 유일 소스가 바이트 일치 | 74LS595는 세그먼트 단원의 핀 확장 주제이다 |
| `01_Digital_IO/012_Blink_oop` | `15_Integrated_Projects/GPIO_oop` | 소스 4개 전부 바이트 일치 | 객체 지향 예제는 15단원에 모여 있고, 01단원에는 Blink 변형이 이미 10개 있다 |

아래 세 건은 **단원을 가로지르는 중복**이었다. 한 예제를 두 단원에 함께 걸어 두었던 것일 수 있으므로, 해당 단원에 그 예제가 꼭 필요하다면 되돌린다.

* `07_PWM/081_PWM_Timer0Interrupt`
* `09_Simple_Sensors/016_74LS595`
* `01_Digital_IO/012_Blink_oop`

## 되돌리는 법

```bash
cd 02_AVR_C_Development
mv _to_delete/01_Digital_IO/012_Blink_oop            01_Digital_IO/
mv _to_delete/07_PWM/081_PWM_Timer0Interrupt         07_PWM/
mv _to_delete/09_Simple_Sensors/016_74LS595          09_Simple_Sensors/
mv _to_delete/15_Integrated_Projects/MainPro328F     15_Integrated_Projects/
mv _to_delete/15_Integrated_Projects/sensor-interface1 15_Integrated_Projects/
```

## 이동하지 않은 것

* **`99_Archive/99_Archive`** — 폴더 재구성 이전의 전체 덤프이다. 소스 1,315개를 담고 있어 현행 예제 대부분이 여기에 포함되어 있으나, 보관이 목적인 폴더이므로 건드리지 않았다.
* **`11_SPI_Devices/110_SPI_MAX7219_v2` ⊂ `110_SPI_MAX7219`** — `_v2`의 소스가 원본에 모두 포함되고 원본에만 파일이 하나 더 있다. 완전 중복이 아니므로 판단을 남겨 둔다. 참고로 `uC_Examples.atsln`에 등록된 쪽은 `_v2`이다.
* **`042_Timer0CTC`/`042_Timer0_CTC`, `043_Timer0CTC_Int`/`043_Timer0_CTC_int`, `028_PCInterrupt`/`028_PC_Interrupt`** — 중복이 아니다. 각각 2021년 원본과 2025년 PlatformIO 재구성판으로, 표시 방식과 출력 핀 설정이 서로 다르다. 특히 `028_PC_Interrupt`에는 다른 쪽에 없는 외부 인터럽트 예제 `Interrupt.c`가 들어 있다.
* **`09_Simple_Sensors/950_ttl_uC`** — 소스 파일이 없어 내용 판정이 불가능하다.
