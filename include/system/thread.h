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
		UNDEFINED,
		NEW,
		RUNNING,
		WAITING,
		READY,
		TERMINATED

	} state; 

	ThreadLayout data;
} Thread;

Thread threadTable[MAX_THREADS];

int mops_create_thread_layout(uint32_t*, uint32_t*, Thread*);



#endif
