/**
*	@file 	commands.c
*	@author Simon Hoffmann
*	@brief	Contains all functions for the callable commands
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "task.h"
#include "commands.h"
#include "tasklist.h"
#include "os_tasks.h"
#include "fifo.h"
#include <stdio.h>
#include <string.h>

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */
																														
/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
*	Fills the fifo with a given message buffer
*
* @param msg buffer to use for fifo
* @return none
*/
void fill_fifo(char *msg){
	int i = 0;
	do{
		fifo_put(msg[i]);
		i++;
	}while((msg[i] != '\0') && (msg[i] != 0x0D));
}
	
/**
*	Suspends a given task
*
* @param args contains the taskPID
* @return int status code
*/
int command_suspend(char *args){
	int index = 0;
	while(args[index] != ' '){
		index++;
	}
	index++;
	int processID = args[index] - '0';
	task_kill(processID);
	return 1;
}

/**
 * Resumes a given task
 *
 * @param args contains the taskPID
 * @return int status code
 */
int command_resume(char *args){
	int index = 0;
	while(args[index] != ' '){
		index++;
	}
	index++;
	int processID = args[index] - '0';
	
	task_create(processID, 0);
	return 1;
}

/**
 * Lists all tasks (not displaying correctly)
 *
 * @param args not used here
 * @return int status code
 */
int command_listpid(char *args){
	char msg[100];
	tcbType *pt;
	
	memset(msg, 0, 100);
	strcpy(msg, "pid   state");
	msg[11] = 0x0D;
	fill_fifo(msg);
	strcpy(msg, "-----------");
	msg[11] = 0x0D;
	memset(msg, 0, 100);
	pt = RunPt;
	while(pt->taskID != 0){
		pt = pt->next;
	}
	for(int i = 0; i < tasklist_getNumTasks(); i++){
		msg[0] = task_list[i].id;
		msg[1] = ' ';
		msg[2] = ' ';
		msg[3] = ' ';
		msg[4] = ' ';
		msg[5] = ' ';
		if(pt->blocked){
			msg[6] = 0;
			strcat(msg, " (Blocked)");
			msg[17] = 0x0D;
		} else if(pt->running){
			msg[6] = 1;
			strcat(msg, " (Running)");
			msg[17] = 0x0D;
		} else if(pt->ready){
			msg[6] = 2;
			strcat(msg, " (Ready)");
			msg[15] = 0x0D;
		} else if(pt->sleep){
			msg[6] = 3;
			strcat(msg, " (Sleeping)");
			msg[18] = 0x0D;
		}
		fill_fifo(msg);
		pt = pt->next;
		memset(msg, 0, 100);
	}
	return 1;
}

/**
 * Displays CPU usage
 *
 * @param args not used here
 * @return int status code
 */
int command_displayCPU(char *args){
	CPUSTATUS = true;
	return 1;
}

/**
 * Stops displaying CPU usage
 *
 * @param args not used here
 * @return int status code
 */
int command_suspendDisplayCPU(char *args){
	CPUSTATUS = false;
	return 1;
}

/**
 * Handles unknown commands
 *
 * @param args not used here
 * @return int status code
 */
int command_none(char *args){
	char msg[100];
	strcpy(msg, "Command ");
	strcat(msg, args);
	strcat(msg, " not recognised");
	fill_fifo(msg);
	return 1;
}


