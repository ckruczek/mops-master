#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>


typedef struct sched_task
{
	enum 
	{
		NEW,
		RUNNING,
		WAITING,
		READY,
		TERMINATED

	} state; 
	uint32_t id;
	uint32_t prio;

} sched_task;

#endif
