#include "syscalls.h"

void mops_trap_handler(uint32_t trapNumber, uint32_t *sp)
{

	switch(trapNumber)
	{
		// write to uart
		case 0:
			mops_trap_writeC(*sp);	
			break;
		case 1:
			break;

		default:
			return;
	}

}

void mops_trap_writeC(uint32_t character)
{
	
	uart_send_char((char)character);

}