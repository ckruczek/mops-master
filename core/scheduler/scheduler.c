#include "scheduler.h"

currIndex = 0;

Thread threadTable[MAX_THREADS];

void mops_schedule()
{	
	int index = 1;
//	while(1)
	{
			if(++currIndex >= MAX_THREADS - 1)
				currIndex = 0;

			mops_resume(currIndex);
//			int i = 0;
/*			Thread nextRunner;
			for(;i < MAX_THREADS; i++)
			{

				if(threadTable[i].state != UNDEFINED)
				{
					switch(threadTable[i].state)
					{
						case WAITING:
						case NEW:
							threadTable[i].state = RUNING;
							break;
						case RUNING:
							threadTable[i].state = WAITING;
							break;
					}
				}
			}*/
//			asm("mov r0,#44");
//			asm("ldr r0, =threadTable");
//			asm("add r1, r0, #0x1C");
//			asm("mov r0, r1");
/*			asm("mov r0, %0"
				:
				:"r"(index++)
				:);*/
			// save all register in the register array
//			asm("stmfd r0!, {r0-r12,sp,lr,pc}");
//			asm("swi 11");
//			mops_resume(1);
	}
}

void mops_resume(int threadTableIndex)
{	
	if(threadTable[threadTableIndex].canBeScheduled == 1)
		MOPS_resume((uint32_t*)&threadTable[threadTableIndex]);
}
