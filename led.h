/**
*	@file 	led.h
*	@author Simon Hoffmann
*	@brief	LED Interface
*/

#ifndef __LED_H
#define __LED_H

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>

/*---------------------------- M A C R O S ------------------------------*/

/* ----------------------- F U N C T I O N S  -------------------------- */


/**
*	Initializes the GPIOA pins 0-7
*
* @details GPIOA pins 0-7 connected to external LED circuit board
*	@param 	none
*	@return none
*/
void led_init(void);

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
void led_group1_blink(void);

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
void led_group2_blink(void);

#endif

