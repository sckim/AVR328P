#include "onewire.h"          /* F_CPU 정의가 delay.h 보다 먼저 와야 한다 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* 핀을 Low로 끌어내린다 */
static inline void ow_low(void)     { OW_DDR |=  (1 << OW_BIT); }
/* 핀을 해제한다 (하이 임피던스, 풀업이 High로 만든다) */
static inline void ow_release(void) { OW_DDR &= ~(1 << OW_BIT); }
static inline uint8_t ow_level(void){ return (OW_PIN & (1 << OW_BIT)) ? 1 : 0; }

uint8_t ow_reset(void)
{
    uint8_t presence;
    uint8_t sreg = SREG;

    OW_PORT &= ~(1 << OW_BIT);   /* 출력값은 항상 0으로 유지 */

    cli();
    ow_low();
    _delay_us(480);              /* Reset 펄스 : 480us 이상 Low */
    ow_release();
    _delay_us(70);               /* 디바이스가 15~60us 후 Presence 펄스를 낸다 */
    presence = !ow_level();      /* Low로 끌려 있으면 응답 있음 */
    SREG = sreg;

    _delay_us(410);              /* 슬롯 나머지를 채운다 (총 480us 이상) */
    return presence;
}

void ow_write_bit(uint8_t bit)
{
    uint8_t sreg = SREG;
    cli();
    ow_low();
    if (bit) {
        _delay_us(6);            /* Write 1 : 짧게 Low */
        ow_release();
        _delay_us(64);
    } else {
        _delay_us(60);           /* Write 0 : 길게 Low */
        ow_release();
        _delay_us(10);
    }
    SREG = sreg;
}

uint8_t ow_read_bit(void)
{
    uint8_t bit;
    uint8_t sreg = SREG;
    cli();
    ow_low();
    _delay_us(6);                /* 슬롯 시작 */
    ow_release();
    _delay_us(9);                /* 마스터는 15us 이내에 샘플링해야 한다 */
    bit = ow_level();
    SREG = sreg;

    _delay_us(55);               /* 슬롯 나머지 (총 60us 이상) */
    return bit;
}

void ow_write_byte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++) {   /* LSB 우선 */
        ow_write_bit(data & 0x01);
        data >>= 1;
    }
}

uint8_t ow_read_byte(void)
{
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        data >>= 1;
        if (ow_read_bit()) data |= 0x80;
    }
    return data;
}

/* Dallas/Maxim CRC-8, 다항식 X^8 + X^5 + X^4 + 1 */
uint8_t ow_crc8(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0;
    while (len--) {
        uint8_t inbyte = *data++;
        for (uint8_t i = 0; i < 8; i++) {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}
