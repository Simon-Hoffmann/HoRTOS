/**
*	@file 	handlers.h
*	@author Simon Hoffmann & Aleksei Svatko
*	@brief	Exception Handlers Interface
*/

#ifndef __HANDLERS_H
#define __HANDLERS_H

/*-------------------------- I N C L U D E S ----------------------------*/

/*---------------------------- M A C R O S ------------------------------*/

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Hardfault Handler
*
* Could maybe restart process that caused hardfault or something along those lines?
*
*	@param 	none
*	@return none
*/
void HardFault_Handler(void);

#endif
