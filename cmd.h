/**
*	@file 	cmd.h
*	@author Simon Hoffmann
*	@brief	cmd interface
*/

#ifndef __CMD_TASK_H_
#define __CMD_TASK_H_

/*-------------------------- I N C L U D E S ----------------------------*/

/*---------------------------- M A C R O S ------------------------------*/

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
 * @brief Executes commands for device
 *
 * @param args Command args
 * @return int Status code
 */
int cmd_execute(char *args);

#endif
