/**
 ****************************************************************************
 * @file    : shellUtils.c
 * @brief   : Utilities used on the shell logic.
 * @author  : Eldorado Research Institute
 ****************************************************************************
 */

/****************************************************************************
 * Include Files
 ****************************************************************************/
#include <string.h>
#include "shellUtils.h"
#include "../Commands/shellCommands.h"

#ifdef TARGET_MCU
#include <Types.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

/****************************************************************************
 * Private Definitions
 ****************************************************************************/
#define HISTORY_SIZE			(10)						/**< Number of entries to store on the history array. */
#define nextElement(element)	((element+1)%HISTORY_SIZE)	/**< Next element index of the history array. */

/****************************************************************************
 * Private Variables
 ****************************************************************************/
static char mHistory[HISTORY_SIZE][20] = { 0 }; /**< Array used to implement a circular buffer for the history. */
static int8_t mTailHistory = 0; /**< Points to the next available spot on the history buffer. */
static int8_t mHeadHistory = 0; /**< Points to the first element on the history buffer. */
static int8_t mIndexHistory = 0; /**< Variable used to navigate on the history buffer. */

/* TODO: Create a structure to hold the command names and shortcuts.*/
char mCommands[SHELL_COMMANDS_NUM][10] = { "help", "info", "led", "version", "reset" };

/****************************************************************************
 * Public Source Code
 ****************************************************************************/
bool ShellUtils_autocomplete( char *str, uint16_t *size ) {
    /* Compare with the available commands */
    for (int i = 0; i < SHELL_COMMANDS_NUM; i++) {

        if (strcmp(str, mCommands[i]) == 0) { /* If the command is equal to the input return false */
            return false; /* Returns false, no need to update text */
        }
        if (ShellUtils_compare(str, mCommands[i]) == true) {
            strcpy(str, mCommands[i]);
            *size = strlen(mCommands[i]);
            return true; /* Partial match, update the text with the command found */
        }
    }
    return false;
}

bool ShellUtils_compare( char *str1, char *str2 ) {

    if (str1 == NULL || str2 == NULL) return false;

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

void ShellUtils_addHistory( char *cmd ) {

    if (cmd == NULL) return;

    /* Remove trailing space */
    uint8_t mLen = strlen(cmd);
    while (cmd[mLen - 1] == ' ') {
        cmd[mLen - 1] = '\0';
        mLen = strlen(cmd);
    }

    strcpy(mHistory[mTailHistory], cmd);
    mTailHistory = nextElement(mTailHistory); /* Circular buffer. */

    if (mTailHistory == mHeadHistory) { /* Buffer full, update the head. */
        mHeadHistory = nextElement(mTailHistory);
    }

    mIndexHistory = mTailHistory; /* Update the history index, pointing to the last command entered. */
}

bool ShellUtils_historyUp( char *str, uint16_t *size ) {

    if (str == NULL || size == NULL) {
        return false;
    }

    if (mIndexHistory == mHeadHistory) { /* Reached the beginning of the buffer, do nothing. */
        return false;
    }
    else {
        if ((mIndexHistory - 1) < 0) {
            if ((HISTORY_SIZE - 1) == mHeadHistory) { /* Reached the beginning of the buffer, do nothing. */
                return false;
            }
            mIndexHistory = HISTORY_SIZE - 1;
        }
        else {
            if ((mIndexHistory - 1) == mHeadHistory) { /* Reached the beginning of the buffer, do nothing. */
                return false;
            }
            mIndexHistory = mIndexHistory - 1;
        }

        strcpy(str, mHistory[mIndexHistory]);
        *size = strlen(mHistory[mIndexHistory]) + 1;
    }
    return true;
}

bool ShellUtils_historyDown( char *str, uint16_t *size ) {

    if (str == NULL || size == NULL) {
        return false;
    }

    if (mTailHistory == mHeadHistory) { // Empty buffer
        return false;
    }
    if (mIndexHistory == mTailHistory) { /* Reached the end of the buffer, do nothing. */
        return false;
    }
    else {
        if ((mIndexHistory + 1) >= HISTORY_SIZE) {
            if (mTailHistory == 0) { /* Reached the end of the buffer, do nothing. */
                return false;
            }
            mIndexHistory = 0;
        }
        else {
            if ((mIndexHistory + 1) == mTailHistory) { /* Reached the end of the buffer, do nothing. */
                return false;
            }
            mIndexHistory = mIndexHistory + 1;
        }

        strcpy(str, mHistory[mIndexHistory]);
        *size = strlen(mHistory[mIndexHistory]) + 1;
    }
    return true;
}
