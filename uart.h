/**
*	@file 	uart.h
*	@author Simon Hoffmann
*	@brief	UART Interface
*/

#ifndef __UART_H
#define __UART_H

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>

/*---------------------------- M A C R O S ------------------------------*/


/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Initializes the UART
*
* @details UART1 & UART3
*	@param 	none
*	@return none
*/
void uart_init(void);

/**
*	Sends a char over UART1 to the pc connected
*
*	@param 	c		char to send
*	@return none
*/
void UART_SendChar (char c);

/**
*	Receives a char from UART3 the connected keyboard to the device
*
*	@details	Has a timeout, retries 10 times, if nothing to receive 0 is returned.
*	@param 	none
*	@return uint8_t character received
*/
uint8_t UART_ReceiveChar (void);

#endif
