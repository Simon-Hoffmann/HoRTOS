/**
*	@file 	os_task.h
*	@author Simon Hoffmann
*	@brief	Os Task Interface
*/

#ifndef __OS_TASK_H_
#define __OS_TASK_H_

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*---------------------------- M A C R O S ------------------------------*/

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */
extern bool CPUSTATUS;

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Start task for Hardware initialization and task creation
*
* @param param Task parameter in this case not used
* @return none
*/
void start_task(uint32_t param);

/**
*	Idle Task
*
*	@param param Task parameter in this case not used
* @return none
*/
void idle_task(uint32_t param);

/**
*	Sleep task
*
* @details decrements the sleep counters of all currently sleeping tasks
*	@param param Task parameter in this case not used
* @return none
*/
void sleep_task(uint32_t param);


#endif
