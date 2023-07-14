/**
*	@file 	scheduler.c
*	@author Simon Hoffmann
*	@brief	scheduler for the os
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "stm32g474xx.h"
#include <stdint.h>
#include "scheduler.h"
#include "tasklist.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

uint32_t totalThreadsRunning;						///<Total number of currently running tasks
tcbType tcbs[NUMTHREADS];								///<Array of all thread control blocks
int32_t Stacks[NUMTHREADS][STACKSIZE];	///<Array of all the Stacks for all tasks
																														
/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/**
* @details From SchedulerASM.s
*/
void schedulerASM_disableInterrupts(void); 
/**
* @details From SchedulerASM.s
*/
void schedulerASM_enableInterrupts(void); 
/**
*	Starts OS. Loads registers with first task
* @details From SchedulerASM.s
*/
void schedulerASM_start_os(void);


/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Priotity Scheduler

*	Has functionality:	
*	-	Task blocking
*	-	Task sleeping
*	- Task running/stopped
*	.
*	Loops through all tasks that are running and not blocked/sleeping to find the next one with highest priority. 
*	If there are several tasks with the same priority, then Round Robin is used.
*	@details	Called from Systick_Handler in SchedulerASM.s
*	@param 	none
*	@return none
*/
void scheduler(void){
	uint8_t max_priority = 255;		
	tcbType *pt;
	tcbType *bestPt;
	RunPt->running = false;
	pt = RunPt;
	do{
		pt = pt->next;
		if((pt->priority < max_priority) && ((pt->ready)&&(pt->blocked)==0)&&((pt->sleep)==0)){
			max_priority = pt->priority;
			bestPt = pt;
		}
	} while(RunPt != pt);
	RunPt = bestPt;
	RunPt->running = true;
}

/**
* Launches the Scheduler
*
*	Sets the Systick_Handler execution period, enables the clock and starts the first task in tcbs.
* @details Scheduler_Init must be called beforehand.
*	@param theTimeSlice 	the execution period of the Systick
*	@return none
*/
void scheduler_launch(uint32_t timeSlice){
	SysTick->LOAD = timeSlice - 1;							// reload value
	SysTick->CTRL = 0x7;												// enable, core clock and interrupt arm
  schedulerASM_start_os();                  	// start on the first task
}

/**
*	Handles Task ending
*
*	This function address is saved in the LR of every task, if the task does not have a endless loop it will load the LR and jump here.
* It sets the ready status of the task to false (will be ignored by the scheduler) and suspends the task.
*	@param none
*	@return none
*/
void Scheduler_Function_End(void){
	scheduler_destroy(task_getID());
	while(1){}
}

/**
*	Initializes the operating system
*
*	Disables interrupts until Scheduler_Launch is called.
* @details Adds the standard CPU usage task and all tasks from tasklist.h to the scheduler, activating the ones that have startOnLaunch set
*	@param 	none
*	@return none
*/
void scheduler_init(void){
  schedulerASM_disableInterrupts();

	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	
	NVIC_SetPriority(PendSV_IRQn, 0xFF);
	
	//Add startup task
	tcbs[0].next = &tcbs[0];
	tcbs[0].taskID = task_list[0].id;
	scheduler_setInitialStack(0);
	Stacks[0][STACKSIZE-2] = (int32_t)task_list[0].Task;			//Load function pointer into PC stack
	RunPt = &tcbs[0];																					//SetInitialStack current RunPt to current tcb task
	tcbs[0].priority = task_list[0].priority;
	totalThreadsRunning = 1;
	tcbs[0].running = true;
	tcbs[0].ready = true;
	
		//add all tasks to scheduler and active the ones that should start at os launch
	for(int i = 1; i < tasklist_getNumTasks();i++){
		scheduler_addTask(task_list[i].Task,task_list[i].priority,task_list[i].id);
		if(task_list[i].startOnLaunch){
			scheduler_create(task_list[i].id, 0);
		}
	}
}

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
int scheduler_addTask(void(*task)(uint32_t param), uint8_t priority, uint8_t taskID){ 
	for(int i = 0; i < NUMTHREADS; i++){
		if(tcbs[i].next == 0){
			tcbs[i].next = tcbs[i-1].next;
			tcbs[i-1].next = &tcbs[i];
			tcbs[i].taskID = taskID;
			tcbs[i].priority = priority;
			break;
		}
	}
	return 1;
}


