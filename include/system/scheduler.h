#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "thread.h"

void mops_schedule();
void mops_resume(int threadTableIndex);
extern void MOPS_schedule();
Thread threadTable[MAX_THREADS];
extern Thread* pThreadTables[MAX_THREADS];
extern void MOPS_resume(uint32_t* threadAddress);
extern int currThreadIndex;
#endif
