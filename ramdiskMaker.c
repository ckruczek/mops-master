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

	fprintf(ramDisk, "extern const int ramdisk[%ld];",bufferSize);
	fclose(ramDisk);

	ramDisk = fopen("ramdisk.c", "w+");
	fprintf(ramDisk,"#include \"ramdisk.h\" \n");
	fprintf(ramDisk,"const int ramdisk[%ld] = {",bufferSize);

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
	int fileDes = open(argv[1],O_RDONLY,0);

	if(fileDes != -1)
	{

		Elf *elfFile = elf_begin(fileDes,ELF_C_READ,NULL);
		Elf_Kind ek = elf_kind(elfFile);
/*		switch(ek)
		{
			case ELF_K_AR:
				printf("elf archive");
				break;
			case ELF_K_ELF:
				printf("elf object");
				break;
			case ELF_K_NONE:
				printf("elf data");
				break;
		}*/

		Elf_Scn *scn;;
		GElf_Shdr shdr;
		Elf_Data *data;
		char* name;
		size_t n, shstrndx,sz;
		if(elf_version(EV_CURRENT) == EV_NONE)
		{
			printf("error library init\n");
			return -1;
		}
		if(elf_getshdrstrndx(elfFile, &shstrndx) != 0)
		{	
			printf("getshdrstrndx() failed\n");
			return -1;
		}

		scn = NULL;
		printf("before while\n");
		while((scn = elf_nextscn(elfFile, scn)) != NULL)
		{
			printf("section\n");
			if(gelf_getshdr(scn,&shdr) != &shdr)
			{
				printf("getshdr failed");
				return -1;
			}

			if((name = elf_strptr(elfFile,shstrndx,shdr.sh_name)) == NULL)
			{
				printf("elf_strptr failed");
				return -1;

			}

			printf("Section %-4.4jd %s\n",(uintmax_t)
					elf_ndxscn(scn),name);
		}
		close(fileDes);
		elf_end(elfFile);
	}
/*
		if(argc > 1)
		{
			readFile(argv[1]);
		}
		else
		{
			printf("Not enough arguments\n");
		}	
*/	
}
