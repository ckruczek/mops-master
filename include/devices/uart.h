/***************************************************************
        Copyright ARM Ltd 2002-6. All rights reserved.
****************************************************************
    Versatile test program for nested-interrupt handler code
****************************************************************
uart.h - This is the uart header file. It contains code which is
         used to control the uart (see uart.c). The values for 
         "DIVISOR_INT" and "DIVISOR_FRAC" were derived from the
         PL011 UART Primecell Technical Reference Manual (3-10).
***************************************************************/

#ifndef VERSATILE_UART_H
#define VERSATILE_UART_H

#include <stdint.h>
#include "vic.h"

// to recieve interrupts from uart
#define UART0_INTENABLE		(1<<12)
#define UART_MASK_RXIM 		(1<<4) 

typedef volatile struct
{
  uint32_t DataRegister;
  union
  {
	uint32_t ReceiveStatus;
	uint32_t ErrorClear;
  } RecvStatusErrClear;
  uint32_t Reserved1[4];
  const uint32_t Flags;
  uint32_t Reserved2;
  uint32_t IrDALowPower;
  uint32_t BaudRateDivisorInt;
  uint32_t BaudRateDivisorFrac;
  uint32_t LineControlHigh;
  uint32_t ControlRegister;
  uint32_t InterruptFIFOLevel;
  uint32_t InterruptMask;
  uint32_t InterruptRawStatus;
  uint32_t InterruptStatus;
  uint32_t InterruptClear;
  uint32_t DMAControl;
} periph_uart;

extern periph_uart board_uart;

void init_uart(void);
void isr_uart();
void uart_send_char(char c);
void uart_print(const char* text);
#endif /* !defined VERSATILE_UART_H */
