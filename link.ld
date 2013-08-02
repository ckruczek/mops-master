ENTRY(_start) 
SECTIONS
{
	. =0x000000;
	.ramvect  :
 	{
 		__ram_start = .;
		. += 0x1000;
 	}
 	. = ALIGN(4); 
 	. = 0x10000;

 	.startup : 
 	{ 
	    
 		startup/startup.o(.text) 
		startup/initstacks.o(.text)
 	}

	
	.fastcode :
	{ 
		*startup/arm_init.o (.text.*)
		*(.text.fastcode)
		. = ALIGN(4);
 	}	 

 	.text : { *(.text) } 
 	.data : { *(.data) }
 	.bss : { *(.bss COMMON) }

		. = ALIGN(4);
		. += 0x2000;
		stack_top = .;
 		. += 0x2000; 
 		__sys_stack_top = .;
		
		. += 0x2000;
 		__irq_stack_top = .;
		
		. += 0x2000;
		__fiq_stack_top = .;

		. += 0x2000;
		__svc_stack_top = .;
		

		__k_heap_start = .;
		. += 0x2000;
		__k_heap_end = .;

	. = 0x10140000;
	primary_vic =ABSOLUTE(.);
	. = 0x10003000;
	secondary_vic = ABSOLUTE(.);
	. = 0x101E2000;
	dual_timer = ABSOLUTE(.);
	. = 0x101F1000;
	board_uart = ABSOLUTE(.);
}
