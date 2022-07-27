/**
 ****************************************************************************
 * @file    : test_shell.c
 * @brief   : Unit test for the Shell.c component
 * @author  : Eldorado Research Institute
 ****************************************************************************
 */

#ifdef TEST

#include "unity.c"
#include "shell.h"
#include "mock_shellUtils.h"

// Test callback
void ShellCallbackMockFunction( uint8_t *cmd, uint16_t argc, uint8_t **argv ) {

}

void setUp( void ) {

}

void tearDown( void ) {

}

void test_InitShellNullArgument( void ) {
    TEST_ASSERT_EQUAL(1, Shell_init(NULL));
}

void test_InitShellValidArgument( void ) {
    TEST_ASSERT_EQUAL(0, Shell_init((shellCallbackPtr ) ShellCallbackMockFunction));
}

void test_Shell_getChar_NewLine( void ) {
//	shellCheckMessage_Expect();
    Shell_getChar('\n');
}

void test_Shell_getChar_h( void ) {
//	shellCheckMessage_Expect();
    Shell_getChar('h');
}

void test_Shell_getChar_Tab( void ) {
//	shellCheckMessage_Expect();
    uint16_t size = 1;
    ShellUtils_autocomplete_ExpectAndReturn("h", &size, true);
    Shell_getChar(0x09);
}

void test_Shell_getChar_Esc( void ) {
    Shell_getChar(0x1B);
}

void test_Shell_getChar_Esc2( void ) {
    ShellUtils_addHistory_Expect("h");
    Shell_getChar(0x1B);
    Shell_getChar('\n');
}

void test_Shell_getChar_LedCmd( void ) {
    ShellUtils_addHistory_Expect("led ?");

    int count = 0;
    char cmd[6] = "led ?";

    for (count = 0; count < sizeof(cmd); count++) {

        Shell_getChar(cmd[count]);
    }

    Shell_getChar('\n');
}

void test_Shell_getChar_Backspace( void ) {
//	shellCheckMessage_Expect();
    Shell_getChar(0x08);
}

void test_Shell_getChar_ArrowUp( void ) {
    uint16_t size = 0;
    ShellUtils_historyUp_ExpectAndReturn("", &size, true);
    Shell_getChar(0x1B);	//ESC
    Shell_getChar('[');		//Braces
    Shell_getChar('A');	    //A
}

void test_Shell_getChar_ArrowDown( void ) {
    uint16_t size = 0;
    ShellUtils_historyDown_ExpectAndReturn("", &size, true);
    Shell_getChar(0x1B);	//ESC
    Shell_getChar('[');		//Braces
    Shell_getChar('B');	    //A
}
#endif
