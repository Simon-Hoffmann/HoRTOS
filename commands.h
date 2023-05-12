/**
*	@file 	commands.h
*	@author Simon Hoffmann
*	@brief	commands interface
*/

#ifndef __COMMANDS_TASK_H_
#define __COMMANDS_TASK_H_

/*-------------------------- I N C L U D E S ----------------------------*/

/*---------------------------- M A C R O S ------------------------------*/

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Suspends a given task
*
* @param args contains the taskPID
* @return int status code
*/
int command_suspend(char *args);

/**
 * Resumes a given task
 *
 * @param args contains the taskPID
 * @return int status code
 */
int command_resume(char *args);

/**
 * Lists all tasks (not displaying correctly)
 *
 * @param args not used here
 * @return int status code
 */
int command_listpid(char *args);

/**
 * Displays CPU usage
 *
 * @param args not used here
 * @return int status code
 */
int command_displayCPU(char *args);

/**
 * Stops displaying CPU usage
 *
 * @param args not used here
 * @return int status code
 */
int command_suspendDisplayCPU(char *args);

/**
 * Handles unknown commands
 *
 * @param args not used here
 * @return int status code
 */
int command_none(char *args);

#endif
