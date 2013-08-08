#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "thread.h"

void mops_schedule();
void mops_resume(int threadTableIndex);

extern Thread threadTable[MAX_THREADS];
extern void MOPS_resume(uint32_t* threadAddress);
#endif
