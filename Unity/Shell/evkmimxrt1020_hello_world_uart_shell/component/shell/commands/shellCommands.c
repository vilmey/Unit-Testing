/**
 * @file    shellCommands.c
 * @version SHELL_FW_XXX_0.1.0
 * @brief   Menu and commands of the shell
 */

//==============================================================================
// INCLUDE FILES
//==============================================================================
#include "shellCommands.h"
#include <string.h>
#include <stdlib.h>

//==============================================================================
// PRIVATE DEFINITIONS
//==============================================================================

//==============================================================================
// PRIVATE TYPEDEFS
//==============================================================================

typedef struct {
	uint8_t wifi_name[20];
	uint8_t passwd[20];
	uint8_t host[50];
	uint16_t port;
} Rede_t;

typedef struct {
	uint8_t ledCount;
	uint8_t leds[4];
} Leds_t;

//==============================================================================
// PRIVATE VARIABLES
//==============================================================================

static Leds_t ledStatus;
static uint8_t registeredCommands = 0;

//==============================================================================
// PRIVATE FUNCTIONS
//==============================================================================

//==============================================================================
// SOURCE CODE
//==============================================================================
//void shellRegisterCommand(char *command, char *shortcut, uint8_t args, callback function, char *helpText)
//{
//    /*
//    char command[30];
//    char shortcut[10];
//    uint8_t args;
//    callback function;
//    char helpText[300];
//    */
//    strcpy(shellCommands[registeredCommands].command, command);
//
//
//    return;
//}

char *shellCommandsIndex[SHELL_COMMANDS_NUM] = { "help", "led", "info",
		"version", "reset" };

