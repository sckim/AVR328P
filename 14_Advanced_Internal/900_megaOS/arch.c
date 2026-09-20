#include <os.h> 

static void uart_tx(char ch, FILE *stream);

static volatile struct uart *const uart = (void*)UART_REG;
static FILE mystdio = FDEV_SETUP_STREAM(uart_tx, NULL, _FDEV_SETUP_RW); 

static void uart_tx(char ch, FILE *stream)
{
    if (ch == '\n')
        uart_tx('\r', stream);

    while (!(uart->ucsr_a & UDRE));
    uart->udr = ch;
}

static void uart_init(void)
{
    uart->ucsr_b = 0x00;
    uart->ucsr_a = 0x00;
    uart->ucsr_c = DATA_8BIT << CHAR_SZ_SHIFT; // 8,N,1
    uart->ubrr   = (SYS_CLOCK/BAUDRATE/16 - 1) + UART_COMPENSATION;
    uart->ucsr_b = (RXEN | TXEN);

    stdout = stdin = &mystdio;
}

void arch_init(void)
{
    cli();
    uart_init();
}
