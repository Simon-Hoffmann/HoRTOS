/**
*	@file 	lcd.c
*	@author Simon Hoffmann
*	@brief	UART hardware controll
*
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "uart.h"
#include "stm32g474xx.h"


/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */
																							
/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Initializes the UART
*
* @details UART1 & UART3
*	@param 	none
*	@return none
*/
void uart_init(void){
		/*Pc connection*/
		GPIOA->MODER &= ~((3<<18)|(3<<20)); // Pin config as PA10->RxD & PA9->TxD
		GPIOA->MODER |= ((2<<18)|(2<<20));
		GPIOA->AFR[1]|= (7<<4) |(7<<8); // Pins 8 .. 15 in AF high register
		RCC->APB2ENR|= (1<<14); // USART1 = enable
		USART1->CR1 |= (0<<28)|(0<<12)|(0<<10); // 8 bits (M[1:0]=00), no parity
		USART1->CR2 |= (0<<12); // 1 stop bit
		USART1->BRR = 5000; 
		USART1->CR1 |= (1<<3)|(1<<2)|(1<<0); // Tx = Rx = USART = enable

		/*keyboard*/
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; // GPIOA = enable
		GPIOC->MODER &= ~((3<<20)|(3<<22)); // Pin config as PA10->RxD & PA9->TxD
		GPIOC->MODER |= ((2<<20)|(2<<22));
		GPIOC->AFR[1]|= (7<<8) |(7<<12); // Pins 8 .. 15 in AF high register
		RCC->APB1ENR1|= (1<<18); // USART1 = enable
		USART3->CR1 |= (1<<28)|(0<<12)|(1<<10); // 8 bits (M[1:0]=00), no parity
		USART3->CR2 |= (0<<12); // 1 stop bit
		USART3->BRR = 40000; 
		USART3->CR1 |= (1<<3)|(1<<2)|(1<<0); // Tx = Rx = USART = enable
}

/**
*	Sends a char over UART1 to the pc connected
*
*	@param 	c		char to send
*	@return none
*/
void UART_SendChar (char c)
{
		
	while (!(USART1->ISR & (1<<7)));  // Wait for TC to SET.. This indicates that the data has been transmitted
	USART1->TDR = c; // LOad the Data
}

/**
*	Receives a char from UART3 the connected keyboard to the device
*
*	@details	Has a timeout, retries 10 times, if nothing to receive 0 is returned.
*	@param 	none
*	@return uint8_t character received
*/
uint8_t UART_ReceiveChar (void)
{
	uint8_t Temp;
	int retry = 0;
	
	while (!(USART3->ISR & (1<<5))){
		retry++;
		if(retry >= 10){
			return 0;
		}
	}  // Wait for RXFNE to SET.. This indicates that the data has been Received
	Temp = USART3->RDR;  	// Read the data.
	Temp &= 0x7F;					// Mask MSB away because only 7bit data
	return Temp;
}
