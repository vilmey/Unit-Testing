/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifdef TARGET_MCU

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "shell.h"
#include "shellCommands.h"

#endif  /* END TARGET_MCU*/

#ifdef TARGET_HOST

#include <stdio.h>
#include <stdlib.h>
#include "Device/Components/Shell/Middleware/shell.h"
#include "Device/Components/Shell/Commands/shellCommands.h"

#endif  /* END TARGET_HOST*/


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/**
 * @brief Main function
 */
int main(void) {


#ifdef TARGET_MCU

	/* Init board hardware. */
	BOARD_ConfigMPU();
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();
#endif /* END TARGET_MCU */

	SHELL_PRINTF("\033c");			/* Clean the terminal. */

	Shell_init(ShellCommands_callback); 	/* Initialization of the shell with the callback. */

	while (1) {
#ifdef TARGET_MCU
		Shell_getChar(GETCHAR());	/* Sending characters to the shell MCU. */
#else
        Shell_getChar(getc(stdin)); /* Sending characters to the shell HOST. */
#endif

	}
}
