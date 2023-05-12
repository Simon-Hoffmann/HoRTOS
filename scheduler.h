/**
*	@file 	scheduler.h
*	@author Simon Hoffmann
*	@brief	scheduler Interface
*/

#ifndef __SCHEDULER_H_
#define __SCHEDULER_H_

/*-------------------------- I N C L U D E S ----------------------------*/

#include "task.h"

/*---------------------------- M A C R O S ------------------------------*/

#define STACKSIZE   100      					///<Number of 32-bit words in stack
#define CLOCK_SPEED	48000000							///<Microcontroller clock speed
#define TIME_1MS  	CLOCK_SPEED / 1000		///<Depending on clock
#define TIME_2MS  	2*TIME_1MS

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Initializes the operating system
*
*	Disables interrupts until Scheduler_Launch is called.
* @details Adds the standard CPU usage task and all tasks from tasklist.h to the scheduler, activating the ones that have startOnLaunch set
*	@param 	none
*	@return none
*/
void scheduler_init(void);
	
/**
* Launches the Scheduler
*
*	Sets the Systick_Handler execution period, enables the clock and starts the first task in tcbs.
* @details Scheduler_Init must be called beforehand.
*	@param theTimeSlice 	the execution period of the Systick
*	@return none
*/
void scheduler_launch(uint32_t timeSlice);

/**
*	Starts a task
*
*	Resets the InitialStack, Sets the function pointer (PC), param (R0) and function end (LR).
*	@details Resetting the Initialstack is for the purpose of the same task having previously run, so the stack does not have any old states contained.
* @param taskID The ID of the task to start
* @param param The parameter (value/pointer) the function should be given
*	@return 1 for success
*/
int scheduler_create(uint8_t taskID, uint32_t param);


/**
*	Stops a task
*
*	Sets the running flad to false for the task.
*	@details Resetting the Initialstack is for the purpose of the same task having previously run, so the stack does not have any old states contained.
* @param taskID The ID of the task to stop
*	@return 1 success
*/
int scheduler_destroy(uint8_t taskID);


/**
*	Sets the initial stack of a task
*
* Sets the values of all the registers saved in the stack. 
*	For debugging purposes, the Register number is stored in the relevant stack space at initialisation.
*	@details	Is called when a task is started
*	@param 	i Index of task in task_list to be started
*	@return none
*/
void scheduler_setInitialStack(int i);

/**
*	Adds task to Scheduler
*	
*	Adds a new task to the tcbs array for the scheduler. It edits the next and previous fields of the respective task around the inserted task.
* @details Should only be called in Scheduler_Init, during OS runtime no new tasks should be added
*	@param task The function pointer to the function for the task
*	@param priority The priority of the task
*	@param taskID The id to be given to the task
* @return 1 success
*/
int scheduler_addTask(void(*task)(uint32_t param), uint8_t priority, uint8_t taskID);

/**
*	Decrements sleeping tasks
*
* @details decrements the sleep counters of all currently sleeping tasks
*	@param 	none
* @return none
*/
void scheduler_decrement_sleeping_tasks(void);

#endif
