#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "thread.h"

void mops_schedule();
void mops_continue(uint32_t *threadAddr);

static int currIndex = 0;

#endif
