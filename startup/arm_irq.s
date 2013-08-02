    .equ    NO_IRQ,         0x80                     /* mask to disable IRQ */
    .equ    NO_FIQ,         0x40                     /* mask to disable FIQ */
    .equ    NO_INT,         (NO_IRQ | NO_FIQ) /*mask to disable IRQ and FIQ */
    .equ    FIQ_MODE,       0x11
    .equ    IRQ_MODE,       0x12
    .equ    SYS_MODE,       0x1F
	.equ	Mode_IRQ,    0x12
	.equ	Mode_SYS,    0x1F // available on ARM Arch 4 and later
	.equ 	Mode_USR,	 0x10
    .text
    .code 32

    /* use the special section (.text.fastcode), to enable fine-tuning
    * of the placement of this section inside the linker script
    */
    .section .text.fastcode

ARM_int_enable:
	stmfd sp!, {r0,lr}
	mrs r0, cpsr
	// bic clears the bit which means we enable irqs
	bic r0, r0, #NO_IRQ
	msr cpsr, r0
	ldmfd sp!, {r0,pc}

ARM_int_disable:
	stmfd sp!, {r0,lr}
	mrs r0, cpsr
	orr r0,r0, #NO_IRQ
	msr cpsr, r0
	ldmfd sp!, {r0,pc}
	

ARM_handle_interrupt:
	stmfd sp!, {lr}
	stmfd sp!,{r0,r1,lr}
	ldr r0, =primary_vic
	ldr r1, [r0, #0x30]
	stmfd sp!, {r0-r2,lr}
	mov lr, pc
	bx r1
	ldr r0,=vic_clear_vect_addr
	mov lr, pc
	bx r0
	ldmfd sp!, {r0-r2,lr}
	ldmfd sp!, {r0,r1,lr}
	ldmfd sp!, {pc}
	.global ARM_irq
	.func	ARM_irq
ARM_irq:
	// change to irq mode and disable interrupts
	// save old status
	mrs r0, spsr
	
	//msr cpsr_c, #(Mode_IRQ | NO_IRQ)
	sub lr, lr, #4
	stmfd sp!,{lr}
	bl ARM_handle_interrupt
	msr spsr_cxsf, r0
	ldmfd sp!, {pc}^
	.size ARM_irq, . - ARM_irq
	.endfunc

/*****************************************************************************
* void ARM_swi(void);
*/
    .global ARM_swi
    .func   ARM_swi
ARM_swi:
	sub sp,sp,#4
	stmfd sp!, {r0-r12,lr}
	mrs r2, spsr
	str r2, [sp, #14*4]
	mov r1, sp
	ldr r0, [lr, #-4]
	bic r0,r0,#0xFF000000
	bl mops_trap_handler
	ldr r2, [sp,#14*4]
	msr spsr_csxf, r2
	ldmfd sp!,{r0-r12,lr}
	add sp, sp, #4
	movs pc,lr
   .size   ARM_swi, . - ARM_swi
    .endfunc
/*****************************************************************************
* void ARM_fiq(void);
*/
    .global ARM_fiq
    .func   ARM_fiq
ARM_fiq:

	mrs r0, spsr
	
	msr cpsr_c, #(FIQ_MODE | NO_INT)
	sub lr, lr, #4
	stmfd sp!, {lr}
	bl ARM_handle_interrupt
	msr spsr_cxsf, r0
	ldmfd sp!, {pc}^

	.size   ARM_fiq, . - ARM_fiq
    .endfunc


/*****************************************************************************
* void ARM_reset(void);
*/
    .global ARM_reset
    .func   ARM_reset
ARM_reset:
    LDR     r0,Csting_reset
    B       ARM_except
    .size   ARM_reset, . - ARM_reset
    .endfunc

/*****************************************************************************
* void ARM_undef(void);
*/
    .global ARM_undef
    .func   ARM_undef
ARM_undef:
    LDR     r0,Csting_undef
    B       ARM_except
    .size   ARM_undef, . - ARM_undef
    .endfunc
/*****************************************************************************
* void ARM_pAbort(void);
*/
    .global ARM_pAbort
    .func   ARM_pAbort
ARM_pAbort:
    LDR     r0,Csting_pAbort
    B       ARM_except
    .size   ARM_pAbort, . - ARM_pAbort
    .endfunc

/*****************************************************************************
* void ARM_dAbort(void);
*/
    .global ARM_dAbort
    .func   ARM_dAbort
ARM_dAbort:
    LDR     r0,Csting_dAbort
    B       ARM_except
    .size   ARM_dAbort, . - ARM_dAbort
    .endfunc

/*****************************************************************************
* void ARM_reserved(void);
*/
    .global ARM_reserved
    .func   ARM_reserved
ARM_reserved:
    LDR     r0,Csting_rsrvd
    B       ARM_except
    .size   ARM_reserved, . - ARM_reserved
    .endfunc

/*****************************************************************************
* void ARM_except(void);
*/
    .global ARM_except
    .func   ARM_except
ARM_except:
    SUB     r1,lr,#4            /* set line number to the exception address */
    MSR     cpsr_c,#(SYS_MODE | NO_INT) /* SYSTEM mode, IRQ/FIQ disabled */
    LDR     r12,=arm_abort
    MOV     lr,pc               /* store the return address */
    BX      r12                 /* call the assertion-handler (ARM/THUMB) */
    /* the assertion handler should not return, but in case it does
    * hang up the machine in the following endless loop
    */
    B       .

Csting_reset:  .string  "Reset"
Csting_undef:  .string  "Undefined"
Csting_swi:    .string  "Software Int"
Csting_pAbort: .string  "Prefetch Abort"
Csting_dAbort: .string  "Data Abort"
Csting_rsrvd:  .string  "Reserved Exception"

    .size   ARM_except, . - ARM_except
    .endfunc

    .end

