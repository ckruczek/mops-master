#include "ramdisk.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
typedef void (*syscall)(void);
syscall call;

int main(int argc, char* argv[])
{
	

	FILE *file = fopen(argv[1],"r");
	fseek(file,0,SEEK_END);
	int length = ftell(file);
	rewind(file);
	printf("Read %i bytes\n",length);
	char *buffer = (char*)malloc(length+1);

//	int f = open(argv[1],O_RDONLY);
//	read(f,buffer, length);
//	close(f);
	fread(buffer,1,length,file);
	fclose(file);
	free(buffer);
//	((void (*)(void))buffer)();
//	int length = sizeof(ramdisk) / sizeof(ramdisk[0]);
//	int* code = (int*)malloc(sizeof(int) * length);

//	for(int i = 0; i < length; i++)
//	{
//		fputc((int)ramdisk[i],file);
//		code[i] = ramdisk[i];
//	}
//	unsigned offset = *(unsigned*)code;
//	call = (syscall)(code + offset);
	
//	call();
//	free(code);
	return 0;
}
