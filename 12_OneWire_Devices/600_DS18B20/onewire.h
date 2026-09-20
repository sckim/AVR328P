/*
 * onewire.h - ATmega328P bare-metal 1-Wire master
 *
 * 데이터선은 오픈 드레인으로 다룬다.
 *   - Low 구동 : DDR 비트를 1로 (PORT 비트는 항상 0)
 *   - 해제     : DDR 비트를 0으로 → 외부 4.7k 풀업이 High로 끌어올린다
 */
#ifndef ONEWIRE_H_
#define ONEWIRE_H_

/* 빌드 시스템이 -DF_CPU 를 주면 그 값을 쓰고, 없으면 16MHz 로 가정한다 */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdint.h>

/* 데이터선 정의 : 기본 PD2 */
#define OW_DDR    DDRD
#define OW_PORT   PORTD
#define OW_PIN    PIND
#define OW_BIT    PD2

uint8_t ow_reset(void);                 /* 1 = 디바이스 응답 있음 */
void    ow_write_bit(uint8_t bit);
uint8_t ow_read_bit(void);
void    ow_write_byte(uint8_t data);
uint8_t ow_read_byte(void);
uint8_t ow_crc8(const uint8_t *data, uint8_t len);

#endif /* ONEWIRE_H_ */
