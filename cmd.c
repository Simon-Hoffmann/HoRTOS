/**
*	@file 	cmd.c
*	@author Simon Hoffmann
*	@brief	Commands sent over UART are handled here
*/

#include "commands.h"
#include "cmd.h"
#include "string.h"

/* ------------  F U N C T I O N   D E F I N I T I O N ----------------- */

/* ---------------  B U I L T I N   C O M M A N D S -------------------- */


char *commands_str[] = {
  "suspend",
  "resume",
	"listpid",
	"cpu",
	"stop"
};	///<Contains all commands that can be called

//
int (*commands_func[]) (char*) = {
  &command_suspend,
  &command_resume,
	&command_listpid,
	&command_displayCPU,
	&command_suspendDisplayCPU,
	&command_none
};	///<Contains the function pointers for all callable commands

/* ----------------------  F U N C T I O N S --------------------------- */

/**
 * @brief returns number of commands
 *
 * @return int number of commands
 */
int cmd_number_commands(void) {
  return sizeof(commands_str) / sizeof(char *);
}


/**
 * @brief Executes commands for device
 *
 * @param args Command args
 * @return int Status code
 */
int cmd_execute(char *args){
  int i;

  for (i = 0; i < cmd_number_commands(); i++) {
      //check if command exists
      if (strcmp(args, commands_str[i]) == 0) {
          //return status code of function call
          return (*commands_func[i])(args);
      } 
  }
	return (*commands_func[5])(args);
  //return status code of programm launch
}
