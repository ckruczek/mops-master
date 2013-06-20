#ifndef THREAD_H
#define THREAD_H

#define MAX_THREADS		3

#include <stdint.h>

typedef struct ThreadLayout
{
	uint32_t *start;
	uint32_t *end;
	uint32_t *sp;
} ThreadLayout;

typedef struct Thread
{
	int id;
	enum 
	{
		NEW,
		RUNNING,
		WAITING,
		READY,
		TERMINATED

	} state; 

	ThreadLayout data;
} Thread;

Thread threadTable[MAX_THREADS];



#endif
