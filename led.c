/**
*	@file 	led.c
*	@author Simon Hoffmann
*	@brief	LED hardware controll
*
* Hardware control for initialising and controlling external LED circuit board
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "led.h"
#include <stdbool.h>
#include "stm32g474xx.h"
#include "delay.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */
																														
/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Initializes the GPIOA pins 0-7
*
* @details GPIOA pins 0-7 connected to external LED circuit board
*	@param 	none
*	@return none
*/
void led_init(void){
	  RCC->AHB2ENR |= 1;						// enable clock for port A
    GPIOA->MODER &= 0xFFFF0000;		// Mask pins 0-7
	  GPIOA->MODER |= 0x00005555;		// Set pins to 1 -> general output mode
}

/**
*	Sets the LEDs on GPIO 0-3 in a running light manner
*
*	Following behaviour (X - on, O - Off):	
*	GPIOA:	3		2		1		0
*					O		O		O		X
*					O		O		X		O
*					O		X		O		O
*					X		O		O		O
*					O		X		O		O
*					O		O		X		O
*					O		O		O		X
*
* @details Runs from one side to the other in a repeated manner
*	@param 	none
*	@return none
*/
void led_group1_blink(void){
	static uint8_t ledPosition = 0x1;
	static bool left = true;													//LED "travel" direction
	
	GPIOA->ODR = (GPIOA->ODR & 0xF0) | ledPosition;		//Sets current GPIO to on, and masks other groups GPIOs
	
	//Changes direction when GPIO on either end is set
	if(ledPosition == 0x8){
	 left = false;
	} else if(ledPosition == 0x1){
		left = true;
	}
	
	//Shifts ledPosition according to "travel" direction
	if(left){
			ledPosition <<= 1;
	}else{
		ledPosition >>= 1;
	}
}

/**
*	Sets the LEDs on GPIO 4-7 in a running light manner
*
*	Following behaviour (X - on, O - Off):	
*	GPIOA:	7		6		5		4
*					X		O		O		O
*					O		X		O		O
*					O		O		X		O
*					O		O		O		X
*					O		O		X		O
*					O		X		O		O
*					X		O		O		O
*
* @details Runs from one side to the other in a repeated manner
*	@param 	none
*	@return none
*/
void led_group2_blink(void){
	static uint8_t speedCount = 0;										//allows running slower than group1
	static uint8_t ledPosition = 0x80;
	static bool right = true;													//LED "travel" direction
	
	if(speedCount == 2){
		speedCount = 0;

		GPIOA->ODR =  (GPIOA->ODR & 0xF) | ledPosition;	//Sets current GPIO to on, and masks other groups GPIOs

		//Changes direction when GPIO on either end is set
		if(ledPosition == 0x80){
			right = true;
		} else if(ledPosition == 0x10){
			right = false;
		}
		
		//Shifts ledPosition according to "travel" direction
		if(right){
				ledPosition >>= 1;
		}else{
			ledPosition <<= 1;
		}
	}
	speedCount++;
}
