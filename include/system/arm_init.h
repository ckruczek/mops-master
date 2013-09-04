#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include "arm_irq.h"
#include "vic.h"


void arm_init();

void arm_irq()__attribute((interrupt));
void arm_fiq();
void arm_abort();


void setupUART();
void setupTimer();

#endif
