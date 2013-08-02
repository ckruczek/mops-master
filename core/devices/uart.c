#include "uart.h"
#include "syscalls.h"
/****************************************************************
init_uart - This function handles initialisation in the uart, by
            setting the constants used to defined the baud rate, 
            and also the control bits.
***************************************************************/

void isr_uart()
{
	
	board_uart.InterruptClear |= UART_MASK_RXIM;
	vic_clear_interrupt(UART0_INTENABLE);
	mops_trap_writeC((char)board_uart.DataRegister);
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
