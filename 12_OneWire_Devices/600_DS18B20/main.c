/*
 * 600_DS18B20 - 1-Wire DS18B20 온도 측정 (ATmega328P, bare-metal)
 *
 * 배선
 *   DS18B20 VDD  -> 5V
 *   DS18B20 GND  -> GND
 *   DS18B20 DQ   -> PD2, 그리고 DQ와 5V 사이에 4.7k 풀업 저항
 *   UART TX(PD1) -> USB-Serial RX,  9600 bps 8N1
 *
 * 동작
 *   1초마다 온도를 측정하여 UART로 출력한다.
 */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define BAUD  9600UL

#include "onewire.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

/* ---- DS18B20 명령 ---- */
#define DS_SKIP_ROM       0xCC
#define DS_CONVERT_T      0x44
#define DS_READ_SCRATCH   0xBE
#define DS_WRITE_SCRATCH  0x4E

/* ---------------- UART ---------------- */
static void uart_init(void)
{
    uint16_t ubrr = (uint16_t)(F_CPU / (16UL * BAUD) - 1);
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8N1 */
}

static int uart_putchar(char c, FILE *stream)
{
    if (c == '\n') uart_putchar('\r', stream);
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
    return 0;
}

static FILE uart_out = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

/* ---------------- DS18B20 ---------------- */
/* 분해능 설정 : 9~12비트. 변환 시간은 각각 94 / 188 / 375 / 750 ms */
static void ds_set_resolution(uint8_t bits)
{
    uint8_t cfg;
    if (bits < 9)  bits = 9;
    if (bits > 12) bits = 12;
    cfg = 0x1F | ((uint8_t)(bits - 9) << 5);

    if (!ow_reset()) return;
    ow_write_byte(DS_SKIP_ROM);
    ow_write_byte(DS_WRITE_SCRATCH);
    ow_write_byte(0x7F);   /* TH */
    ow_write_byte(0x80);   /* TL */
    ow_write_byte(cfg);    /* Configuration */
}

/*
 * 온도를 0.0625도 단위의 raw 값으로 읽는다.
 * 반환 : 0 = 정상, 1 = 디바이스 없음, 2 = CRC 오류
 */
static uint8_t ds_read_raw(int16_t *raw)
{
    uint8_t sp[9];

    if (!ow_reset()) return 1;
    ow_write_byte(DS_SKIP_ROM);
    ow_write_byte(DS_CONVERT_T);

    /* 12비트 분해능 기준 최대 750ms. 여유를 두고 대기한다.
       (기생 전원이 아니므로 변환 중 버스를 읽어 완료를 감지할 수도 있다) */
    for (uint8_t i = 0; i < 80; i++) _delay_ms(10);

    if (!ow_reset()) return 1;
    ow_write_byte(DS_SKIP_ROM);
    ow_write_byte(DS_READ_SCRATCH);
    for (uint8_t i = 0; i < 9; i++) sp[i] = ow_read_byte();

    if (ow_crc8(sp, 8) != sp[8]) return 2;

    *raw = (int16_t)((uint16_t)sp[1] << 8 | sp[0]);
    return 0;
}

/* ---------------- main ---------------- */
int main(void)
{
    int16_t raw;
    uint8_t err;

    uart_init();
    stdout = &uart_out;

    printf("\nDS18B20 1-Wire temperature monitor\n");

    if (!ow_reset()) {
        printf("no device on the bus. check wiring and 4.7k pull-up.\n");
    }
    ds_set_resolution(12);

    for (;;) {
        err = ds_read_raw(&raw);

        if (err == 1) {
            printf("error: no presence pulse\n");
        } else if (err == 2) {
            printf("error: CRC mismatch\n");
        } else {
            /* raw x 0.0625 = 섭씨. 부동소수점 없이 정수 연산으로 출력한다.
               raw * 625 은 0.0001도 단위이다. */
            int32_t milli = (int32_t)raw * 625 / 10;   /* 0.001도 단위 */
            int16_t  ip   = (int16_t)(milli / 1000);
            uint16_t fp   = (uint16_t)((milli < 0 ? -milli : milli) % 1000);
            printf("T = %d.%03u C  (raw = %d)\n", ip, fp, raw);
        }

        for (uint8_t i = 0; i < 100; i++) _delay_ms(10);   /* 1초 주기 */
    }
}
