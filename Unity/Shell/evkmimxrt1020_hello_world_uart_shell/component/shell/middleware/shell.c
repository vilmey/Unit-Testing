/**
 * @file    shell.c
 * @version SHELL_FW_XXX_0.1.0
 * @brief   Shell library
 */

//==============================================================================
// INCLUDE FILES
//==============================================================================

#ifndef TEST
#include "fsl_debug_console.h"	//TODO: move the hardware dependencies to shellSetup.c
#include "../types.h"
#endif

#include "shell.h"
#include "../commands/shellCommands.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//==============================================================================
// PRIVATE DEFINITIONS
//==============================================================================

/** Size of internal buffer */
#define SHELL_BUFFER_SIZE		(1024)						/**< Maximum length of a command. */
#define HISTORY_SIZE			(10)						/**< Number of entries to store on the history array. */
#define nextElement(element)	((element+1)%HISTORY_SIZE)	/**< Next element index of the history array. */

//==============================================================================
// PRIVATE VARIABLES
//==============================================================================

static uint16_t read_ptr = 0; /**< Number of characters on a command line. */
static uint8_t shell_buffer[SHELL_BUFFER_SIZE] = { 0 }; /**< Array that stores the command line. */
static char history[HISTORY_SIZE][20] = { 0 }; /**< Array used to implement a circular buffer for the historic. */
static uint8_t tailHistory = 0; /**< Points to the next available spot on the history buffer. */
static uint8_t headHistory = 0; /**< Points to the first element on the history buffer. */
static uint8_t indexHistory = 0; /**< Variable used to navigate on the history buffer. */

bool isCommandReady = false;

shellCallbackPtr callbackFunction;

//==============================================================================
// PRIVATE FUNCTIONS
//==============================================================================

/**
 * Function to compare two pieces of strings.
 * @param str1 first string.
 * @param str2 second string.
 */
bool ShellCompare(char *str1, char *str2);

/**
 * Function to auto complete the commands.
 * @param str [in, out] string displayed on the terminal. Completed string will the stored here.
 * @param size [in,out] size of the string. Size of the completed string will be stored here.
 */
bool ShellAutoComplete(char *str, uint16_t *size);

/**
 * Function to save commands to the history.
 * @param cmd command string to be stored.
 */
void ShellAddHistory(char *cmd);

/**
 * Retrieves the previous command on the history.
 * @param str [in, out] string displayed on the terminal. String from history will the stored here.
 * @param size [in,out] size of the string. Size of the string from history will be stored here.
 */
bool ShellHistoryUp(char *str, uint16_t *size);

/**
 * Retrieves the next command on the history list.
 * @param str [in, out] string displayed on the terminal. String from history will the stored here.
 * @param size [in,out] size of the string. Size of the string from history will be stored here.
 */
bool ShellHistoryDown(char *str, uint16_t *size);

/**
 * Function to check if receive a valid command
 */
static void ShellCheckMessage(void);

/**
 * Function to parse the command received.
 * @param cmd String received.
 * @param size Number of bytes received.
 */
static void ShellParser(uint8_t *cmd, uint16_t size);

//==============================================================================
// PRIVATE SOURCE CODE
//==============================================================================

static void ShellCheckMessage(void) {
	/* Is the command line ready ? */
	if (!isCommandReady)
		return;

	/* command arrived, has other characters? */
	if (read_ptr != 0) {
		ShellParser(&shell_buffer[0], read_ptr);
	}

	/* reset the buffer command */
	memset(&shell_buffer, 0, sizeof(shell_buffer));
	read_ptr = 0;
}

static void ShellParser(uint8_t *cmd, uint16_t size) {
	uint16_t cmd_ptr = 0;
	uint16_t arg_ptr = 0;
	uint16_t cmd_size = 0;
	uint8_t command_buffer[SHELL_BUFFER_SIZE];

	uint16_t argc = 0;
	uint8_t *argv[16];

	/* copy to the root command */
	memset(&command_buffer, 0, sizeof(command_buffer));

	/* add command to the history */
	ShellAddHistory(shell_buffer);

	/* find the root command terminator (space) */
	while (cmd_ptr < size) {
		if (cmd[cmd_ptr] == ' ')
			break;
		cmd_ptr++;
	}
	cmd_size = size - cmd_ptr;

	/* extract command arguments */
	strncpy((char*) &command_buffer[0], (const char*) &cmd[cmd_ptr + 1],
			(size - cmd_ptr));

	/* terminates the root command */
	cmd[cmd_ptr] = 0;
	arg_ptr = 0;

	/* extract the further arguments */
	while (arg_ptr < (cmd_size)) {
		argc++;
		*(argv + (argc - 1)) = &command_buffer[arg_ptr];

		/* find terminator */
		while (command_buffer[arg_ptr] != ' ' && (arg_ptr < 1023)) {
			arg_ptr++;
		}

		/* adds to argument list */
		command_buffer[arg_ptr] = 0;
		arg_ptr++;

	}

	/* finds and execute the command table */
	callbackFunction(cmd, argc, argv);
}

//==============================================================================
// PUBLIC SOURCE CODE
//==============================================================================

