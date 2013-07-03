
test.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <func>:
   0:	e52db004 	push	{fp}		; (str fp, [sp, #-4]!)
   4:	e28db000 	add	fp, sp, #0
   8:	e24dd00c 	sub	sp, sp, #12
   c:	e3a03000 	mov	r3, #0
  10:	e50b3008 	str	r3, [fp, #-8]
  14:	e3a0002a 	mov	r0, #42	; 0x2a
  18:	e28bd000 	add	sp, fp, #0
  1c:	e8bd0800 	ldmfd	sp!, {fp}
  20:	e12fff1e 	bx	lr
