/**
 ****************************************************************************
 * @file    : test_shellUtils.c
 * @brief   : Unit test for the ShellUtils.c component
 * @author  : Eldorado Research Institute
 ****************************************************************************
 */

#ifdef TEST

#include "unity.c"
#include "shellUtils.h"
#include <stdbool.h>

void setUp( void ) {

}

void tearDown( void ) {

}

/* Testing ShellUtils_compare */
void test_CompareNullStrings( void ) {
    char *str1 = NULL;
    char *str2 = NULL;
    bool res = ShellUtils_compare(str1, str2);
    TEST_ASSERT_EQUAL(false, res);
}
void test_CompareTwoDifferentStrings( void ) {
    char *str1 = { "help" };
    char *str2 = { "ver" };
    bool res = ShellUtils_compare(str1, str2);
    TEST_ASSERT_EQUAL(false, res);
}

void test_CompareTwoEqualStrings( void ) {
    char *str1 = { "info" };
    char *str2 = { "info" };
    bool res = ShellUtils_compare(str1, str2);
    TEST_ASSERT_EQUAL(true, res);
}

void test_CompareTwoPatiallyEqualStrings( void ) {
    char *str1 = { "version" };
    char *str2 = { "ver" };
    bool res = ShellUtils_compare(str1, str2);
    TEST_ASSERT_EQUAL(true, res);
}

/* Testing ShellUtils_addHistory */
void test_AddHistoryNullString( void ) {
    char *str1;
    ShellUtils_addHistory(str1);
}

void test_AddHistoryRegularString( void ) {
    char str1[] = { "help" };
    ShellUtils_addHistory(str1);
}

void test_AddHistoryStringWithTrailingSpaces( void ) {
    char str1[] = { "led 1 bl1   " };
    ShellUtils_addHistory(str1);
}

void test_AddHistoryRegularString2( void ) {
    char str1[] = { "version   " };
    ShellUtils_addHistory(str1);
}

/* Testing ShellUtils_historyUp */
void test_HistoryUpOnce( void ) {
    // Gets the previous command
    char str[15] = { };
    uint16_t size;

    bool res = ShellUtils_historyUp(str, &size);
    TEST_ASSERT_EQUAL(true, res);
    TEST_ASSERT_EQUAL_STRING("version", str);
}

void test_HistoryUpTwice( void ) {
    // Gets the previous command
    char str[15] = { };
    uint16_t size;

    bool res = ShellUtils_historyUp(str, &size);
    TEST_ASSERT_EQUAL(true, res);
    TEST_ASSERT_EQUAL_STRING("led 1 bl1", str);
}

void test_HistoryUpUntilTheEnd( void ) {
    // Gets the first command typed
    char str[] = { "Nothing here" };
    uint16_t size;

    bool res = ShellUtils_historyUp(str, &size);
    TEST_ASSERT_EQUAL(true, res);
    TEST_ASSERT_EQUAL_STRING("help", str);
}

void test_HistoryUpPastTheEnd( void ) {
    // Returns false, no more history
    char str[15] = { "Nothing" };
    uint16_t size;

    bool res = ShellUtils_historyUp(str, &size);
    TEST_ASSERT_EQUAL(false, res);
    // Does not return new string
    TEST_ASSERT_EQUAL_STRING("Nothing", str);
}

/* Testing ShellUtils_historyDown */
void test_HistoryDownOnce( void ) {
    // Gets next command in line
    char str[15] = { };
    uint16_t size;

    bool res = ShellUtils_historyDown(str, &size);
    TEST_ASSERT_EQUAL(true, res);
    TEST_ASSERT_EQUAL_STRING("led 1 bl1", str);
}

void test_HistoryDownTwice( void ) {
    // Gets next command in line
    char str[15] = { };
    uint16_t size;

    bool res = ShellUtils_historyDown(str, &size);
    TEST_ASSERT_EQUAL(true, res);
    TEST_ASSERT_EQUAL_STRING("version", str);
}

void test_HistoryDownUntilTheEnd( void ) {
    // Gets last command typed
    char str[15] = { };
    uint16_t size;

    bool res = ShellUtils_historyDown(str, &size);
    TEST_ASSERT_EQUAL(false, res);
    TEST_ASSERT_EQUAL_STRING("", str);
}

void test_HistoryDownPastTheEnd( void ) {
    // Returns false, no more history
    char str[15] = { };
    uint16_t size;

    bool res = ShellUtils_historyDown(str, &size);
    res = ShellUtils_historyDown(str, &size);
    TEST_ASSERT_EQUAL(false, res);
    TEST_ASSERT_EQUAL_STRING("", str);
}

#endif
