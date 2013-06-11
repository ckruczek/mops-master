/***************************************************************
        Copyright ARM Ltd 2002-6. All rights reserved.
****************************************************************
    Versatile test program for nested-interrupt handler code
****************************************************************
uart.c - This is the uart module. It contains code used to deal
         with data transfers via the uart.
***************************************************************/

#include "uart.h"

/****************************************************************
init_uart - This function handles initialisation in the uart, by
            setting the constants used to defined the baud rate, 
            and also the control bits.
***************************************************************/

void isr_uart()
{
	board_uart.InterruptClear |= UART_MASK_RXIM;
	vic_clear_interrupt(UART0_INTENABLE);
	uart_send_char((char)board_uart.DataRegister);
	vic_enable_interrupt(UART0_INTENABLE);
}

void init_uart(void)
{
    board_uart.ControlRegister |= UART0_INTENABLE;
	board_uart.InterruptMask  |= UART_MASK_RXIM;
	uart_print("== Uart0 configured ==\n");
}

void uart_send_char(char c)
{
    while((board_uart.Flags & 0x80) == 0);
    board_uart.DataRegister = c;
}


void uart_print(const char* text)
{
	while(*text != '\0')
		uart_send_char(*text++);
}
