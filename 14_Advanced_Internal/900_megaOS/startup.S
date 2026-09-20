#include <avr/io.h>

    .section .vectors

    .global __vectors
__vectors:
    jmp     _start


    .text
    .global _start
_start:
    clr     r1
    out     AVR_STATUS_ADDR, r1
    ldi     r28,lo8(__stack)
    ldi     r29,hi8(__stack)
    out     AVR_STACK_POINTER_HI_ADDR, r29
    out     AVR_STACK_POINTER_LO_ADDR, r28

    .set    __stack, RAMEND

_do_copy_data:
    ldi     r17, hi8(__data_end)
    ldi     r26, lo8(__data_start)
    ldi     r27, hi8(__data_start)
    ldi     r30, lo8(__data_load_start)
    ldi     r31, hi8(__data_load_start)
    rjmp    2f
1:  lpm     r0, Z+
    st      X+, r0
2:  cpi     r26, lo8(__data_end)
    cpc     r27, r17
    brne    1b

_do_clear_bss:
    ldi     r17, hi8(__bss_end)
    ldi     r26, lo8(__bss_start)
    ldi     r27, hi8(__bss_start)
    rjmp    4f
3:  st      X+, r1
4:  cpi     r26, lo8(__bss_end)
    cpc     r27, r17
    brne    3b

    call    main

