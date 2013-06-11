#include "vic.h"

void vic_enable_interrupt(unsigned int status)
{
	primary_vic.IntEnable |= status;
}

void vic_clear_interrupt(unsigned int status)
{
	primary_vic.IntEnClear |= status;
}

void vic_enable_as_fiq(unsigned int interrupt)
{
	primary_vic.IntSelect |= (interrupt);
}


void vic_enable_as_irq(unsigned int interrupt)
{
	primary_vic.IntSelect &= ~(interrupt);
}

void vic_clear_vect_addr()
{
	primary_vic.VectAddr = (uint32_t)&primary_vic.VectAddr;
}

void init_vic()
{
	/*
	// register secondary vic
	primary_vic.VectAddrs[0] = (uint32_t)&irq_secondary_vic;
	primary_vic.VectCntl[0] |= (uint32_t)(PVICSOURCE_SVIC | VIC_VECTOR_ENABLE); */
	
	/** INIT TIMER AND ENABLE INTERRUPT IN VIC ** */
	primary_vic.VectAddrs[1] =	(uint32_t) &isr_Timer;
	primary_vic.VectCntl[1]	|=	(uint32_t)(PVICSOURCE_TIMER | VIC_VECTOR_ENABLE);

	vic_enable_as_irq(TIMER_INTENABLE);
	vic_enable_interrupt(TIMER_INTENABLE);

	/** INIT UART0 AND ENABLE INTERRUPTS IN VIC ** */
	primary_vic.VectAddrs[2] = (uint32_t)&isr_uart;
	primary_vic.VectCntl[2] |= (uint32_t)(PVICSOURCE_UART0 | VIC_VECTOR_ENABLE);
	
	vic_enable_as_irq(UART0_INTENABLE);
	vic_enable_interrupt(UART0_INTENABLE);

}
