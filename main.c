#include <stdint.h>
#include "vic.h"
#include "timer.h"
#include "uart.h"
#include "arm_init.h"
#include "mops_loader.h"


void main(void) 
{


	arm_init();
	init_vic();
//	init_uart();
	init_timer();
	mops_load_ramdisk();
 	uart_print("=================\n");
	uart_print("Registered all important services, system is ready!\n");
	for(;;)
	{
	}
}

void __aeabi_unwind_cpp_pr0(void){}
void __aeabi_unwind_cpp_pr1(void){}
