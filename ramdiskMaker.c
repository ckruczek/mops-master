#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

typedef uint16_t BUFFER_TYPE;
typedef uint32_t FINAL_BUFFER_TYPE;

const char* BUFFER_NAME = "uint32_t";

void writeRamDisk(FILE *ramdisk,FINAL_BUFFER_TYPE *buffer, unsigned long bufferSize, int stackSize)
{
	for(int i =0; i < bufferSize+1; i++)
	{
		if(i != bufferSize)
		{
			fprintf(ramdisk,"%#x",buffer[i]);
			fprintf(ramdisk,"%s",",");
		}
		else
			fprintf(ramdisk,"%i",stackSize);
		if(i % 16 == 0)
			fprintf(ramdisk,"%s","\n");
	}
}

void convertToUint32(BUFFER_TYPE *buffer, size_t length, FINAL_BUFFER_TYPE *newBuffer)
{
	for(int i = 0, j = 0; i < length; i+=2,j++)
	{
		newBuffer[j] = ((FINAL_BUFFER_TYPE)buffer[i+1] << 16 | buffer[i]);
	}
}

void readFile(FILE *ramdisk,const char* name)
{
	FILE *file;
	BUFFER_TYPE *buffer;
	unsigned long fileLen;

	file = fopen(name, "rb");
	
	size_t bufferTypeSize = sizeof(BUFFER_TYPE);
	// file lenght
	fseek(file,0, SEEK_END);
	fileLen = ftell(file);
	fileLen /= bufferTypeSize;
	rewind(file);

	printf("Read %ld bytes\n",fileLen);
	buffer = (BUFFER_TYPE*)malloc(fileLen * bufferTypeSize);
	if(buffer)
	{
		size_t result = fread(buffer,sizeof(BUFFER_TYPE),fileLen ,file);
		size_t bufferLength = (fileLen * sizeof(FINAL_BUFFER_TYPE)) / sizeof(FINAL_BUFFER_TYPE) / 2;
		FINAL_BUFFER_TYPE *finalBuffer = (FINAL_BUFFER_TYPE*)malloc(bufferLength);
		convertToUint32(buffer,fileLen, finalBuffer);
		fclose(file);

		if(result != fileLen)
		{
			printf("Error reading file\n");
			free(buffer);
			free(finalBuffer);
			return;
		}
		writeRamDisk(ramdisk,finalBuffer, bufferLength , 512);
		printf("Finished writing ramdisk.h\n");
		free(buffer);

	}

}

void writeImageDescriptor(char* fileNames[], int length)
{	
	FILE *ramdisk = fopen("ramdisk.c", "w+");
	fprintf(ramdisk, "#include \"ramdisk.h\"\n");
	fprintf(ramdisk, "const %s imageDescriptor[%i] = {",BUFFER_NAME,length-1);
	int sum = 0;
	for(int i = 1; i < length; i++)
	{
		FILE *binFile = fopen(fileNames[i], "rb");
		fseek(binFile,0, SEEK_END);
		size_t filelength = ftell(binFile);
		filelength /= sizeof(FINAL_BUFFER_TYPE);
		fprintf(ramdisk,"%i", filelength);
		if(i != length - 1)
			fprintf(ramdisk,",");

		fclose(binFile);
		sum += filelength+1;
	}
	fprintf(ramdisk,"};\n");
	fclose(ramdisk);

	ramdisk = fopen("ramdisk.h", "a+");
	fprintf(ramdisk,"extern const %s ramdisk[%i];\n",BUFFER_NAME, sum);
	fclose(ramdisk);
	ramdisk = fopen("ramdisk.c", "a+");
	fprintf(ramdisk, "const %s ramdisk[%i] = {", BUFFER_NAME, sum);
	fclose(ramdisk);
}

int main(int argc, char* argv[])
{
	
		if(argc > 1)
		{
			FILE* ramdisk = fopen("ramdisk.h", "w+");
			fprintf(ramdisk,"#include<stdint.h>\n");
			fprintf(ramdisk, "extern const %s imageDescriptor[%i];\n",BUFFER_NAME, argc-1);
			fclose(ramdisk);
			
			writeImageDescriptor(argv,argc);
			
			ramdisk = fopen("ramdisk.c", "a+");

			for(int i = 1; i < argc; i ++)
			{
				readFile(ramdisk,argv[i]);
				if(i < argc - 1)
					fprintf(ramdisk,",");
			}
			fprintf(ramdisk,"};\n");
			fclose(ramdisk);

		}
		else
		{
			printf("Not enough arguments\n");
		}	

}
