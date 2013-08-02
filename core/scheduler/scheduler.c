#include "scheduler.h"


void mops_schedule()
{
	if(currIndex > MAX_THREADS)
		currIndex = 0;
	int i = 0;
	Thread nextRunner;
	for(;i < MAX_THREADS; i++)
	{
		Thread t = threadTable[i];
		if(t.state != UNDEFINED)
		{
			switch(t.state)
			{
				case WAITING:
				case NEW:
					t.state = RUNING;
					break;
				case RUNING:
					t.state = WAITING;
					break;
			}
			threadTable[i] = t;
		}
	}
	currIndex++;
	asm("mov r0,#42");
}

void mops_resume(int threadTableIndex)
{
	MOPS_resume((uint32_t*)&threadTable[threadTableIndex]);
}
