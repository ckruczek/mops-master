//#include "syscalls.h"

void func()
{	
	for(;;)
	{
	  asm("mov r0, #33");
	  asm("swi 0x0");
	}
}


