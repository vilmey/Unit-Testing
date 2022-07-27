#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.c"
#include "Binaries/Test/test/mocks/mock_shellUtils.h"
#include "Sources/App/Device/Components/Shell/Middleware/shell.h"




void ShellCallbackMockFunction( uint8_t *cmd, uint16_t argc, uint8_t **argv ) {



}



void setUp( void ) {



}



void tearDown( void ) {



}



void test_InitShellNullArgument( void ) {

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((Shell_init(

   ((void *)0)

   ))), (

   ((void *)0)

   ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_INT);

}



void test_InitShellValidArgument( void ) {

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((Shell_init((shellCallbackPtr ) ShellCallbackMockFunction))), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);

}



void test_Shell_getChar_NewLine( void ) {



    Shell_getChar('\n');

}



void test_Shell_getChar_h( void ) {



    Shell_getChar('h');

}



void test_Shell_getChar_Tab( void ) {



    uint16_t size = 1;

    ShellUtils_autocomplete_CMockExpectAndReturn(49, "h", &size, 

   1

   );

    Shell_getChar(0x09);

}



void test_Shell_getChar_Esc( void ) {

    Shell_getChar(0x1B);

}



void test_Shell_getChar_Esc2( void ) {

    ShellUtils_addHistory_CMockExpect(58, "h");

    Shell_getChar(0x1B);

    Shell_getChar('\n');

}



void test_Shell_getChar_LedCmd( void ) {

    ShellUtils_addHistory_CMockExpect(64, "led ?");



    int count = 0;

    char cmd[6] = "led ?";



    for (count = 0; count < sizeof(cmd); count++) {



        Shell_getChar(cmd[count]);

    }



    Shell_getChar('\n');

}



void test_Shell_getChar_Backspace( void ) {



    Shell_getChar(0x08);

}



void test_Shell_getChar_ArrowUp( void ) {

    uint16_t size = 0;

    ShellUtils_historyUp_CMockExpectAndReturn(84, "", &size, 

   1

   );

    Shell_getChar(0x1B);

    Shell_getChar('[');

    Shell_getChar('A');

}



void test_Shell_getChar_ArrowDown( void ) {

    uint16_t size = 0;

    ShellUtils_historyDown_CMockExpectAndReturn(92, "", &size, 

   1

   );

    Shell_getChar(0x1B);

    Shell_getChar('[');

    Shell_getChar('B');

}
