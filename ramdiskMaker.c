#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <libelf.h>
#include <gelf.h>
void writeRamDisk(char * buffer, unsigned long bufferSize)
{
	FILE *ramDisk;
	ramDisk = fopen("ramdisk.h", "w+");

	fprintf(ramDisk, "extern const char ramdisk[%ld];",bufferSize);
	fclose(ramDisk);

	ramDisk = fopen("ramdisk.c", "w+");
	fprintf(ramDisk,"#include \"ramdisk.h\" \n");
	fprintf(ramDisk,"const char ramdisk[%ld] = {",bufferSize);

	for(int i =0; i < bufferSize; i++)
	{
		fprintf(ramDisk,"%#x",(char)buffer[i]);
		if(i != bufferSize - 1)
			fprintf(ramDisk,"%s",",");
		if(i % 16 == 0)
			fprintf(ramDisk,"%s","\n");
	}
	fprintf(ramDisk,"%s", "};");
	fclose(ramDisk);
}


void readFile(const char* name)
{
	FILE *file;
	char *buffer;
	unsigned long fileLen;

	file = fopen(name, "rb");
	
	// file lenght
	fseek(file,0, SEEK_END);
	fileLen = ftell(file);
	rewind(file);
	printf("Readed %ld bytes\n",fileLen);
	buffer = (char*)malloc(fileLen + 1);
	if(buffer)
	{
		size_t result = fread(buffer,1,fileLen ,file);
		if(result != fileLen)
		{
			printf("Error reading file");
			return;
		}
		fclose(file);
		writeRamDisk(buffer, fileLen);
		printf("Finished writing ramdisk.h\n");
		free(buffer);

	}

}


int main(int argc, char* argv[])
{

		if(argc > 1)
		{
			readFile(argv[1]);
		}
		else
		{
			printf("Not enough arguments\n");
		}	

}
