/**
*	@file 	fifo.h
*	@author Simon Hoffmann
*	@brief	FIFO Interface
*/

#ifndef __FIFO_H
#define __FIFO_H

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>

/*---------------------------- M A C R O S ------------------------------*/


/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Initializes the fifo
*
*	@param 	none
*	@return none
*/
void fifo_init(void);

/**
*	Inserts an uint8_t into the fifo
*
* @details If the fifo is full nothing is done, if an element is inserted, CurrentSize semaphore is signalled for fifo_get
*	@param 	data char to insert into fifo
*	@return none
*/
void fifo_put(uint8_t data);

/**
*	Fetches a char from the fifo
*
* @details Blocks the calling thread until the CurrentSize semaphore is signalled
*	@param 	none
*	@return uint8_t fifo value
*/
uint8_t fifo_get(void);

#endif

