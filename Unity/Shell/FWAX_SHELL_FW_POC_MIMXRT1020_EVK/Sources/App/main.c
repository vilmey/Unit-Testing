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
#include "shell.h"
#include "shellCommands.h"

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

	Shell_init(ShellCommands_callback); 	/* Initialization of the shell with the callback. */

	while (1) {
		Shell_getChar(GETCHAR());	/* Sending characters to the shell. */

	}
}

#endif
