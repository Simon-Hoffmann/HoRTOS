/**
*	@file 	main.c
*	@author Simon Hoffmann & Aleksei Svatko
*	@brief	Exception Handlers
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "handlers.h"
#include "stm32g4xx.h"
#include <stdio.h>
#include <stdbool.h>

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

static volatile	bool _HARDFAULT;

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Hardfault Handler
*
* Could maybe restart process that caused hardfault or something along those lines?
*
*	@param 	none
*	@return none
*/
void HardFault_Handler(void){
	_HARDFAULT = true;
	while(_HARDFAULT);
}

