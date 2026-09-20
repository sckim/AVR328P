OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(avr:5)
 
MEMORY
{
  flash   (rx)   : org = 0,        len = 32K
  sram    (rw!x) : org = 0x800100, len = 2K
}
 
SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))
        *(.text)
        . = ALIGN(2);
        *(.text.*)
        . = ALIGN(2);
    } > flash
 
    .data :
    {
        __data_start = .;
        *(.data)
        *(.data*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(2);
        __data_end = .;
    } > sram AT > flash
    __data_load_start = LOADADDR(.data);
 
    .bss :
    {
        __bss_start = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    } > sram
 
    __heap_start = .;
}