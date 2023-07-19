/**
*	@file 	Task.h
*	@author Simon Hoffmann
*	@brief	Task Interface
*/

#ifndef __TASK_H_
#define __TASK_H_

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*---------------------------- M A C R O S ------------------------------*/

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

struct tcb{
  int32_t *sp;       			///<pointer to stack
  struct tcb *next;  			///<linked-list pointer to next tcb
	int32_t* blocked;				///<non zero if blocked (ptr to semaphore)
	uint32_t sleep;					///<non zero if sleeping (amount milliseconds sleep)
	uint8_t priority;				///<0 highest, 254 lowest
	uint8_t taskID;					///<Unique ID of task
	bool running;						///<Currently running task
	bool ready;							///<task ready to run
};	///<Task control block

typedef struct tcb tcbType;

extern tcbType *RunPt;

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* Kills a task
* @param TaskID The task to kill
* @return 1 success
*/
int task_kill(uint8_t taskID);

/**
*	Starts a task
*	@param TaskID The task to start
* @param param Parameter for task function
* @return 1 success
*/
int task_create(uint8_t taskID, uint32_t param);

/**
* Suspends the calling task
*
* This calls the Scheduler to switch tasks
* @param none
* @return none
*/
void task_yield(void);

/**
* Disables interrupts 
*
* @param none
* @return none
*/
void task_enter_critical(void);

/**
* Enables interrupts 
*
* @param none
* @return none
*/
void task_exit_critical(void);

/**
*	Sets task to sleep
*
*	Sets the time for task to sleep and calls task_yield
*	@param seconds Time for task to sleep
* @return none
*/
void task_sleep(uint32_t seconds);

/**
* Gets the ID of the calling task
* @param none
* @return Thread ID of calling task
*/
uint32_t task_getID(void);

#endif
