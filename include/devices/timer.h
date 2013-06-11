/***************************************************************
        Copyright ARM Ltd 2002-6. All rights reserved.
****************************************************************
    Versatile test program for nested-interrupt handler code
****************************************************************
timer.h - This is the timer header file. It contains function 
          prototypes which correspond to the timer 
		  (see timer.c).
***************************************************************/

#ifndef VERSATILE_TIMER_H
#define VERSATILE_TIMER_H

#include <stdint.h>
#include "uart.h"

#define TIMER_INTENABLE	(1<<4)
#define TIMER_CONTROL_MASK 0xEF
#define TIMER_CONTROL_ENABLED 0x80
#define TIMER_CONTROL_DISABLED 0x0
#define TIMER_CONTROL_MODE_PERIODIC 0x40
#define TIMER_CONTROL_MODE_FREE 0x0
#define TIMER_CONTROL_INT_ENABLED 0x20
#define TIMER_CONTROL_INT_DISABLED 0x0
#define TIMER_CONTROL_DIVIDE_1 0x0
#define TIMER_CONTROL_DIVIDE_16 0x4
#define TIMER_CONTROL_DIVIDE_256 0x8
#define TIMER_CONTROL_SIZE_16 0x0
#define TIMER_CONTROL_SIZE_32 0x2
#define TIMER_CONTROL_WRAPPING 0x0
#define TIMER_CONTROL_ONE_SHOT 0x1

typedef volatile struct
{
    uint32_t TimerLoad;
    const uint32_t TimerValue;
    uint32_t TimerControl;
    uint32_t TimerIntClr;
    uint32_t TimerRIS;
    uint32_t TimerMIS;
    uint32_t TimerBGLoad;
} periph_timer;

typedef volatile struct
{
	periph_timer Timer1;
	periph_timer Timer2;
} periph_dualtimer;

extern periph_dualtimer dual_timer;

void init_timer(void);
void timer_clear_interrupt(void);
void isr_Timer(void);

#endif /* !defined VERSATILE_TIMER_H */
