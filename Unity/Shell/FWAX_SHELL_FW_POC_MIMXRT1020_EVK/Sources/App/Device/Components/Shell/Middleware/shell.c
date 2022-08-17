/**
 ****************************************************************************
 * @file	: shell.c
 * @brief	: Logic of the Shell component
 * @author	: Eldorado Research Institute
 ****************************************************************************
 */

/****************************************************************************
 * Include Files
 ****************************************************************************/

#ifdef TARGET_MCU
#include "fsl_debug_console.h"	//TODO: move the hardware dependencies to shellSetup.c
#include <Types.h>
#else
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#include "shell.h"
#include "../Commands/shellCommands.h"
#include "../Utils/shellUtils.h"
#include <string.h>

/****************************************************************************
 * Private Definitions
 ****************************************************************************/
#define SHELL_BUFFER_SIZE		(1024)						/**< Maximum length of a command. */
#define nextElement(element)	((element+1)%HISTORY_SIZE)	/**< Next element index of the history array. */

/****************************************************************************
 * Private Variables
 ****************************************************************************/
static uint16_t mReadPtr = 0; /**< Number of characters on a command line. */
static uint8_t mShellBuffer[SHELL_BUFFER_SIZE] = { 0 }; /**< Array that stores the command line. */
static bool mIsCommandReady = false; /**< Assert if command is complete. */
static shellCallbackPtr mCallbackFunction; /**< Handler of the commands. */

/****************************************************************************
 * Private Functions
 ****************************************************************************/
/**
 * Function to check if receive a valid command
 */
static void checkMessage( void );

/**
 * Function to parse the command received.
 * @param cmd String received.
 * @param size Number of bytes received.
 */
static void commandParser( uint8_t *cmd, uint16_t size );

/****************************************************************************
 * Private Source Code
 ****************************************************************************/
static void checkMessage( void ) {
    /* Is the command line ready ? */
    if (!mIsCommandReady) return;

    /* command arrived, has other characters? */
    if (mReadPtr != 0) {
        commandParser(&mShellBuffer[0], mReadPtr);
    }

    /* reset the buffer command */
    memset(&mShellBuffer, 0, sizeof(mShellBuffer));
    mReadPtr = 0;
}

static void commandParser( uint8_t *cmd, uint16_t size ) {
    uint16_t mCommandPtr = 0;
    uint16_t mArgPtr = 0;
    uint16_t mCommandSize = 0;
    uint8_t mCommandBuffer[SHELL_BUFFER_SIZE];

    uint16_t mArgc = 0;
    uint8_t *mArgv[16];

    /* copy to the root command */
    memset(&mCommandBuffer, 0, sizeof(mCommandBuffer));

    /* add command to the history */
    ShellUtils_addHistory((char*)mShellBuffer);

    /* find the root command terminator (space) */
    while (mCommandPtr < size) {
        if (cmd[mCommandPtr] == ' ') break;
        mCommandPtr++;
    }
    mCommandSize = size - mCommandPtr;

    /* extract command arguments */
    strncpy((char*) &mCommandBuffer[0], (const char*) &cmd[mCommandPtr + 1], (size - mCommandPtr));

    /* terminates the root command */
    cmd[mCommandPtr] = 0;
    mArgPtr = 0;

    /* extract the further arguments */
    while (mArgPtr < (mCommandSize)) {
        mArgc++;
        *(mArgv + (mArgc - 1)) = &mCommandBuffer[mArgPtr];

        /* find terminator */
        while (mCommandBuffer[mArgPtr] != ' ' && (mArgPtr < 1023)) {
            mArgPtr++;
        }

        /* adds to argument list */
        mCommandBuffer[mArgPtr] = 0;
        mArgPtr++;

    }

    /* finds and execute the command table */
    mCallbackFunction(cmd, mArgc, mArgv);
}

/****************************************************************************
 * Public Source Code
 ****************************************************************************/
uint8_t Shell_init( shellCallbackPtr callback ) {

    if (callback == NULL) return 1;

    mCallbackFunction = callback;
    SHELL_PRINTF(SHELL_STATUS "%s version: %s"CRLF, SHELL_WELCOME_MESSAGE, SHELL_VERSION);
    SHELL_PRINTF(SHELL_STATUS "Type <help> to show all the commands"CRLF);
    SHELL_PRINTF(SHELL_PROMPT);

    return 0;
}

typedef enum CharStateType {
    SingleKey = 0, EscapeKey, BracketKey,
} CharState;

void Shell_getChar( uint8_t c ) {
    uint16_t mTemp;
    static CharState mState = SingleKey;

    switch (mState) /* Detects if it is a single key or a key chord. */
    {
        case SingleKey: /* Single key. */
            switch (c) {
                case '\r': /* Carriage Return. */
                case '\n': /* New line. */
                    mIsCommandReady = true;
                    SHELL_PRINTF(CRLF)
                    ;
                    checkMessage();
                    SHELL_PRINTF(CRLF SHELL_PROMPT)
                    ;
                    break;

                case 0x7F: /* Delete. */
                case 0x08: /* Backspace. */
                    if (mReadPtr > 0) {
                        SHELL_PRINTF("\b \b"); /* Erase the character from the terminal. */
                        mReadPtr--;
                    }
                    if (mReadPtr < 0) {
                        mReadPtr = SHELL_BUFFER_SIZE;
                    }
                    mShellBuffer[mReadPtr] = '\0';
                    break;

                case 0x09: /* Tab. */
                    mTemp = mReadPtr;
                    if (ShellUtils_autocomplete((char*) mShellBuffer, &mReadPtr)) { /* Handle the auto completion. */

                        while (mTemp-- > 0) { /* Erase old command on the terminal. */
                            SHELL_PRINTF("\b \b");
                        }
                        SHELL_PRINTF("%s", mShellBuffer);
                    }
                    break;
                case 0x1B: /* ESC - Escape key and beginning of a chord of keys. */
                    mState = EscapeKey;
                    break;

                default:
                    /* store the incoming character on command circular buffer. */
                    mShellBuffer[mReadPtr] = c;
                    mReadPtr = (mReadPtr + 1) % SHELL_BUFFER_SIZE;
                    SHELL_PRINTF("%c", c)
                    ;
                    break;
            }
            break;

        case EscapeKey:
            if (c == '[') {
                mState = BracketKey;
            }
            else {
                mState = SingleKey;
            }
            break;

        case BracketKey: /* ESC + '[' */
            mState = SingleKey;
            if (c == 'A') /* Arrow UP  = ESC + '[' + 'A' */
            {
                mTemp = mReadPtr;
                if (ShellUtils_historyUp((char*) mShellBuffer, &mReadPtr)) {

                    while (mTemp-- > 1) { /* Erase old command on the terminal, ignore \0 count. */
                        SHELL_PRINTF("\b \b");
                    }
                    SHELL_PRINTF("%s", mShellBuffer);
                }
            }
            else if (c == 'B') /* Arrow DOWN  = ESC + '[' + 'B' */
            {
                mTemp = mReadPtr;
                if (ShellUtils_historyDown((char*) mShellBuffer, &mReadPtr)) {

                    while (mTemp-- > 1) { /* Erase old command on the terminal, ignore \0 count. */
                        SHELL_PRINTF("\b \b");
                    }
                    SHELL_PRINTF("%s", mShellBuffer);
                }
            }
            break;
    }
}
