/***************************************************************
        Copyright ARM Ltd 2002-6. All rights reserved.
****************************************************************
    Versatile test program for nested-interrupt handler code
****************************************************************
vic.h - This is the vic header file. It contains code 
        corresponding to the primary vic (see vic.c).
***************************************************************/

#ifndef VERSATILE_VIC_H
#define VERSATILE_VIC_H

#include <stdint.h>
#include "timer.h"
#include "uart.h"

// bit 5 is the vector enable bit in the vector control register
#define VIC_VECTOR_ENABLE	0x20
// is the bit to define a secondary vic generated irq
#define PVICSOURCE_SVIC		31
#define PVICSOURCE_TIMER	4
#define PVICSOURCE_UART0	12
#define SVICSOURCE_KMI		3
/***************************************************************
periph_primary_vic - This struct represents the primary
                     interrupt control register. Each entry here
                     is set by writing values to the appropriate
                     places in the register. The base address of
                     this peripheral is defined in the scatter
                     file.
***************************************************************/

typedef volatile struct
{
	const uint32_t IRQStatus;
	const uint32_t FIQStatus;
	const uint32_t RawIntr;
	uint32_t IntSelect;
	uint32_t IntEnable;
	uint32_t IntEnClear;
	uint32_t SoftInt;
	uint32_t SoftIntClear;
	uint32_t Protection;
	const uint32_t Reserved[3];
	uint32_t VectAddr;
	uint32_t DefVectAddr;
	const uint32_t Reserved2[50];
	uint32_t VectAddrs[32];
	const uint32_t Reserved3[32];
	uint32_t VectCntl[32];
	const uint32_t Reserved4[800];
	uint32_t VicAddress;
	const uint32_t Reserved5[896];
	uint32_t VICPeripheral[4];
	uint32_t VICPrimecell[4];
} periph_primary_vic;

/***************************************************************
periph_secondary_vic - This struct represents the secondary
                       interrupt control register. Each entry 
                       here is set by writing values to the 
                       appropriate places in the register. The 
                       base address of this peripheral is defined
                       in the scatter file.
***************************************************************/

typedef volatile struct
{
	const uint32_t Status;
	const uint32_t RawStat;
	uint32_t EnSet;
	uint32_t EnClear;
	uint32_t SoftIntSet;
	uint32_t SoftIntClear;
	uint32_t Reserved1;
	uint32_t Reserved2;
	uint32_t PicEnSet;
	uint32_t PicEnClr;
} periph_secondary_vic;

void vic_clear_vect_addr();
void vic_enable_interrupt(unsigned int);
void vic_clear_interrupt(unsigned int);
void vic_enable_as_irq(unsigned int);
void vic_enable_as_fiq(unsigned int);
void init_vic(void);
extern periph_primary_vic primary_vic;
extern periph_secondary_vic secondary_vic;


#endif /* !defined VERSATILE_VIC_H */
