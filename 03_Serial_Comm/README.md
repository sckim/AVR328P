# 03. Serial Comm (UART)

## 🎯 학습 목표
*   USART 레지스터를 직접 설정하여 보율, 데이터 비트, 정지 비트를 구성한다.
*   폴링 방식과 인터럽트 방식 송수신의 차이를 이해한다.
*   `printf` 계열 함수를 UART에 연결하여 디버깅 출력을 확보한다.

## 💻 주요 레지스터
| 레지스터 | 역할 |
|---|---|
| `UBRR0H` / `UBRR0L` | 보율 분주값. `UBRR = F_CPU / (16 × BAUD) − 1` |
| `UCSR0A` | 상태 — `UDRE0`(송신 버퍼 빔), `RXC0`(수신 완료) |
| `UCSR0B` | `TXEN0` / `RXEN0` 송수신 허용, `RXCIE0` 수신 인터럽트 허용 |
| `UCSR0C` | 프레임 형식 — 데이터 비트 수, 패리티, 정지 비트 |
| `UDR0` | 데이터 레지스터. 읽으면 수신, 쓰면 송신 |

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `060_UART`, `90_UART_start`, `91_USART`, `92_UART` | 레지스터 설정과 1바이트 송수신 |
| `91_UART_print` | 문자열 송신 |
| `062_UART_printf`, `065_LIbUART_printf` | `fdevopen` / `FILE` 구조체로 `printf` 연결 |
| `064_LibUART`, `UART_Lib` | 재사용 가능한 UART 라이브러리 모듈 |
| `SerialComm`, `SerialTest` | 통신 시험 |
| `SetRC_UART` | UART 명령으로 RC 서보 각도 설정 |
| `RS232` | TTL ↔ RS-232 레벨 변환 |

## 📌 참고
*   16 MHz에서 9600 bps의 오차는 0.2 %로 안전하지만, 115200 bps는 2.1 %에 달한다. 고속에서는 `U2X0` 비트를 켜거나 14.7456 MHz 크리스털을 쓴다.
*   `printf`는 코드 크기를 크게 키운다. 부동소수점 출력이 필요하면 링커에 `-Wl,-u,vfprintf -lprintf_flt`를 추가해야 한다.
