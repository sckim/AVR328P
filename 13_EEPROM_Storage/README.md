# 13. EEPROM Storage

## 🎯 학습 목표
*   내장 1 KB EEPROM에 설정값을 저장하고 전원 재투입 후 복원한다.
*   `<avr/eeprom.h>`의 `eeprom_read/write` 계열 함수와 `EEMEM` 속성을 사용한다.
*   UART 메뉴를 통해 설정값을 변경하고 저장하는 구조를 만든다.

## 💻 주요 API
```c
#include <avr/eeprom.h>
uint16_t cal EEMEM;                 // EEPROM 영역에 변수 배치
uint16_t v = eeprom_read_word(&cal);
eeprom_update_word(&cal, v + 1);    // 값이 같으면 쓰지 않는다
```

## 📂 예제
| 폴더 | 내용 |
|---|---|
| `201_eeprom`, `eeprom` | EEPROM 읽기/쓰기 기본형 |
| `200_Menu_start` | UART 기반 설정 메뉴 골격 |
| `210_Menu_eeprom` | 메뉴에서 바꾼 값을 EEPROM에 보존 |

## 📌 참고
*   EEPROM 수명은 셀당 약 100,000회이다. 반드시 `eeprom_write_*` 대신 `eeprom_update_*`를 써서 불필요한 쓰기를 피한다.
*   1바이트 쓰기에 약 3.3 ms가 걸린다. 루프 안에서 무심코 쓰지 않도록 주의한다.
*   전원 강하 중 쓰기가 진행되면 데이터가 손상될 수 있다. BOD(Brown-out Detection) 퓨즈를 켜 두는 것이 안전하다.
