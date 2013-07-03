#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

typedef uint16_t BUFFER_TYPE;
typedef uint32_t FINAL_BUFFER_TYPE;

const char* BUFFER_NAME = "uint32_t";

void writeRamDisk(FINAL_BUFFER_TYPE *buffer, unsigned long bufferSize, int stackSize)
{
	FILE *ramDisk;
	ramDisk = fopen("ramdisk.h", "w+");

	int bufferPlusStack = bufferSize + stackSize;
	fprintf(ramDisk, "#include <stdint.h>\n");
	fprintf(ramDisk, "extern const %s  ramdisk[%ld];",BUFFER_NAME,bufferPlusStack);
	fclose(ramDisk);

	ramDisk = fopen("ramdisk.c", "w+");
	fprintf(ramDisk,"#include \"ramdisk.h\" \n");
	fprintf(ramDisk,"const %s ramdisk[%ld] = {",BUFFER_NAME,bufferPlusStack);
	
	for(int i =0; i < bufferPlusStack; i++)
	{
		if(i < bufferSize)
			fprintf(ramDisk,"%#x",buffer[i]);
		else
			fprintf(ramDisk, "%#x", (FINAL_BUFFER_TYPE)0x00);

		if(i != bufferPlusStack - 1)
			fprintf(ramDisk,"%s",",");
		if(i % 16 == 0)
			fprintf(ramDisk,"%s","\n");
	}
	fprintf(ramDisk,"%s", "};");
	fclose(ramDisk);
}

void convertToUint32(BUFFER_TYPE *buffer, size_t length, FINAL_BUFFER_TYPE *newBuffer)
{
	for(int i = 0, j = 0; i < length; i+=2,j++)
	{
		newBuffer[j] = ((FINAL_BUFFER_TYPE)buffer[i+1] << 16 | buffer[i]);
	}
}

void readFile(const char* name)
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
		printf("Size of buffer type %i\n", sizeof(BUFFER_TYPE));
		size_t result = fread(buffer,sizeof(BUFFER_TYPE),fileLen ,file);
		size_t bufferLength = (fileLen * sizeof(FINAL_BUFFER_TYPE)) / sizeof(FINAL_BUFFER_TYPE);
		FINAL_BUFFER_TYPE *finalBuffer = (FINAL_BUFFER_TYPE*)malloc(bufferLength);
		convertToUint32(buffer,fileLen, finalBuffer);
		fclose(file);
		if(result != fileLen)
		{
			printf("Error reading file\n");
			free(buffer);
			return;
		}
		writeRamDisk(finalBuffer, bufferLength , 512);
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
