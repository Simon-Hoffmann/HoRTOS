/**
*	@file 	task.c
*	@author Simon Hoffmann
*	@brief	task control
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "stm32g474xx.h"
#include "task.h"
#include "Scheduler.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

tcbType *RunPt;	///<Pointer to the currently running thread control block
																														
/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/**
* Scheduler
* @details From SchedulerASM.s
*/
void schedulerASM_handler(void);	

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
* Kills a task
*
*	Stops the task from running
* @param taskID The thread to kill
* @return 1 success
*/
int task_kill(uint8_t taskID){
	return scheduler_destroy(taskID);
}

/**
*	Starts a task
*	
*	Starts the task with a parameter
*	@param taskID The task to start
* @param param Parameter for thread function
* @return 1 success
*/
int task_create(uint8_t taskID, uint32_t param){
		return scheduler_create(taskID, param);
}

/**
* Suspends the calling task
*
* This calls the Scheduler to switch tasks
* @param none
* @return none
*/
void task_yield(void){
	SCB->ICSR |= 0x10000000;						//trigger PendSV 
}

/**
* Disables interrupts 
*
* @param none
* @return none
*/
void task_enter_critical(void){
	schedulerASM_disableInterrupts();
}

/**
* Enables interrupts 
*
* @param none
* @return none
*/
void task_exit_critical(void){
	schedulerASM_enableInterrupts();
}

/**
*	Sets task to sleep
*
*	Sets the time for task to sleep and calls task_yield
*	@param seconds Time for task to sleep
* @return none
*/
void task_sleep(uint32_t seconds){
	RunPt->sleep = seconds;
	task_yield();
}

/**
* Gets the ID of the calling task
* @param none
* @return Thread ID of calling task
*/
uint32_t task_getID(void){
	return RunPt->taskID;
}
