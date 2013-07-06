#include "scheduler.h"


void mops_schedule()
{
	if(currIndex > MAX_THREADS)
		currIndex = 0;
	int i = 0;
	int setRuning = 0;
	Thread nextRunner;
	for(;i < MAX_THREADS; i++)
	{
		Thread t = threadTable[i];
		if(t.state != UNDEFINED && setRuning == 0)
		{
			switch(t.state)
			{
				case WAITING:
					t.state = RUNING;
					nextRunner = t;
					break;
				case NEW:
					t.state = RUNING;
					nextRunner = t;
					setRuning = 1;
					break;
				case RUNING:
					t.state = WAITING;
					break;
			}
			threadTable[i] = t;
		}
	}
	mops_continue((uint32_t*)&nextRunner);
}

void mops_continue(uint32_t *threadAddr)
{
	MOPS_continue(threadAddr);
}
