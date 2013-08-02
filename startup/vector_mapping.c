#include <stdint.h>
#include "uart.h"


void map_vectors(void (*reset_addr)(), void (*return_addr)()) 
{
	uart_print("====Start copy vector table!====\n");
 	extern uint8_t __ram_start;
	uint32_t LDR_PC_PC = 0xe59ff000U;

	*(uint32_t volatile *)(&__ram_start + 0x00) = LDR_PC_PC | 0x18;			
	*(uint32_t volatile *)(&__ram_start + 0x04) = LDR_PC_PC | 0x18;
	*(uint32_t volatile *)(&__ram_start + 0x08) = LDR_PC_PC | 0x18;	
	*(uint32_t volatile *)(&__ram_start + 0x0c) = LDR_PC_PC | 0x18;	
	*(uint32_t volatile *)(&__ram_start + 0x10) = LDR_PC_PC | 0x18;	
	*(uint32_t volatile *)(&__ram_start + 0x14) = LDR_PC_PC | 0x18;	
	*(uint32_t volatile *)(&__ram_start + 0x18) = LDR_PC_PC | 0x18;	
	*(uint32_t volatile *)(&__ram_start + 0x1c) = LDR_PC_PC | 0x18;	

	*(uint32_t volatile *)(&__ram_start + 0x20) = (uint32_t)reset_addr;
	*(uint32_t volatile *)(&__ram_start + 0x24) = 0x04U;
	*(uint32_t volatile *)(&__ram_start + 0x28) = 0x08U;
	*(uint32_t volatile *)(&__ram_start + 0x2C) = 0x0CU;
	*(uint32_t volatile *)(&__ram_start + 0x30) = 0x10U;
	*(uint32_t volatile *)(&__ram_start + 0x34) = 0x14U;
	*(uint32_t volatile *)(&__ram_start + 0x38) = 0x18U;
	*(uint32_t volatile *)(&__ram_start + 0x3C) = 0x1CU;

	uart_print("====Finished copy vector table!====\n");
}

