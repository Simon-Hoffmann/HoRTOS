/**
*	@file 	Tasklist.h
*	@author Simon Hoffmann
*	@brief	Tasklist Interface
*/

#ifndef __TASKLIST_H_
#define __TASKLIST_H_

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*---------------------------- M A C R O S ------------------------------*/

#define NUMTHREADS  	20        ///<maximum number of threads

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

enum TaskID{
	START_TSK = 0,		///<Idle task
	IDLE_TSK,					///<Sleep task
	SLEEP_TSK,
	LED_GROUP1_TSK,		///<Led group 1 pattern task
	LED_GROUP2_TSK,		///<Led group 2 pattern task
	UART_SEND_TSK,
	UART_RECEIVE_TSK
}; ///<Contains all Task IDs

typedef struct{
	enum TaskID id;					///<Id of task
	void(*Task)(uint32_t);	///<Function pointer for task
	uint8_t priority;				///<Task priority
	bool startOnLaunch;			///<If task launches on OS start
}Tasklist;	///<Contains all tasks for the Scheduler

extern const Tasklist task_list[];

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Gets number of tasks
*	@param none
* @return number of tasks
*/
uint8_t tasklist_getNumTasks(void);

#endif
