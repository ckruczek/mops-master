/***************************************************************
        Copyright ARM Ltd 2002-6. All rights reserved.
****************************************************************
    Versatile test program for nested-interrupt handler code
****************************************************************
timer.c - This is the Timer module. It contains the 
          initialisation prodecure for the Timer, an interrupt 
          clear function, and an interrupt handler.
***************************************************************/

#include "vic.h"
#include "timer.h"


void isr_Timer(void)
{
	timer_clear_interrupt();
	uart_print("tick\n");
}

/***************************************************************
timer_clear_interrupt - This function writes to the timer 
                        interrupt clear register in the timer.
***************************************************************/

void timer_clear_interrupt(void)
{
    dual_timer.Timer1.TimerIntClr = 0x0;
	vic_clear_interrupt(TIMER_INTENABLE);
	vic_enable_interrupt(TIMER_INTENABLE);
}

/***************************************************************
init_timer - This function initialises the timer whos base
             address is defined externally, i.e. in a scatter or 
             header file.
***************************************************************/

void init_timer(void)
{
    dual_timer.Timer1.TimerIntClr = 1;
    dual_timer.Timer1.TimerLoad = 1000000;
    dual_timer.Timer1.TimerControl |=
        (TIMER_CONTROL_MODE_PERIODIC |
         TIMER_CONTROL_INT_ENABLED |
		 TIMER_CONTROL_ENABLED);
	uart_print("== Timer configured ==\n");
}
