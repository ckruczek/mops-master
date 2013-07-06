//#include "syscalls.h"

void func()
{	
	  asm("mov r0, #33");
	  asm("swi 0x0");
}


