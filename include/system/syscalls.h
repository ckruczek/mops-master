#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include "uart.h"
#include "scheduler.h"

void mops_trap_handler(uint32_t trapNumber,uint32_t * sp);
void mops_trap_writeC(uint32_t character);
void mops_trap_writeC_handler(uint32_t character);
void mops_trap_schedule(uint32_t* address);
void mops_trap_schedule_handler(uint32_t* address);
void mops_trap_exit(uint32_t threadId);
#endif
