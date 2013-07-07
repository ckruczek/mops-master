//#include "syscalls.h"

void klaus()
{	
//	for(;;)
	{	 
		asm("mov r0, #33");
		asm("swi 0x0");
	}
}


