/**
*	@file 	semaphore.c
*	@author Simon Hoffmann
*	@brief	Semaphores implementation
*
* Lightweight semaphores for OS, enabling suspension of threads on blocked semaphores
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "Semaphore.h"
#include "task.h"


/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

// function definitions in schedulerASM.s
/**
* @details From SchedulerASM.s
*/
void schedulerASM_disableInterrupts(void); 
/**
* @details From SchedulerASM.s
*/
void schedulerASM_enableInterrupts(void); 


/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* Initializes a Semaphore
*
*	Sets the value of the semaphore
*	@param sem Pointer to semaphore
*	@param value Value to set on semaphore
* @return none
*/
void semaphore_init(Semaphore *sem, uint8_t value){
	*sem = value;
}

/**
* Calls wait on Semaphore
*
* Decrements semaphore value. If the semaphore is lower 0 (it is "empty"), then the calling thread is suspended and blocked. Blocking saves the semaphore pointer into the blocked field.
* @param sem Pointer to semaphore
* @return none
*/
void semaphore_wait(Semaphore *sem){
	schedulerASM_disableInterrupts();
	(*sem) = (*sem) - 1;
	if((*sem) < 0){
		RunPt->blocked = sem;
		schedulerASM_enableInterrupts();
		task_yield();
	}
	schedulerASM_enableInterrupts();
}

/**
* Calls signal on Semaphore
*
* Increments semaphore value. If the semaphore was smaller or equal to 0 this means a thread is blocked on this semaphore.
* The function looks through all blocked threads for one with the pointer to this semaphore and unblocks the thread.
* @param sem Pointer to semaphore
* @return none
*/
void semaphore_signal(Semaphore *sem){
	tcbType *pt;
	schedulerASM_disableInterrupts();
	(*sem) = (*sem) + 1;
	if((*sem) <= 0){	//if true, a thread is blocked on this semaphore
		pt = RunPt->next;	//search for thread blocked on this semaphore
		while(pt->blocked != sem){
			pt = pt->next;
		}
		pt->blocked = 0; //wake blocked thread up
	}
	schedulerASM_enableInterrupts();
} 


