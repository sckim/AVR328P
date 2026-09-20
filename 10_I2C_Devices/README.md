# 10. I2C (TWI) Devices

## 🎯 학습 목표
*   ATmega328P의 TWI 모듈을 레지스터 수준에서 구동하여 I2C 마스터를 구현한다.
*   START / 주소+R/W / 데이터 / ACK·NACK / STOP의 순서와 상태 코드를 이해한다.
*   텍스트 LCD를 4비트 병렬과 I2C 확장칩(PCF8574) 두 방식으로 모두 구동한다.

## 🛠 주요 부품
*   16×2 텍스트 LCD(HD44780), PCF8574/PCF8575 I/O 확장칩, LM75 온도센서, DS1307/DS3231 RTC, ADXL345 · ITG3200

## 💻 주요 레지스터
| 레지스터 | 역할 |
|---|---|
| `TWBR`, `TWSR`의 `TWPS` | SCL 주파수 결정. `SCL = F_CPU / (16 + 2·TWBR·4^TWPS)` |
| `TWCR` | `TWINT` 완료 플래그, `TWSTA` START, `TWSTO` STOP, `TWEA` ACK, `TWEN` 허용 |
| `TWSR` 상위 5비트 | 상태 코드 — 0x08 START, 0x18 SLA+W ACK, 0x28 데이터 ACK 등 |
| `TWDR` | 주소 또는 데이터 |

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `030_myTextLCD`, `62~67_textLCD*`, `64_textLCD_4bits` | HD44780 4비트 병렬 구동 |
| `032_LibTextLCD`, `68_textLCDLib`, `69_textLCD3_read` | LCD 라이브러리화 및 읽기 동작 |
| `035_textLCDADC` | ADC 측정값을 LCD에 표시 |
| `220_TWI_LM75` | I2C 온도센서 |
| `221_TWI_RTC` | 실시간 시계 |
| `224_TWI_PCF8574`, `225_TWI_PCF8575` | I/O 확장칩 |
| `225_TWI_LCD`, `TWI_LCD`, `LCD_I2C`, `LCD_I2C_v2` | I2C 백팩 LCD |
| `226_TWO_LCD_OOP`, `LCD1`, `LCDTest`, `TestLCD` | C++ 객체 지향 래퍼 |
| `ADXL_ITG_20150521` | 가속도계 + 자이로 복합 측정 |

## 📌 참고
*   SDA/SCL에는 4.7 kΩ 풀업 저항이 필요하다. 모듈에 내장된 경우가 많으니 중복 연결에 주의한다.
*   슬레이브 주소는 7비트이다. `TWDR`에 넣을 때는 1비트 왼쪽으로 민 뒤 R/W 비트를 더한다.
*   응답 없는 슬레이브를 기다리다 멈추지 않도록 `TWINT` 대기 루프에 타임아웃을 둔다.
