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

	.global ARM_irq2
	.func	ARM_irq2
ARM_irq2:
	// change to irq mode and disable interrupts
	// save old status
	mrs r0, spsr
	
	msr cpsr_c, #(Mode_IRQ | NO_IRQ)
	sub lr, lr, #4
	stmfd sp!, {lr}
	// save the current 
	stmfd sp!, {r0,r1,lr}
	// get the primary vic base address
	ldr r0, =primary_vic
	// on offset 0x30 is the vector address for the current isr
	ldr r1, [r0,#0x30]
	mov r2, #100
	stmfd sp!, {r0-r2,lr}
	mov lr, pc
	bx r1
	ldr r0, =vic_clear_vect_addr
	mov lr, pc
	bx r0
	ldmfd sp!,{r0-r2,lr}
	ldmfd sp!, {r0,r1,lr}
	msr spsr_cxsf, r0
	ldmfd sp!, {pc}^
	.size ARM_irq2, . - ARM_irq2
	.endfunc
/*****************************************************************************
* void ARM_irq(void);
*/
    .global ARM_irq
    .func   ARM_irq
ARM_irq:
/* IRQ entry {{{ */
	MOV     r13,r0              /* save r0 in r13_IRQ */
    SUB     r0,lr,#4            /* put return address in r0_SYS */
    MOV     lr,r1               /* save r1 in r14_IRQ (lr) */
    MRS     r1,spsr             /* put the SPSR in r1_SYS */

    MSR     cpsr_c,#(SYS_MODE | NO_IRQ) /* SYSTEM, no IRQ, but FIQ enabled! */
    STMFD   sp!,{r0,r1}         /* save SPSR and PC on SYS stack */
    STMFD   sp!,{r2-r3,r12,lr}  /* save APCS-clobbered regs on SYS stack */
    MOV     r0,sp               /* make the sp_SYS visible to IRQ mode */
    SUB     sp,sp,#(2*4)        /* make room for stacking (r0_SYS, r1_SYS) */

    MSR     cpsr_c,#(IRQ_MODE | NO_IRQ) /* IRQ mode, IRQ/FIQ disabled */
    STMFD   r0!,{r13,r14}       /* finish saving the context (r0_SYS,r1_SYS)*/

    MSR     cpsr_c,#(SYS_MODE | NO_IRQ) /* SYSTEM mode, IRQ disabled */
/* IRQ entiry }}} */
//	bl arm_irq
// ldmfd sp!, {fp, pc}
	bl ARM_isr_handler
//    ldr r12, =arm_irq
//	mov	lr,	pc
//	bx  r12                 /* call the C IRQ-handler (ARM/THUMB) */
 		
/* IRQ exit {{{ */
    MSR     cpsr_c,#(SYS_MODE | NO_INT) /* SYSTEM mode, IRQ/FIQ disabled */
    MOV     r0,sp               /* make sp_SYS visible to IRQ mode */
    ADD     sp,sp,#(8*4)        /* fake unstacking 8 registers from sp_SYS */

    MSR     cpsr_c,#(IRQ_MODE | NO_INT) /* IRQ mode, both IRQ/FIQ disabled */
    MOV     sp,r0               /* copy sp_SYS to sp_IRQ */
    LDR     r0,[sp,#(7*4)]      /* load the saved SPSR from the stack */
    MSR     spsr_cxsf,r0        /* copy it into spsr_IRQ */

    LDMFD   sp,{r0-r3,r12,lr}^  /* unstack all saved USER/SYSTEM registers */
    NOP                         /* can't access banked reg immediately */
    LDR     lr,[sp,#(6*4)]      /* load return address from the SYS stack */
	MOVS    pc,lr               /* return restoring CPSR from SPSR */
/* IRQ exit }}} */
    .size   ARM_irq, . - ARM_irq
    .endfunc
/*****************************************************************************
* void ARM_fiq(void);
*/
    .global ARM_fiq
    .func   ARM_fiq
ARM_fiq:
/* FIQ entry {{{ */
    MOV     r13,r0              /* save r0 in r13_FIQ */
    SUB     r0,lr,#4            /* put return address in r0_SYS */
    MOV     lr,r1               /* save r1 in r14_FIQ (lr) */
    MRS     r1,spsr             /* put the SPSR in r1_SYS */

    MSR     cpsr_c,#(SYS_MODE | NO_INT) /* SYSTEM mode, IRQ/FIQ disabled */
    STMFD   sp!,{r0,r1}         /* save SPSR and PC on SYS stack */
    STMFD   sp!,{r2-r3,r12,lr}  /* save APCS-clobbered regs on SYS stack */
    MOV     r0,sp               /* make the sp_SYS visible to FIQ mode */
    SUB     sp,sp,#(2*4)        /* make room for stacking (r0_SYS, SPSR) */

    MSR     cpsr_c,#(FIQ_MODE | NO_INT) /* FIQ mode, IRQ/FIQ disabled */
    STMFD   r0!,{r13,r14}       /* finish saving the context (r0_SYS,r1_SYS)*/

    MSR     cpsr_c,#(SYS_MODE | NO_INT) /* SYSTEM mode, IRQ/FIQ disabled */
/* FIQ entry }}} */

    /* NOTE: NOTE: BSP_fiq must NEVER enable IRQ/FIQ interrrupts!
    */
    LDR     r12,=arm_fiq
    MOV     lr,pc               /* store the return address */
    BX      r12                 /* call the C FIQ-handler (ARM/THUMB)


/* FIQ exit {{{ */              /* both IRQ/FIQ disabled (see NOTE above) */
    MOV     r0,sp               /* make sp_SYS visible to FIQ mode */
    ADD     sp,sp,#(8*4)        /* fake unstacking 8 registers from sp_SYS */

    MSR     cpsr_c,#(FIQ_MODE | NO_INT) /* FIQ mode, IRQ/FIQ disabled */
    MOV     sp,r0               /* copy sp_SYS to sp_FIQ */
    LDR     r0,[sp,#(7*4)]      /* load the saved SPSR from the stack */
    MSR     spsr_cxsf,r0        /* copy it into spsr_FIQ */

    LDMFD   sp,{r0-r3,r12,lr}^  /* unstack all saved USER/SYSTEM registers */
    NOP                         /* can't access banked reg immediately */
    LDR     lr,[sp,#(6*4)]      /* load return address from the SYS stack */
    MOVS    pc,lr               /* return restoring CPSR from SPSR */
/* FIQ exit }}} */

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
* void ARM_swi(void);
*/
    .global ARM_swi
    .func   ARM_swi
ARM_swi:
    LDR     r0,Csting_swi
    B       ARM_except
    .size   ARM_swi, . - ARM_swi
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

