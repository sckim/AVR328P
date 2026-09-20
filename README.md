# 02. AVR C/ASM Development (Bare-metal)

이 폴더는 ATmega328P 마이크로컨트롤러를 **Bare-metal(AVR C 및 Assembly)** 수준에서 제어하기 위한 학습 예제 모음이다. 아두이노 프레임워크의 추상화 뒤에 감추어진 레지스터 제어와 하드웨어의 동작 원리를 직접 다룬다.

같은 상위 폴더의 `01_Arduino_Projects`는 동일한 15단계 주제를 아두이노 프레임워크(`digitalWrite`, `analogRead` 등)로 구현한 대응 저장소이다. 두 폴더의 폴더 번호 체계는 의도적으로 일치시켜 두었으므로, 같은 번호끼리 비교하며 추상화 계층의 차이를 학습할 수 있다.

## 🛠 개발 환경 (Development Environments)

두 가지 개발 환경을 모두 지원한다. 각 환경의 설정 파일(`*.cproj`, `platformio.ini`)이 독립적으로 관리되므로 필요에 따라 선택하여 사용한다.

### 1. Visual Studio Code + PlatformIO (권장)
*   **특징**: 현대적인 에디터 환경, 빠른 코드 작성, 간편한 라이브러리 관리.
*   **사용법**: VS Code에서 해당 프로젝트 폴더를 열면 `platformio.ini`를 인식하여 자동으로 환경을 구성한다.
*   **팁**: 소스 코드가 루트에 있는 경우 `platformio.ini`에 `src_dir = .` 설정이 포함되어 있다.

### 2. Microchip Studio (구 Atmel Studio)
*   **특징**: 공식 IDE, 강력한 하드웨어 디버깅(Atmel-ICE 등), 레지스터 실시간 모니터링.
*   **사용법**: 루트의 `uC_Examples.atsln` 솔루션 파일을 열면 모든 프로젝트가 로드된다.
*   **팁**: 하드웨어의 세부 동작을 한 단계씩 실행(step-by-step)하며 확인할 때 유용하다.

---

## 📚 학습 커리큘럼 (실제 폴더 구성 기준)

### 00. Introduction — `00_Introduction`
*   개발 환경 구축 및 첫 동작 확인 (`How_to_run_uC`, `1How_to_run_uC`, `2How_to_run_uC`)
*   새 프로젝트의 출발점 (`001_Template`, `05_main`, `Demo1`)
*   비트 조작(bit twiddling) 기초 (`30_BitTwidding`)
*   메모리 섹션(.data/.bss) 확인 (`Check_databss`)

### 01. Digital I/O — `01_Digital_IO`
*   `DDRx`/`PORTx`/`PINx` 레지스터에 의한 LED 출력과 버튼 입력 (`010_Blink`, `020_Input_LED`, `GPIORead`)
*   Assembly에 의한 초저수준 제어 (`002_asmBlink`, `005_asmBlink`, `assembler_Exam1`)
*   아두이노 스타일 구현과의 비교 (`012_Blink_Arduino`)
*   입력 응용 (`23_Input_UpDown`, `24_Input_Toggle`)

### 02. Segment Display — `02_Segment_Display`
*   7-세그먼트 구동 원리 (`40_One7Segments`, `45_Four7Segments`, `42_Six7Segments`)
*   입력·숫자 변환 응용 (`47_Four7Segments_Input`, `48_Four7Segments_itoa`)
*   시프트 레지스터 74LS595를 이용한 핀 확장 (`500_74LS595`, `500_74LS596_two`, `74LS595_Test`)

### 03. Serial Comm (UART) — `03_Serial_Comm`
*   UART 레지스터 직접 설정과 송수신 기초 (`060_UART`, `90_UART_start`, `91_UART_print`)
*   표준 입출력(`printf`) 연결 (`062_UART_printf`, `065_LIbUART_printf`)
*   재사용 가능한 UART 라이브러리 (`064_LibUART`, `UART_Lib`), RS232 레벨 변환 (`RS232`)

### 04. ADC — `04_ADC`
*   ADC 레지스터 설정과 변환 (`050_ADC`, `100_ADC_hold`, `108_ADC_serial`)
*   LCD 연동 측정값 표시 (`102_ADC_on_LCD`, `105_ADC_KeyIn_on_LCD`)
*   ※ 이 폴더에 섞여 있던 PWM 예제 4개는 `07_PWM`으로 옮겼다.

