#include "syscalls.h"


void print_syscall()
{
	char helloString[] = "Hello World! \n";
	unsigned length = sizeof(helloString) / sizeof(helloString[0]);
	for(int i = 0; i < length; i++)
	{
		mops_trap_writeC(helloString[i]);
	}
}
