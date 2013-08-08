#include "thread.h"
#include "scheduler.h"
int mops_create_thread_layout(uint32_t* startAddr, uint32_t* endAddr)
{
	int i = 0;
	int maxId = 0;
	int threadsFullCount = 0;
	int emptyThreadTableIndex = 0;
	for(;i < MAX_THREADS; i++)
	{
			// get the max id to increment for next thread
		if(maxId <= threadTable[i].id)
			maxId = threadTable[i].id;

		if(threadTable[i].state != UNDEFINED)
			threadsFullCount++;
		else
		{
			emptyThreadTableIndex = i;
			break;
		}
	}

	if(threadsFullCount == MAX_THREADS)
		return -1;
	 threadTable[emptyThreadTableIndex].data.start = startAddr;
	 threadTable[emptyThreadTableIndex].id = ++maxId;
	 threadTable[emptyThreadTableIndex].state = NEW;
	 threadTable[emptyThreadTableIndex].canBeScheduled = 1;
	 threadTable[emptyThreadTableIndex].all_register[15] = startAddr;
	 threadTable[emptyThreadTableIndex].all_register[13] = endAddr - 12;
	return threadTable[emptyThreadTableIndex].id;

}
