/**
 * @file    shellCommands.c
 * @version SHELL_FW_XXX_0.1.0
 * @brief   Menu and commands of the shell
 */

#ifndef _SHELL_COMMANDS_H_
#define _SHELL_COMMANDS_H_

//==============================================================================
// INCLUDE FILES
//==============================================================================

#include "../middleware/shell.h"

//==============================================================================
// INCLUDE FILES
//==============================================================================

#define SHELL_COMMANDS_NUM      5 // Number of available commands

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

/**
 * Function that does the treatment of the commands
 * @param cmd command received.
 * @param argc number of arguments received.
 * @param argv pointer of pointer to the arguments received.
 */
void shellCallback(uint8_t *cmd, uint16_t argc, uint8_t **argv);

/* Prototype of the commands structure */

typedef void (*callback)(void);
typedef struct shellCommand {
	char command[30];
	char shortcut[10];
	uint8_t args;
	callback function;
	char helpText[300];
} TshellCommand;

//TshellCommand shellCommands[SHELL_COMMANDS_NUM];

/* End of prototype of the commands structure */

#endif /* _SHELL_COMMANDS_H_ */

