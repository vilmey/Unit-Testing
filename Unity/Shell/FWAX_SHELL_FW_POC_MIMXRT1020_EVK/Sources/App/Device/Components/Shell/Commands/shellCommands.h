/**
 ****************************************************************************
 * @file    : shellCommands.h
 * @brief   : Commands and callbacks supported by the shell
 * @author  : Eldorado Research Institute
 ****************************************************************************
 */

#ifndef SHELL_COMMANDS_H
#define SHELL_COMMANDS_H

/****************************************************************************
 * Include Files
 ****************************************************************************/
#include "../middleware/shell.h"

/****************************************************************************
 * Public Definitions
 ****************************************************************************/
#define SHELL_COMMANDS_NUM      ( 5 ) /**< Number of available commands. */

/****************************************************************************
 * Public Functions
 ****************************************************************************/
/**
 * Function that does the treatment of the commands
 * @param cmd command received.
 * @param argc number of arguments received.
 * @param argv pointer of pointer to the arguments received.
 */
void ShellCommands_callback( uint8_t *cmd, uint16_t argc, uint8_t **argv );

/* Prototype of the commands structure */

typedef void (*callback)( void );
typedef struct shellCommandType {
    char Command[30];
    char Shortcut[10];
    uint8_t Args;
    callback Function;
    char HelpText[300];
} ShellCommand;

//TshellCommand shellCommands[SHELL_COMMANDS_NUM];

/* End of prototype of the commands structure */

#endif /* SHELL_COMMANDS_H */

