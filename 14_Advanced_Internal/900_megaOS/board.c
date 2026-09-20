#include <os.h> 

static volatile struct port *const portb = (void*)PORTB_REG;

void board_init(void)
{
    portb->ddr  = LED;
    portb->port = LED;
}
