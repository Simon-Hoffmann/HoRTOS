/**
*	@file 	user_tasks.h
*	@author Simon Hoffmann
*	@brief	User Task Interface
*/

#ifndef __USER_TASK_H_
#define __USER_TASK_H_

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>

/*---------------------------- M A C R O S ------------------------------*/

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Led group 1 pattern task
*
* @param param Task parameter in this case not used
* @return none
*/
void led_group1_task(uint32_t param);

/**
*	Led group 2 pattern task
*
* @param param Task parameter in this case not used
* @return none
*/
void led_group2_task(uint32_t param);

/**
*	Retreives any data that needs to be sent from the fifo and sends it over UART
*
* @param param Task parameter in this case not used
* @return none
*/
void uart_send_task(uint32_t param);

/**
*	Receives any data over UART, if nothing received sleeps for 50ms to not use to many system resources
*
*	@details If data is received it is added to the command buffer, when a carriage return is received, the command buffer is used to call cmd_execute
* @param param Task parameter in this case not used
* @return none
*/
void uart_receive_task(uint32_t param);

#endif
