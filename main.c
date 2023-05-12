/**
*	@file 	main.c
*	@author Simon Hoffmann
*	@brief	Main Task
*/

/* ---------------- G L O B A L   D E F I N I T I O N S ---------------- */

/*-------------------------- I N C L U D E S ----------------------------*/

#include "scheduler.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

#define TIMESLICE   TIME_2MS 							///<Timeslice for tasks

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */
#include "stm32g474xx.h"

	
/**
*	Main program called at program startup
*
*	@param 	none
*	@return none
*/
int main(void)
{
	scheduler_init();
	scheduler_launch(TIMESLICE);
	return 0;
}
