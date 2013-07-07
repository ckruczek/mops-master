/*;***************************************************************
; Copyright ARM Ltd 2002-6. All rights reserved.
;***************************************************************
; Versatile test program for nested-interrupt handler code
;***************************************************************
; initstacks.s - This is the initstacks module. It deals with 
;                stack initialisation.
;***************************************************************

; Standard definitions of mode bits and interrupt (I & F) flags in PSRs*/
	.text
	.code 32
	.global initstacks
	.func initstacks

	.equ  	Mode_USR,	 0x10
	.equ  	Mode_FIQ,    0x11
	.equ	Mode_IRQ,    0x12
	.equ	Mode_SVC,    0x13
	.equ	Mode_ABT,    0x17
	.equ	Mode_UND,    0x1B
	.equ	Mode_SYS,    0x1F // available on ARM Arch 4 and later

	.equ	I_Bit,     0x80 // when I bit is set, IRQ is disabled
	.equ	F_Bit,     0x40 // when F bit is set, FIQ is disabled


initstacks:
// stack_base could be defined above, or located in a scatter file. CPSR currently in SVC mode.
	mov r1, lr
// Enter each mode in turn and set up the stack pointer
	MSR	CPSR_c, #(Mode_FIQ|I_Bit|F_Bit)
    ldr	sp, =__fiq_stack_top
    MSR	CPSR_c, #(Mode_IRQ|I_Bit|F_Bit)
    ldr	sp, =__irq_stack_top
    MSR	CPSR_c, #(Mode_SYS|I_Bit|F_Bit)
    ldr	sp, =__sys_stack_top
    MSR	CPSR_c, #(Mode_SVC|I_Bit|F_Bit)
    ldr	sp, =__svc_stack_top
// Branch back to current mode return address (SVC in this case, as it was the initial mode)
	mov pc, r1
	.end
