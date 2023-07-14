/**
*	@file 	user_tasks.c
*	@author Simon Hoffmann
*	@brief	all user tasks are contained in this file
*					the user can implement these as he wishes
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "user_tasks.h"
#include <string.h>
#include "led.h"
#include "uart.h"
#include "fifo.h"
#include "task.h"
#include "cmd.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */
																														
/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Led group 1 pattern task
*
* @param param Task parameter in this case not used
* @return none
*/
void led_group1_task(uint32_t param){
	while(1){
		led_group1_blink();
		task_sleep(500);
	}
}

/**
*	Led group 2 pattern task
*
* @param param Task parameter in this case not used
* @return none
*/
void led_group2_task(uint32_t param){
	while(1){
		led_group2_blink();
		task_sleep(500);
	}
}

/**
*	Retreives any data that needs to be sent from the fifo and sends it over UART
*
* @param param Task parameter in this case not used
* @return none
*/
void uart_send_task(uint32_t param){
	while(1){
		uint8_t data;
		data = fifo_get();
		UART_SendChar(data);
	}
}

/**
*	Receives any data over UART, if nothing received sleeps for 50ms to not use to many system resources
*
*	@details If data is received it is added to the command buffer, when a carriage return is received, the command buffer is used to call cmd_execute
* @param param Task parameter in this case not used
* @return none
*/
void uart_receive_task(uint32_t param){
	char command[50];
	uint8_t index = 0;
	fifo_put('>');
	uint8_t data;
	
	while(1){
		
		data = UART_ReceiveChar();
		if(data == 0){
			task_sleep(50);
			continue;
		}
		fifo_put(data);	
		
		if(data == 0x0D){	//carriage return
			cmd_execute(command);
			index = 0;
			memset(command, 0, 50);					//reset command
			fifo_put('>');
		} else{
			command[index++] = data;
		}
	}
}
