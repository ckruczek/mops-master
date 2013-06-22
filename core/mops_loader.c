#include "mops_loader.h"
#include "mops_change_proc.h"
void mops_load_ramdisk()
{
	extern uint8_t __heap_start;
	int length = sizeof(ramdisk) / sizeof(ramdisk[0]);
	char* dst = &__heap_start;
	Thread t;
	int i = 0;
	for(; i < length; i++)
		*dst++ = ramdisk[i];


	
	if(mops_create_thread_layout(&__heap_start, dst, &t) != -1)
	{
		MOPS_change_proc(&t);
	}

}
