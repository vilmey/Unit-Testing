/**
 ****************************************************************************
 * @file    : shell.h
 * @brief   : Logic of the Shell component
 * @author  : Eldorado Research Institute
 ****************************************************************************
 */

#ifndef SHELL_H
#define SHELL_H

/****************************************************************************
 * Include Files
 ****************************************************************************/
#ifdef TARGET_MCU
#include "fsl_debug_console.h"

#else
#include <stdint.h>
#include <stdio.h>
#endif

/****************************************************************************
 * Public Definitions
 ****************************************************************************/
#define SHELL_WELCOME_MESSAGE "Welcome to shell"
#define SHELL_VERSION   "SHELL_FW_V0.1.0"
#define SHELL_HW_VERSION "NOT DEFINED"
#define SHELL_PROMPT    "> "
#define SHELL_ERROR     "X "
#define SHELL_STATUS    "? "
#define SHELL_HELP      "| "
#define CRLF            "\r\n"
#ifdef TARGET_MCU
#define SHELL_PRINTF(fmt, ...)      PRINTF(fmt, ##__VA_ARGS__);
#else
#define SHELL_PRINTF(fmt, ...)      printf(fmt, ##__VA_ARGS__);
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/
typedef void (*shellCallbackPtr)( uint8_t *cmd, uint16_t argc, uint8_t **argv ); // Callback type

/****************************************************************************
 * Public Functions
 ****************************************************************************/
/**
 * Function to initialize the shell and register the callback
 * @param callback function to treat the commands received.
 */
uint8_t Shell_init( shellCallbackPtr callback );

/**
 * Function to receive one byte
 * @param c byte received.
 */
void Shell_getChar( uint8_t c );

#endif /* SHELL_H */