### 05. Interrupts — `05_Interrupts`
*   외부 인터럽트와 핀 변화 인터럽트 (`027_Interrupt`, `028_PCInterrupt`, `29_Interrupts`)
*   타이머 인터럽트 기반 구현 (`041_Timer0Overflow_Int`, `043_Timer0CTC_Int`)
*   ISR의 모듈화 (`044_Timer0Overflow_Int_module`)

### 06. Timers & Counters — `06_Timers_Counters`
*   Overflow 및 CTC 모드 (`040_Timer0Overflow`, `042_Timer0CTC`, `71_Timer1Overflow`)
*   정확한 주기 생성 (`70_Timer0_10mSec`, `75_Timer0_Sec0_5`)
*   비교 일치 출력 (`73_Timer1OCR`, `76_Timer1_Compare`), LCD 연동 (`78_Timer_with_LCD`)

### 07. PWM — `07_PWM`
*   Fast PWM / Phase-correct PWM / CTC 기반 PWM (`082_PWM_Timer0FPWM`, `082_PWM_Timer1FPWM`, `082_PWM_Timer0CTC`, `088_FastPWM`)
*   소프트웨어 PWM (`080_PWM_bitbang`), 2채널 출력 (`081_PWM_Dual`)
*   ADC 및 UART 연동 듀티 제어 (`082_PWM_ADC`, `083_PWM_SetRC_UART`)
*   `04_ADC`에서 옮겨 온 예제 (`080_PWM_bitbang_v2`, `081_PWM_Timer0Interrupt2`, `81_PWM`, `82_PWM`)

### 08. Motors — `08_Motors`
*   스테핑 모터 (`810_Motor_Stepper`), RC 서보 (`811_Motor_RC`), DC 모터 (`812_Motor_DCM`)

### 09. Simple Sensors — `09_Simple_Sensors`
*   키패드 스캔 (`026_Keypad`, `26_Keypad(4x4)`)
*   초음파 거리 측정 (`510_Ultrasound`, `510_Ultrasound_v2`), 로터리 엔코더 (`511_RotaryEncoder`)
*   74LS595 기반 입출력 확장 (`017_74LS596_two`), TTL 레벨 실습 (`950_ttl_uC`)

### 10. I2C (TWI) Devices — `10_I2C_Devices`
*   텍스트 LCD 직접 구동 및 라이브러리화 (`030_myTextLCD`, `032_LibTextLCD`, `68_textLCDLib`, `64_textLCD_4bits`)
*   TWI 레지스터 기반 주변장치 제어 (`220_TWI_LM75` 온도, `221_TWI_RTC` 실시간 시계, `224_TWI_PCF8574`, `225_TWI_PCF8575`)
*   I2C LCD (`225_TWI_LCD`, `LCD_I2C`, `226_TWO_LCD_OOP`), 관성 센서 (`ADXL_ITG_20150521`)

### 11. SPI Devices — `11_SPI_Devices`
*   SPI 기초 (`110_SPI`), 시프트 레지스터 직렬 출력 (`105_SerialShift_595`)
*   MAX7219 도트 매트릭스 (`110_SPI_MAX7219`, `115_SPI_Software_MAX7219`)
*   디지털 가변저항 MCP41xx 제어 (`110_SPI_MCP41xx`)

### 12. One-Wire Devices — `12_OneWire_Devices`
*   1-Wire 프로토콜을 레지스터 수준에서 직접 구현한 DS18B20 온도 측정 (`600_DS18B20`)
*   Reset/Presence, 비트 슬롯 타이밍, CRC-8 검사를 모두 포함한다

### 13. EEPROM Storage — `13_EEPROM_Storage`
*   내장 EEPROM 읽기/쓰기 (`201_eeprom`, `eeprom`)
*   설정값을 EEPROM에 보존하는 메뉴 시스템 (`200_Menu_start`, `210_Menu_eeprom`)

### 14. Advanced Internal — `14_Advanced_Internal`
*   워치독 타이머 (`Watchdog`, `900_Wachdog`), 부트로더 (`Bootloader`)
*   그래픽 LCD 구동 (`056_GLCD_Img`, `057_GLCD_Text`)

### 15. Integrated Projects — `15_Integrated_Projects`
*   전 주제를 통합한 종합 예제 (`777_Allfunction`, `777_AllFunctions_OOP`, `777_AllFunctions_OOP_v2`)
*   객체 지향 구조 실험 (`GPIO_oop`), 모듈·센서 계층 분리 (`Modules`, `Sensors`)
*   보드 통합 펌웨어 (`MainPro328F_v6`)

