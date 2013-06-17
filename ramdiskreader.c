#include "ramdisk.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	
	FILE *file = fopen("a.o","w+");

	int length = sizeof(ramdisk) / sizeof(ramdisk[0]);
	
	for(int i = 0; i < length; i++)
	{
		fputc((int)ramdisk[i],file);
	}
	
	return 0;
}
