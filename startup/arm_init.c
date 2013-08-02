#include "arm_init.h"

void arm_init()
{
	uart_print("== Start map exception handler ==\n");
	*(uint32_t volatile *)0x24 = (uint32_t)&ARM_undef;
    *(uint32_t volatile *)0x28 = (uint32_t)&ARM_swi;
    *(uint32_t volatile *)0x2C = (uint32_t)&ARM_pAbort;
    *(uint32_t volatile *)0x30 = (uint32_t)&ARM_dAbort;
    *(uint32_t volatile *)0x34 = (uint32_t)&ARM_reserved;
    *(uint32_t volatile *)0x38 = (uint32_t)&ARM_irq;
    *(uint32_t volatile *)0x3C = (uint32_t)&ARM_fiq;
	uart_print("== Finished mapping exception handler\n");
}

void arm_abort()
{
	for(;;){}
}
