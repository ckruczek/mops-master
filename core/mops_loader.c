#include "mops_loader.h"
#include "thread.h"

void mops_load_ramdisk()
{
	extern uint32_t __k_heap_start;
	int length = sizeof(ramdisk) / sizeof(ramdisk[0]);

	uint32_t* start= &__k_heap_start;
	uint32_t* dst = &__k_heap_start;
	int i = 0;
	int j = 0;
	int imageLength = sizeof(imageDescriptor) / sizeof(imageDescriptor[0]);

	for(; i < imageLength; i++)
	{
		int bufferLength =  imageDescriptor[i];
		bufferLength += j;
		// copy the essential assembler codes
		for(; j <  bufferLength; j++)
		{
			*dst++ = ramdisk[j];
		}
		int stackSize = ramdisk[j];
		j++;
		int k = 0;
		// copy the essential stack size, just zeros
		for(; k < stackSize; k++)
		{
			*dst++ = 0x0;
		}
		mops_create_thread_layout(start,dst);
		start = (dst + 0x04);
		dst = start;

	}

	threadTable[0].canBeScheduled = 0;
}

