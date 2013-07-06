
	.text
	.code 32

	.global MOPS_continue
	.func	MOPS_continue
MOPS_continue:

	mov r12,sp
	// this loads the new stackpointer
	ldr sp, [r0,#0x10]
	stmfd sp!, {lr}
	stmfd sp!, {r0-r12}

	// this operation loads the startaddress of the new thread to r1
	ldr r1, [r0,#0x14]
	mov lr,pc
	bx r1
	// r0 contains the address to the thread,
	// r0 + 0x08 -> thread start address
	// r0 + 0x0c -> thread end address
	// r0 + 0x10 -> thread sp address
	// r0 + 0x14 -> thread pc 
	ldmfd sp!,{r0-r12}
	str sp, [r0, #0x10]
	ldmfd sp!, {pc}
	.endfunc
	.end
