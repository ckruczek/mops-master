	.cpu arm926ej-s
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"test.c"
	.text
	.align	2
	.global	func
	.type	func, %function
func:
	.fnstart
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	.save {fp}
	.setfp fp, sp, #0
	add	fp, sp, #0
#APP
@ 5 "test.c" 1
	mov r0, #65
@ 0 "" 2
@ 6 "test.c" 1
	swi 0x0
@ 0 "" 2
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.fnend
	.size	func, .-func
	.ident	"GCC: (Sourcery CodeBench Lite 2013.05-24) 4.7.3"
	.section	.note.GNU-stack,"",%progbits
