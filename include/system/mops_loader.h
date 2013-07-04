#ifndef MOPS_LOADER_H
#define MOPS_LOADER_H

#include <stdint.h>
#include "ramdisk.h"
#include "thread.h"

void mops_load_ramdisk();
void mops_create_thread(uint32_t *threadAddr);

#endif
