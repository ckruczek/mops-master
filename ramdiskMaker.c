#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BUFFER_TYPE;
const char* BUFFER_NAME = "uint16_t";

void writeRamDisk(uint16_t *buffer, unsigned long bufferSize, int stackSize)
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
			fprintf(ramDisk, "%#x", (uint16_t)0x00);

		if(i != bufferPlusStack - 1)
			fprintf(ramDisk,"%s",",");
		if(i % 16 == 0)
			fprintf(ramDisk,"%s","\n");
	}
	fprintf(ramDisk,"%s", "};");
	fclose(ramDisk);
}

void convertToUint16(uint8_t *buffer, size_t length,uint16_t *newBuffer)
{

	for(int i = 0,j=0; i < length; i+=2, j++)
	{
		newBuffer[j] = ((uint16_t)buffer[i] << 8) | buffer[i+1];
		
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
		uint16_t *finalBuffer = (uint16_t*)malloc((fileLen/ 2) * sizeof(uint16_t));
		convertToUint16(buffer, fileLen,finalBuffer);		

		fclose(file);
		if(result != fileLen)
		{
			printf("Error reading file\n");
			free(buffer);
			return;
		}
		writeRamDisk(finalBuffer, fileLen / 2, 512);
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