void shellCallback(uint8_t *cmd, uint16_t argc, uint8_t **argv) {
	int8_t err = 0;

	if (strcmp((const char*) "help", (const char*) cmd) == 0
			|| strcmp((const char*) "?", (const char*) cmd) == 0) {
		SHELL_PRINTF(SHELL_HELP"Supported commands:" CRLF);

		SHELL_PRINTF(SHELL_HELP"help    (?)   List available commands." CRLF);

		SHELL_PRINTF(SHELL_HELP"led     (l)   Set LED state." CRLF);
		SHELL_PRINTF(
				SHELL_HELP"       <id> = 1: Status LED | 2: Error LED." CRLF);
		SHELL_PRINTF(
				SHELL_HELP"       <state> = on | off | bl1 : 2x per second.| bl2 : 4x per second." CRLF);

		SHELL_PRINTF(
				SHELL_HELP"info    (i)   Display device info and firmware version." CRLF);

		SHELL_PRINTF(
				SHELL_HELP"version (v)   Display firmware version and hardware version." CRLF);

		SHELL_PRINTF(SHELL_HELP"reset   (rst) Reboot device." CRLF);

		err = 0;
	} else if (strcmp((const char*) "led", (const char*) cmd) == 0
			|| strcmp((const char*) "l", (const char*) cmd) == 0) {
		if (argc == 0) {
			/* print status */
			SHELL_PRINTF("======== LEDS ========" CRLF);
			SHELL_PRINTF("Led Status: %s" CRLF,
					ledStatus.leds[0] == 0 ?
							"OFF" :
							(ledStatus.leds[0] == 1 ? "ON" : "BLINKING"));
			SHELL_PRINTF("Led Error: %s" CRLF,
					ledStatus.leds[1] == 0 ?
							"OFF" :
							(ledStatus.leds[1] == 1 ? "ON" : "BLINKING"));
			SHELL_PRINTF("Backlight Keyboard: %s" CRLF,
					ledStatus.leds[2] == 0 ?
							"OFF" :
							(ledStatus.leds[2] == 1 ? "ON" : "BLINKING"));
			SHELL_PRINTF("Backlight Screen: %s" CRLF,
					ledStatus.leds[3] == 0 ?
							"OFF" :
							(ledStatus.leds[3] == 1 ? "ON" : "BLINKING"));
		}

		if (argc == 1) {
			if (strcmp((const char*) "?", (const char*) argv[0]) == 0) {
				/* print help*/
				SHELL_PRINTF(SHELL_HELP"led     (l)   Set LED state." CRLF);
				SHELL_PRINTF(
						SHELL_HELP"       <id> = 1: Status LED | 2: Error LED." CRLF);
				SHELL_PRINTF(
						SHELL_HELP"       <state> = on | off | bl1 : 2x per second.| bl2 : 4x per second." CRLF);
			} else
				err++;
		}
		if (argc == 2) {
			/* change led state*/
			uint8_t led = (uint8_t) strtol((const char*) argv[0], NULL, 10);
			uint8_t state = (uint8_t) strtol((const char*) argv[1], NULL, 10);

			if (strcmp("off", argv[1]) == 0)
				state = 0;

			if (strcmp("on", argv[1]) == 0)
				state = 1;

			if (strcmp("bl1", argv[1]) == 0)
				state = 2;

			if (strcmp("bl2", argv[1]) == 0)
				state = 3;

			if (led >= 0 && led < 4) {
				if (state >= 0 && state < 4) {
					ledStatus.leds[led] = state;
					SHELL_PRINTF(SHELL_PROMPT "OK");
				} else
					err++;
			} else
				err++;
		}
	} else if (strcmp((const char*) "info", (const char*) cmd) == 0
			|| strcmp((const char*) "i", (const char*) cmd) == 0) {
		if (argc == 0) {
			SHELL_PRINTF("======== INFO ========" CRLF);
			SHELL_PRINTF("HW version: %s" CRLF, SHELL_HW_VERSION);
			SHELL_PRINTF("FW version: %s" CRLF, SHELL_VERSION);
			SHELL_PRINTF("Led Status: %s" CRLF,
					ledStatus.leds[0] == 0 ?
							"OFF" :
							(ledStatus.leds[0] == 1 ? "ON" : "BLINKING"));
			SHELL_PRINTF("Led Error: %s" CRLF,
					ledStatus.leds[1] == 0 ?
							"OFF" :
							(ledStatus.leds[1] == 1 ? "ON" : "BLINKING"));
			SHELL_PRINTF("Backlight Keyboard: %s" CRLF,
					ledStatus.leds[2] == 0 ?
							"OFF" :
							(ledStatus.leds[2] == 1 ? "ON" : "BLINKING"));
			SHELL_PRINTF("Backlight Screen: %s" CRLF,
					ledStatus.leds[3] == 0 ?
							"OFF" :
							(ledStatus.leds[3] == 1 ? "ON" : "BLINKING"));
		} else if (argc == 1) {
			if (strcmp((const char*) "?", (const char*) argv[0]) == 0) {
				SHELL_PRINTF(
						SHELL_HELP"info    (i)   Display device info and firmware version." CRLF);
			} else
				err++;
		}
	} else if (strcmp((const char*) "version", (const char*) cmd) == 0
			|| strcmp((const char*) "v", (const char*) cmd) == 0) {
		if (argc == 0) {
			SHELL_PRINTF("======== INFO ========" CRLF);
			SHELL_PRINTF("HW version: %s" CRLF, SHELL_HW_VERSION);
			SHELL_PRINTF("FW version: %s" CRLF, SHELL_VERSION);
		} else if (argc == 1) {
			if (strcmp((const char*) "?", (const char*) argv[0]) == 0) {
				SHELL_PRINTF(
						SHELL_HELP"version (v)   Display firmware version and hardware version." CRLF);
			} else
				err++;
		}
	} else if (strcmp((const char*) "reset", (const char*) cmd) == 0
			|| strcmp((const char*) "rst", (const char*) cmd) == 0) {
		if (argc == 0) {
			SHELL_PRINTF("======== RESET ========" CRLF);
		} else if (argc == 1) {
			if (strcmp((const char*) "?", (const char*) argv[0]) == 0) {
				SHELL_PRINTF(SHELL_HELP"reset   (rst) Reboot device." CRLF);
			} else
				err++;
		}
	} else {
		SHELL_PRINTF(SHELL_ERROR "Command not found" CRLF);
	}

	if (err != 0) {
		SHELL_PRINTF(SHELL_ERROR "Sintax error" CRLF);
	}
}

