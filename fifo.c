/**
*	@file 	fifo.c
*	@author Simon Hoffmann
*	@brief	FIFO implementation
*
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "fifo.h"
#include "semaphore.h"


/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

#define FIFOSIZE 100			
uint32_t volatile *PutPt;					///<Index for next element to be inserted in fifo
uint32_t volatile *GetPt;					///<Index for next index of available element in fifo
uint8_t static Fifo[FIFOSIZE];
Semaphore CurrentSize;						///<Current size of the fifo, used to check if an element is available to retreive
Semaphore FIFOmutex;
																							
/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Initializes the fifo
*
*	@param 	none
*	@return none
*/
void fifo_init(void){
	PutPt = GetPt = (uint32_t*)&Fifo[0];
	semaphore_init(&CurrentSize, 0);
	semaphore_init(&FIFOmutex, 1);
}

/**
*	Inserts an uint8_t into the fifo
*
* @details If the fifo is full nothing is done, if an element is inserted, CurrentSize semaphore is signalled for fifo_get
*	@param 	data char to insert into fifo
*	@return none
*/
void fifo_put(uint8_t data){
	semaphore_wait(&FIFOmutex);
	if(CurrentSize == FIFOSIZE){
		semaphore_signal(&FIFOmutex);
		return;
	}
	*(PutPt) = data;
	PutPt++;
	if(PutPt == (uint32_t*)&Fifo[FIFOSIZE]){
		PutPt = (uint32_t*)&Fifo[0];
	}
	semaphore_signal(&FIFOmutex);
	semaphore_signal(&CurrentSize);
}

/**
*	Fetches a char from the fifo
*
* @details Blocks the calling thread until the CurrentSize semaphore is signalled
*	@param 	none
*	@return uint8_t fifo value
*/
uint8_t fifo_get(void){
	uint8_t data;
	semaphore_wait(&CurrentSize);
	data = *(GetPt);
	GetPt++;
	if(GetPt == (uint32_t*)&Fifo[FIFOSIZE]){
		GetPt = (uint32_t*)&Fifo[0];
	}
	return data;
}


