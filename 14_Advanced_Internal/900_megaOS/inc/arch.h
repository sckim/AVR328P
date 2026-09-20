
#define sei()  __asm__ __volatile__ ("sei" ::: "memory")
#define cli()  __asm__ __volatile__ ("cli" ::: "memory")


/*------------------------------------------------------------------------------
 * Register Offset Address
 *----------------------------------------------------------------------------*/
#define PORTB_REG   0x23
#define UART_REG    0xC0



/*------------------------------------------------------------------------------
 * PORT structure
 *----------------------------------------------------------------------------*/
struct port
{
    uint8_t     pin;
    uint8_t     ddr;
    uint8_t     port;
};

/*------------------------------------------------------------------------------
 * UART structure
 *----------------------------------------------------------------------------*/
#define RXC     0x80
#define TXC     0x40
#define UDRE    0x20

enum 
{
    DATA_5BIT,
    DATA_6BIT,
    DATA_7BIT,
    DATA_8BIT
};
#define CHAR_SZ_SHIFT   1

#define RXCIE       0x80
#define RXEN        0x10
#define TXEN        0x08

struct uart
{
    uint8_t     ucsr_a;
    uint8_t     ucsr_b;
    uint8_t     ucsr_c;
    uint8_t     reserved;
    uint16_t    ubrr;
    uint8_t     udr;
};

/*------------------------------------------------------------------------------
 * Function proto-types
 *----------------------------------------------------------------------------*/
void arch_init(void);
