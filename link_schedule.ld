ENTRY(mops_schedule) 
SECTIONS
{
	. =0x000000;
 	.text : { *(.text) } 
 	.data : { *(.data) }

	threadTable = ABSOLUTE(.);
}

