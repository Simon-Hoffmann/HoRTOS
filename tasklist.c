/**
*	@file 	Tasklist.c
*	@author Simon Hoffmann
*	@brief	Contains all OS Tasks
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "tasklist.h"
#include "os_tasks.h"
#include "user_tasks.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

const Tasklist task_list[] = {
/* Task name/ID							Task function pointer				Task priority 0-255		Start on OS launch*/
	
	/*-------OS_Tasks - Don't Remove!---------*/
	{START_TSK,								start_task,									0,										true},		//start_task for initialisation and starting all other tasks (highest priority)
	{IDLE_TSK, 								idle_task, 									254,									true},		//should only run when nothing else is running (lowest priority)
	{SLEEP_TSK,								sleep_task,									0,										false},		//highest priority due to sleep times needing to be decremented on time
	
	/*-------				User Tasks			---------*/
	{LED_GROUP1_TSK,					led_group1_task,						5,									  false},		//Controls one side of the led board
	{LED_GROUP2_TSK,					led_group2_task,						5,										false},		//Controls the other side of the led board
	{UART_SEND_TSK,						uart_send_task,							5,										false},		//Handles all data that needs to be sent over UART
	{UART_RECEIVE_TSK,				uart_receive_task,					5,										false}		//Handles all data that needs to be received over UART
}; ///<List of all tasks that will be run by the OS


/**
*	Gets number of tasks
*
* Returns the amount of tasks in tasklist
*	@param none
* @return number of tasks
*/
uint8_t tasklist_getNumTasks(void){
	return (sizeof(task_list)/sizeof(Tasklist));
}
