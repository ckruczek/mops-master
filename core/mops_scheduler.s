
	.text
	.code 32

	.global mops_resume
	.func	mops_resume

mops_resume:
	stmfd sp!, {r0-r12}
	// get the address of the threadTableentry we need
	// on 0x40 we located the table with the addresses of the threads
	mov r1,#0x40
	ldr r1, [r1]
	// load the currThreadIndex variable
	// ****** <begin index>
	mov r3,#0x50
	ldr r2, [r3]
	// check if the index is bigger than 3, than start from beginning and set to 0
	cmp r2, #2
	moveq r2, #0
	streq r2,[r3]
	// increment and save back
	add r2,r2, #1
	str r2,[r3]
	// ****<end index>
	
	// in r0 is the index and we multipli r0 with 4 to get to the next index
	mov r7,#4
	mul r2,r2,r7
	// finished creating index
	
	// get the address we need by load the nth-address from r1, index is defined in r0
	mov r1,#0x40
	ldr r0,[r1,r2]
	bl 	MOPS_resume
	
	.endfunc

/*
 r0 contains the address to the thread,
 r0 + 0x08 -> thread start address
 r0 + 0x0c -> thread end address
 r0 + 0x10 -> thread sp address
 r0 + 0x14 -> thread pc 
 r0 + 0x18 -> can be scheduled
 r0 + 0x1C -> all_register
*/

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
