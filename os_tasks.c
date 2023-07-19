/**
*	@file 	os_tasks.c
*	@author Simon Hoffmann
*	@brief	all os tasks are contained in this file
*					These have a fixed functionality that must not be changed
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>
#include "stm32g474xx.h"
#include "os_tasks.h"
#include "scheduler.h"
#include "task.h"
#include "tasklist.h"
#include "led.h"
#include "semaphore.h"
#include "delay.h"
#include "uart.h"
#include "fifo.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

Semaphore decrementSleepingTasks_Mutex;
static volatile uint32_t system_ms_gone_by = 0;
bool CPUSTATUS = 0;
																														
/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

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
*	Start task for Hardware initialization and task creation
*
* @param param Task parameter in this case not used
* @return none
*/
void start_task(uint32_t param){

	/*Start OS tasks*/
	task_create(SLEEP_TSK, 0);
	
	/*Start User tasks*/
	//task_create(LED_GROUP1_TSK, 0);
	//task_create(LED_GROUP2_TSK, 0);
	
	//task_create(UART_SEND_TSK, 0);
	//task_create(UART_RECEIVE_TSK, 0);
	
	/*Hardware initialization*/
	//led_init();
	//uart_init();
	fifo_init();
	
	
	task_kill(task_getID());
}

/**
*	Idle Task
*
* @details	Runs if no other task is currently running
*						Calculates current CPU usage
*	@param param Task parameter in this case not used
* @return none
*/
void idle_task(uint32_t param){
	uint8_t cpu_load = 0;
	uint32_t idle_ms_gone_by = 0;
	while(1){
		delayms(1);
		idle_ms_gone_by++;
		
		//if a second of system time has gone by
		if(system_ms_gone_by >= 1000){
			//load onto
			cpu_load = (uint8_t) (((double) idle_ms_gone_by / (double)system_ms_gone_by) * (double) 100);
			if(CPUSTATUS){
				uint8_t tens = cpu_load / 10;
				uint8_t ones = cpu_load % 10;
				fifo_put(tens + '0');
				fifo_put(ones + '0');
				fifo_put('%');
				fifo_put(0x0D);
			}
			schedulerASM_disableInterrupts();
			system_ms_gone_by = 0;
			schedulerASM_enableInterrupts();
			idle_ms_gone_by = 0;
		}
	}
}

/**
*	Sleep task
*
* @details decrements the sleep counters of all currently sleeping tasks
*	@param param Task parameter in this case not used
* @return none
*/
void sleep_task(uint32_t param){
	/*Enable timer 2 and nvic interrupt for 1ms interrupts to decrement sleeping tasks*/
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	TIM2->PSC = 0;										
	TIM2->ARR= TIME_1MS - 1;								
	TIM2->CNT=0;
	TIM2->DIER = TIM_DIER_UIE;
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),6,0));
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2->CR1 |= TIM_CR1_CEN;								//Start the Timer
	
	semaphore_init(&decrementSleepingTasks_Mutex, 0);
	while(1){
		//wait for timer to signal mutex
		semaphore_wait(&decrementSleepingTasks_Mutex);
		scheduler_decrement_sleeping_tasks();
	}
}

/**
*	Timer 2 interrupt handler
*
*	Signals semaphore for blocked task sleep_task to run
*	Increments system_ms_gone_by to indicate how many ms have gone by
* @param none
* @return none
*/
void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;
	semaphore_signal(&decrementSleepingTasks_Mutex);
	system_ms_gone_by++;
}
