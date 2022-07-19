/**
 * @file    shell.h
 * @version SHELL_FW_XXX_0.1.0
 * @brief   Shell library
 */

#ifndef _SHELL_H
#define _SHELL_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// INCLUDE FILES
//==============================================================================

// #include "setup_hw.h"
#include <stdint.h>
#ifdef TEST
#include <stdio.h>
#else
#include "fsl_debug_console.h"
#endif
//==============================================================================
// PUBLIC DEFINITIONS
//==============================================================================
#define SHELL_WELCOME_MESSAGE "Welcome to shell"
#define SHELL_VERSION   "SHELL_FW_V0.1.0"
#define SHELL_HW_VERSION "NOT DEFINED"
#define SHELL_PROMPT    "> "
#define SHELL_ERROR     "X "
#define SHELL_STATUS    "? "
#define SHELL_HELP      "| "
#define CRLF            "\r\n"
#ifndef TEST
#define SHELL_PRINTF(fmt, ...)      PRINTF(fmt, ##__VA_ARGS__);
#else
#define SHELL_PRINTF(fmt, ...)      printf(fmt, ##__VA_ARGS__);
#endif
//==============================================================================
// PUBLIC TYPEDEFS
//==============================================================================

typedef void (*shellCallbackPtr)(uint8_t *cmd, uint16_t argc, uint8_t **argv); // Callback type

//==============================================================================
// PUBLIC VARIABLES
//==============================================================================

//==============================================================================
// PUBLIC FUNCTIONS
//==============================================================================

/**
 * Function to initialize the shell and register the callback
 * @param callback function to treat the commands received.
 */
uint8_t shellInit(shellCallbackPtr callback);

/**
 * Function to receive one byte
 * @param c byte received.
 */
void shellGetc(uint8_t c);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* _SHELL_H */
