/**
*	@file 	semaphore.h
*	@author Simon Hoffmann
*	@brief	Semaphores Interface
*/

#ifndef __SEMAPHORE_H_
#define __SEMAPHORE_H_

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

typedef int32_t Semaphore;	///<Semaphore consists of a int value for incrementing or decrementing

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* Initializes a Semaphore
*
*	Sets the value of the semaphore
*	@param sem Pointer to semaphore
*	@param value Value to set on semaphore
* @return none
*/
void semaphore_init(Semaphore *sem, uint8_t value);

/**
* Calls wait on Semaphore
*
* Decrements semaphore value. If the semaphore is lower 0 (it is "empty"), then the calling thread is suspended and blocked. Blocking saves the semaphore pointer into the blocked field.
* @param sem Pointer to semaphore
* @return none
*/
void semaphore_wait(Semaphore *sem);

/**
* Calls signal on Semaphore
*
* Increments semaphore value. If the semaphore was smaller or equal to 0 this means a thread is blocked on this semaphore.
* The function looks through all blocked threads for one with the pointer to this semaphore and unblocks the thread.
* @param sem Pointer to semaphore
* @return none
*/
void semaphore_signal(Semaphore *sem);


#endif
