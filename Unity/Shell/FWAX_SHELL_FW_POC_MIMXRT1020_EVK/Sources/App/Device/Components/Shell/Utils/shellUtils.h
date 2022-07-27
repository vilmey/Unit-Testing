/**
 ****************************************************************************
 * @file    : shellUtils.c
 * @brief   : Utilities used on the shell logic.
 * @author  : Eldorado Research Institute
 ****************************************************************************
 */

#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

/****************************************************************************
 * Include Files
 ****************************************************************************/
#include <stdbool.h>
#ifdef TEST
#include <stdint.h>
#include <stdio.h>
#else
#include <Types.h>
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/
/**
 * Function to compare two pieces of strings.
 * @param str1 first string.
 * @param str2 second string.
 */
bool ShellUtils_compare( char *str1, char *str2 );

/**
 * Function to auto complete the commands.
 * @param str [in, out] string displayed on the terminal. Completed string will the stored here.
 * @param size [in,out] size of the string. Size of the completed string will be stored here.
 */
bool ShellUtils_autocomplete( char *str, uint16_t *size );

/**
 * Function to save commands to the history.
 * @param cmd command string to be stored.
 */
void ShellUtils_addHistory( char *cmd );

/**
 * Retrieves the previous command on the history.
 * @param str [in, out] string displayed on the terminal. String from history will the stored here.
 * @param size [in,out] size of the string. Size of the string from history will be stored here.
 */
bool ShellUtils_historyUp( char *str, uint16_t *size );

/**
 * Retrieves the next command on the history list.
 * @param str [in, out] string displayed on the terminal. String from history will the stored here.
 * @param size [in,out] size of the string. Size of the string from history will be stored here.
 */
bool ShellUtils_historyDown( char *str, uint16_t *size );

#endif /* SHELL_UTILS_SHELLUTILS_H */
