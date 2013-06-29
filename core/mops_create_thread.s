
	.text
	.code 32

	.global MOPS_create_thread
	.func	MOPS_create_thread
MOPS_create_thread:

	mov r12,sp
	// this loads the new stackpointer
	ldr sp, [r0,#0x10]
	stmfd sp!, {r0-r12,lr}
	// this loads the end pointer to r2, this is needed to set stackpointer and programmcounter
	ldr pc, [r0,#0x08]
	// r0 contains the address to the thread,
	// r0 + 0x08 -> thread start address
	// r0 + 0x0c -> thread end address
	// r0 + 0x10 -> thread sp address
	ldmfd sp!,{r0-r12,pc}
	.endfunc
	.end
