#include "thread.h"

int mops_create_thread_layout(uint32_t* startAddr, uint32_t* endAddr, Thread* t)
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
			emptyThreadTableIndex = i;
	}

	if(threadsFullCount == MAX_THREADS)
		return -1;
	
	t->data.start = startAddr;
	t->data.end = endAddr;
	t->id = ++maxId;
	t->state = NEW;
	threadTable[emptyThreadTableIndex] = *t;
	return t->id;

}
