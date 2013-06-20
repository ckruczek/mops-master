#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include "uart.h"

void mops_trap_handler(uint32_t trapNumber,uint32_t * sp);
void mops_trap_writeC(uint32_t character);
void mops_trap_writeC_handler(uint32_t character);

#endif
