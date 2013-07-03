//#include "syscalls.h"

void func()
{	
	int i = 0;
	for(; i < 10; i++)
	{
		asm("mov r0, #65");
		asm("swi 0x0");
	}
//	int i = 0;
//	asm("mov r0, #42");
//	mops_trap_writeC('h');	

}


