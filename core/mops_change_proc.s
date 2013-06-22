
	.text
	.code 32

	.global MOPS_change_proc
	.func	MOPS_change_proc
MOPS_change_proc:
	
	stmfd sp!, {r0-r12,lr}
		
	// r0 contains the address to the thread,
	// r0 + 0x08 -> thread start address
	// r0 + 0x0c -> thread end address
	// r0 + 0x10 -> thread sp address
	

	ldmfd sp!, {r0-r12,pc}

	.endfunc
	.end