uint8_t shellInit(shellCallbackPtr callback) {

	if(callback == NULL)
		return 1;

	callbackFunction = callback;
	SHELL_PRINTF(SHELL_STATUS "%s version: %s"CRLF, SHELL_WELCOME_MESSAGE,
			SHELL_VERSION);
	SHELL_PRINTF(SHELL_STATUS "Type <help> to show all the commands"CRLF);
	SHELL_PRINTF(SHELL_PROMPT);

	return 0;
}

typedef enum getCharState {
	singleKey = 0, escapeKey, bracketKey,
} TgetCharState;

void shellGetc(uint8_t c) {
	uint16_t temp;
	static TgetCharState state = singleKey;

	switch (state)	/* Detects if it is a single key or a key chord. */
	{
	case singleKey:		/* Single key. */
		switch (c) {
		case '\r':    	/* Carriage Return. */
		case '\n':    	/* New line. */
			isCommandReady = true;
			SHELL_PRINTF(CRLF);
			ShellCheckMessage();
			SHELL_PRINTF(CRLF SHELL_PROMPT);
			indexHistory = tailHistory;	/* Update the history index, pointing to the last command entered. */
			break;

		case 0x7F:		/* Delete. */
		case 0x08: 		/* Backspace. */
			if (read_ptr > 0) {
				read_ptr--;
				SHELL_PRINTF("\b \b");	/* Erase the character from the terminal. */
			}
			if (read_ptr < 0) {
				read_ptr = SHELL_BUFFER_SIZE;
			}
			shell_buffer[read_ptr] = ' ';
			break;

		case 0x09:		/* Tab. */
			temp = read_ptr;
			if (ShellAutoComplete((char*) shell_buffer, &read_ptr)) {	/* Handle the auto completion. */
				while (temp > 0) {
					SHELL_PRINTF("\b \b");
					temp--;
				}
				SHELL_PRINTF("%s ", shell_buffer);
			}
			break;
		case 0x1B:  /* ESC - Escape key and beginning of a chord of keys. */
			state = escapeKey;
			break;

		default:
			/* store the incoming character on command circular buffer. */
			shell_buffer[read_ptr] = c;
			read_ptr = (read_ptr + 1) % SHELL_BUFFER_SIZE;
			SHELL_PRINTF("%c", c);
			break;
		}
		break;

	case escapeKey:
		if (c == '[') {
			state = bracketKey;
		} else {
			state = singleKey;
		}
		break;

	case bracketKey:			/* ESC + '[' */
		state = singleKey;
		if (c == 'A')			/* Arrow UP  = ESC + '[' + 'A' */
				{
			temp = read_ptr;
			if (ShellHistoryUp((char*) shell_buffer, &read_ptr)) {
				while (temp > 0) {
					SHELL_PRINTF("\b \b");
					temp--;
				}
				SHELL_PRINTF("%s ", shell_buffer);
			}
		} else if (c == 'B')	/* Arrow DOWN  = ESC + '[' + 'B' */
				{
			temp = read_ptr;
			if (ShellHistoryDown((char*) shell_buffer, &read_ptr)) {
				while (temp > 0) {
					SHELL_PRINTF("\b \b");
					temp--;
				}
				SHELL_PRINTF("%s ", shell_buffer);
			}
		}
		break;
	}
}

bool ShellCompare(char *str1, char *str2) {

	uint8_t strsize1 = strlen(str1);
	uint8_t strsize2 = strlen(str2);
	uint8_t lenght = (strsize1 < strsize2) ? strsize1 : strsize2; /* Get the smaller size. */

	for (int i = 0; i < lenght; i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}

	return true;
}

/* TODO: Create a structure to hold the command names and shortcuts.*/
char commands[SHELL_COMMANDS_NUM][10] = { "help", "info", "led", "version",
		"reset" };

bool ShellAutoComplete(char *str, uint16_t *size) {
	/* Compare with the available commands */
	for (int i = 0; i < SHELL_COMMANDS_NUM; i++) {

		if (ShellCompare(str, commands[i]) == true) {
//            SHELL_PRINTF("Comando %s\n", commands[i]);
			strcpy(str, commands[i]);
			*size = sizeof(commands[i]);
			return true;
		}
	}
	return false;
}

void ShellAddHistory(char *cmd) {
	strcpy(history[tailHistory], cmd);
	tailHistory = nextElement(tailHistory);	/* Circular buffer. */

	if (tailHistory == headHistory) {
		headHistory = nextElement(tailHistory);
	}
}

bool ShellHistoryUp(char *str, uint16_t *size) {

	if (indexHistory == headHistory) { /* Reached the beginning of the buffer, do nothing. */
		return false;
	} else {
		if ((indexHistory - 1) < 0)
			indexHistory = HISTORY_SIZE - 1;
		else
			indexHistory = indexHistory - 1;

		strcpy(str, history[indexHistory]);
		*size = strlen(history[indexHistory]) + 1;
	}
	return true;
}

bool ShellHistoryDown(char *str, uint16_t *size) {

	if (indexHistory == (tailHistory - 1)) { /* Reached the end of the buffer, do nothing. */
		return false;
	} else {
		if ((indexHistory + 1) >= HISTORY_SIZE)
			indexHistory = 0;
		else
			indexHistory = indexHistory + 1;

		strcpy(str, history[indexHistory]);
		*size = strlen(history[indexHistory]) + 1;
	}
	return true;
}
