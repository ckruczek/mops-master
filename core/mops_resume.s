/*
 r0 contains the address to the thread,
 r0 + 0x08 -> thread start address
 r0 + 0x0c -> thread end address
 r0 + 0x10 -> thread sp address
 r0 + 0x14 -> thread pc 
 r0 + 0x18 -> can be scheduled
 r0 + 0x1C -> all_register
*/

	.text
	.code 32

	.global MOPS_resume
	.func	MOPS_resume
MOPS_resume:
	stmfd sp!,{r0-r12,lr}

	// calculate address of all_registers array
	add r1, r0, #0x1C
	mov r0, r1
	stmfd sp!, {r0}
	ldmfd r0!,{r0-r12}
	ldmfd sp!,{r0}
	mov lr,pc
	ldr pc,[r0,#15*4]
	// get stackpointer
	
	ldmfd sp!,{r0-r12,pc}
	.endfunc
	.end
