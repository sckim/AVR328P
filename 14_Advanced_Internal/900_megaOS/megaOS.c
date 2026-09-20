#include <os.h> 

int main(void)
{
	arch_init();
	board_init();
	
	printf("\nmegaOS. [%s %s]\n",__DATE__,__TIME__);
	
	os_start();
	
	while (1);
}