/**
*	Sets the initial stack of a task
*
* Sets the values of all the registers saved in the stack. 
*	For debugging purposes, the Register number is stored in the relevant stack space at initialisation.
*	@details	Is called when a task is started
*	@param 	i Index of task in task_list to be started
*	@return none
*/
void scheduler_setInitialStack(int i){
  tcbs[i].sp = &Stacks[i][STACKSIZE-16]; // thread stack pointer
	Stacks[i][STACKSIZE-1] = 0x01000000;   // PSR has to be saved due to ISR
	Stacks[i][STACKSIZE-2] = 0x15151515;   // R15
  Stacks[i][STACKSIZE-3] = 0x14141414;   // R14
  Stacks[i][STACKSIZE-4] = 0x12121212;   // R12
  Stacks[i][STACKSIZE-5] = 0x03030303;   // R3
  Stacks[i][STACKSIZE-6] = 0x02020202;   // R2
  Stacks[i][STACKSIZE-7] = 0x01010101;   // R1
  Stacks[i][STACKSIZE-8] = 0x00000000;   // R0
  Stacks[i][STACKSIZE-9] = 0x11111111;   // R11
  Stacks[i][STACKSIZE-10] = 0x10101010;  // R10
  Stacks[i][STACKSIZE-11] = 0x09090909;  // R9
  Stacks[i][STACKSIZE-12] = 0x08080808;  // R8
  Stacks[i][STACKSIZE-13] = 0x07070707;  // R7
  Stacks[i][STACKSIZE-14] = 0x06060606;  // R6
  Stacks[i][STACKSIZE-15] = 0x05050505;  // R5
  Stacks[i][STACKSIZE-16] = 0x04040404;  // R4
}

/**
*	Starts a task
*
*	Resets the InitialStack, Sets the function pointer (LR) and param (R0).
*	@details Resetting the Initialstack is for the purpose of the same task having previously run, so the stack does not have any old states contained.
* @param taskID The ID of the task to start
* @param param The parameter (value/pointer) the function should be given
*	@return 1 for success
*/
int scheduler_create(uint8_t taskID, uint32_t param){
	schedulerASM_disableInterrupts();
	scheduler_setInitialStack(taskID);
	Stacks[taskID][STACKSIZE-2] = (int32_t)(task_list[taskID].Task);									//Sets PC so the method is called from schedule context change
	Stacks[taskID][STACKSIZE-8] = param;																							//R0 is the first parameter of a c function call
	Stacks[taskID][STACKSIZE-3] = (int32_t) &Scheduler_Function_End;									//Function pointer for end of function when task function exits stored in LR stack
	tcbs[taskID].running = false;
	tcbs[taskID].ready = true;
	totalThreadsRunning++;
	schedulerASM_enableInterrupts();
	return 1;
}

/**
*	Stops a task
*
*	Sets the running flad to false for the task.
*	@details Resetting the Initialstack is for the purpose of the same task having previously run, so the stack does not have any old states contained.
* @param taskID The ID of the task to stop
*	@return 1 success
*/
int scheduler_destroy(uint8_t taskID){
	schedulerASM_disableInterrupts();
	tcbs[taskID].running = false;
	tcbs[taskID].ready = false;
	totalThreadsRunning--;
	if(taskID == RunPt->taskID){
		schedulerASM_enableInterrupts();
		task_yield();
	}
	schedulerASM_enableInterrupts();
	return 1;
}

/**
*	Decrements sleeping tasks
*
* @details decrements the sleep counters of all currently sleeping tasks
*	@param 	none
* @return none
*/
void scheduler_decrement_sleeping_tasks(void){
		for(int i=0; i < NUMTHREADS; i++){
			if(tcbs[i].sleep){
				tcbs[i].sleep--;
			}
		}
}

/**
*	Triggers the PendSV interrupt
*
*	@param 	none
* @return none
*/
void SysTick_Handler(void){
		SCB->ICSR |= 0x10000000;						//trigger PendSV 
}

