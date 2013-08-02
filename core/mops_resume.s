
	.text
	.code 32

	.global MOPS_resume
	.func	MOPS_resume
MOPS_resume:

	mov r12,sp
	ldr r0, [r0, #0x1C]
	ldmfd r0!, {r0-r12,sp,lr,pc}
	// this loads the new stackpointer
//	ldr sp, [r0,#0x10]
//	stmfd sp!, {lr}
//	stmfd sp!, {r0-r12}

	// this operation loads the startaddress of the new thread to r1
//	ldr r1, [r0,#0x14]
//	mov lr,pc
//	bx r1
	// r0 contains the address to the thread,
	// r0 + 0x08 -> thread start address
	// r0 + 0x0c -> thread end address
	// r0 + 0x10 -> thread sp address
	// r0 + 0x14 -> thread pc 
	// r0 + 0x18 -> can be scheduled
	// r0 + 0x1C -> all_register
//	ldmfd sp!,{r0-r12}
//	str sp, [r0, #0x10]
	ldmfd sp!, {pc}
	.endfunc
	.end