### 99. Archive — `99_Archive`
*   구버전 솔루션·워크스페이스·시뮬레이션 파일 보관 (`Atmega328P.atsln`, `AVR328P.code-workspace`, `AVR328P_Basic.pdsprj`)

---

## 📄 기타 문서

| 파일 | 내용 |
|---|---|
| `README_Microchip.md` | 「마이크로시스템설계」 16주차 강의 진행표 원본 |
| `README_Arduino_Style.md` | 제목 한 줄만 있는 빈 문서 |
| `LICENSE` | 라이선스 |

---

## ✅ 2026-09-19 정리 내역

*   루트 및 하위 폴더 README 18개를 실제 폴더 구성과 bare-metal 관점에 맞게 재작성하였다. 이전에는 `01_Arduino_Projects`의 README 복사본이어서 `pinMode`, `digitalWrite` 등 아두이노 함수를 설명하고 있었다.
*   `04_ADC`에 섞여 있던 PWM 예제 4개를 `07_PWM`으로 옮겼다.
*   `14_Advanced_Internal` 루트에 떠 있던 `Watchdog.cproj`와 `main.c`를 `Watchdog/` 폴더로 묶었다.
*   `uC_Examples.atsln`의 프로젝트 경로 30개가 모두 폴더 재구성 이전 이름(`03_ADC_PWM`, `08_SPI_Devices`, `13_Advanced_Internal` 등)을 가리켜 솔루션이 열리지 않는 상태였다. 현행 폴더명으로 일괄 갱신하여 30개 전부 경로가 맞는다.
*   프로젝트 165개를 **파일명을 무시하고 소스 내용 해시로** 전수 비교하여, 내용이 완전히 같은 5건을 하나만 남기고 `_to_delete/`로 옮겼다. 내역과 복구 방법은 `_to_delete/MANIFEST.md`에 있다.
*   비어 있던 `12_OneWire_Devices`에 `600_DS18B20`을 새로 작성하였다. avr-gcc 기준 경고 없이 빌드되며, 16 MHz / 8 MHz 모두에서 확인하였다 (flash 2,562 B, RAM 182 B).

## 🧹 남은 정리 과제

### 판단이 필요한 건
*   `11_SPI_Devices/110_SPI_MAX7219_v2`의 소스가 `110_SPI_MAX7219`에 모두 포함되고, 원본에만 파일이 하나 더 있다. 완전 중복이 아니라 포함 관계이다. `uC_Examples.atsln`에 등록된 쪽은 `_v2`이다.
*   `99_Archive/99_Archive`는 폴더 재구성 이전의 전체 덤프로 소스 1,315개를 담고 있다. 현행 예제 대부분이 여기에 중복 보관되어 있으나 보관이 목적이므로 그대로 두었다.
*   `09_Simple_Sensors/950_ttl_uC`에는 소스 파일이 없어 내용 판정이 불가능하다.

### 중복이 아님이 확인된 쌍
다음 세 쌍은 2021년 원본과 2025년 PlatformIO 재구성판의 관계이며 내용이 서로 다르다. 그대로 둔다.

| 쌍 | 차이 |
|---|---|
| `042_Timer0CTC` / `042_Timer0_CTC` | 전자는 `COM0A0` 하드웨어 토글 출력 + PORTB 한 자리, 후자는 출력 비교 핀 비활성 + PORTD BCD 두 자리 |
| `043_Timer0CTC_Int` / `043_Timer0_CTC_int` | 표시 자릿수와 `OCR0A` 설정 시점(`sei()` 전후)이 다르다 |
| `028_PCInterrupt` / `028_PC_Interrupt` | 전혀 다른 예제이며, 후자에는 외부 인터럽트 예제 `Interrupt.c`가 추가로 있다 |

### 그 밖에
*   예제 폴더의 번호 접두사가 세 자리 82개, 두 자리 43개, 한 자리 1개, 접두사 없음 40개로 혼재한다. 세 자리로 통일하려면 `uC_Examples.atsln`의 경로도 함께 고쳐야 한다.
*   `900_Wachdog`은 철자 오류이다. `Watchdog`과의 관계를 정리할 필요가 있다.
*   `README_Arduino_Style.md`는 제목 한 줄뿐인 빈 문서이다.
*   `uC_Examples.atsln.bak`은 경로 일괄 갱신 전에 만든 백업이다. 확인이 끝나면 정리한다.

---
※ 각 폴더 내의 `README.md`에서 상세한 학습 목표와 하드웨어 연결 방법을 확인할 수 있다.
