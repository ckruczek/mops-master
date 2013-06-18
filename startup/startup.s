.text
 .code 32
 .global vectors_start
 .global vectors_end
 .global _start

	.equ 	I_BIT,				0x80
	.equ  	Mode_USR,	 		0x10

_start:
	b	reset_handler
	b	.
	b	.
	b	.
	b	.
	b	.
	b	.
	b	.

reset_handler:

 ldr r0, =reset_handler
 ldr sp, =stack_top
 bl map_vectors
 // init all stacks
 bl initstacks
 // save the current programm status register
  mrs r0, cpsr
 // enable irq mode
  bic r0, r0, #I_BIT
 // and save back the newly enabled mode
 msr cpsr, r0
 msr cpsr_c, #(Mode_USR)
 BL main
 B .
 
.end
