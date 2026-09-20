#include <os.h>

static struct list  sched_list[OS_NR_PRIORITIES];
static uint8_t      sched_map;

static void sched_init(void)
{
	int     i;
	
	for (i=0; i<OS_NR_PRIORITIES; i++)
	{
		list_init(&sched_list[i]);
	}
	
	sched_map = 0;
}

static void os_init(void)
{
	sched_init();
}

void os_start(void)
{
	os_init();
}