#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "thread.h"

void mops_schedule();
void mops_resume(int threadTableIndex);

static int currIndex = 0;
static int lastIndex = 0;
#endif
