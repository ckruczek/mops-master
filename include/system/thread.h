#ifndef THREAD_H
#define THREAD_H

#define MAX_THREADS		3

#include <stdint.h>

typedef struct ThreadLayout
{
	uint32_t *start;
	uint32_t *end;
	uint32_t *sp;
	uint32_t *pc;
} ThreadLayout;

typedef struct Thread
{
	int id;
	enum 
	{
		UNDEFINED,
		NEW,
		RUNING,
		WAITING,
		READY,
		TERMINATED

	} state; 
	
	ThreadLayout data;
	int canBeScheduled;
	uint32_t all_register[16];
} Thread;

int mops_create_thread_layout(uint32_t*, uint32_t*);



#endif
