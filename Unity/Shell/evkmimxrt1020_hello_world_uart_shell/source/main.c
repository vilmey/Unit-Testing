/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef UNIT_TESTING

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "../component/shell/commands/shellCommands.h"
#include "../component/shell/middleware/shell.h"

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
	char ch;

	/* Init board hardware. */
	BOARD_ConfigMPU();
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	PRINTF("\033c");			/* Clean the terminal. */
	shellInit(shellCallback); 	/* Initialization of the shell with the callback. */

	while (1) {
		shellGetc(GETCHAR());	/* Sending characters to the shell. */

	}
}

#endif
