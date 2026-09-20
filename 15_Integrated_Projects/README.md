# 15. Integrated Projects

## 🎯 학습 목표
*   앞선 단계에서 익힌 주변장치를 하나의 펌웨어로 통합한다.
*   드라이버 계층과 응용 계층을 분리하여 유지보수 가능한 구조를 설계한다.
*   C++ 클래스로 주변장치를 추상화했을 때의 이점과 비용(코드 크기, RAM)을 확인한다.

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `777_Allfunction` | 전 주변장치를 묶은 종합 예제 (C) |
| `777_AllFunctions_OOP`, `777_AllFunctions_OOP_v2` | 같은 기능의 C++ 객체 지향 구현 |
| `GPIO_oop` | GPIO를 클래스로 추상화 (`01_Digital_IO/012_Blink_oop`과 동일하여 이쪽만 남겼다) |
| `Modules` | 기능별 드라이버 모듈 모음 |
| `Sensors` | 센서 인터페이스 계층 (ADXL345 + ITG-3200) |
| `MainPro328F_v6` | 보드 통합 펌웨어 본체 |
| `200_Menu_start` | UART 메뉴 기반 사용자 인터페이스 |
| `ArduinoSketch1` | 아두이노 코어를 라이브러리로 링크한 혼합 구성 |

## 📌 참고
*   ATmega328P의 RAM은 2 KB뿐이다. C++ 가상 함수와 동적 할당은 신중하게 쓴다.
*   `-Os` 최적화와 `avr-size`로 코드·데이터 크기를 항상 확인하는 습관을 들인다.
*   `MainPro328F`, `sensor-interface1`은 각각 `MainPro328F_v6`, `Sensors`와 바이트 단위로 같아 `_to_delete`로 옮겼다.
