#include "mops_loader.h"
#include "mops_create_thread.h"

void mops_load_ramdisk()
{
	extern uint32_t __k_heap_start;
	int length = sizeof(ramdisk) / sizeof(ramdisk[0]);

	uint32_t* start= &__k_heap_start;
	uint32_t* dst = &__k_heap_start;
	int i = 0;
	for(; i < length; i++)
		*dst++ = ramdisk[i];

	Thread t;
	t.data.start = start;
	t.data.end = dst;
	t.data.sp = dst - 12;
	mops_create_thread(&t);
}

void mops_create_thread(uint32_t *threadAddr)
{
	MOPS_create_thread(threadAddr);
}
