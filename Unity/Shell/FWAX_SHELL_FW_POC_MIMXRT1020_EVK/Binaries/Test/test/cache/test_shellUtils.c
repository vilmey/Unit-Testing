#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.c"
#include "Sources/App/Device/Components/Shell/Utils/shellUtils.h"




void setUp( void ) {



}



void tearDown( void ) {



}





void test_CompareNullStrings( void ) {

    char *str1 = 

                ((void *)0)

                    ;

    char *str2 = 

                ((void *)0)

                    ;

    

   _Bool 

        res = ShellUtils_compare(str1, str2);

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT);

}

void test_CompareTwoDifferentStrings( void ) {

    char *str1 = { "help" };

    char *str2 = { "ver" };

    

   _Bool 

        res = ShellUtils_compare(str1, str2);

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_INT);

}



void test_CompareTwoEqualStrings( void ) {

    char *str1 = { "info" };

    char *str2 = { "info" };

    

   _Bool 

        res = ShellUtils_compare(str1, str2);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_INT);

}



void test_CompareTwoPatiallyEqualStrings( void ) {

    char *str1 = { "version" };

    char *str2 = { "ver" };

    

   _Bool 

        res = ShellUtils_compare(str1, str2);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_INT);

}





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





void test_HistoryUpOnce( void ) {



    char str[15] = { };

    uint16_t size;



    

   _Bool 

        res = ShellUtils_historyUp(str, &size);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("version")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(80));

}



void test_HistoryUpTwice( void ) {



    char str[15] = { };

    uint16_t size;



    

   _Bool 

        res = ShellUtils_historyUp(str, &size);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("led 1 bl1")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(90));

}



void test_HistoryUpUntilTheEnd( void ) {



    char str[] = { "Nothing here" };

    uint16_t size;



    

   _Bool 

        res = ShellUtils_historyUp(str, &size);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("help")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(100));

}



void test_HistoryUpPastTheEnd( void ) {



    char str[15] = { "Nothing" };

    uint16_t size;



    

   _Bool 

        res = ShellUtils_historyUp(str, &size);

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(109), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualString((const char*)(("Nothing")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(111));

}





void test_HistoryDownOnce( void ) {



    char str[15] = { };

    uint16_t size;



    

   _Bool 

        res = ShellUtils_historyDown(str, &size);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("led 1 bl1")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(122));

}



void test_HistoryDownTwice( void ) {



    char str[15] = { };

    uint16_t size;



    

   _Bool 

        res = ShellUtils_historyDown(str, &size);

    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("version")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(132));

}



void test_HistoryDownUntilTheEnd( void ) {



    char str[15] = { };

    uint16_t size;



    

   _Bool 

        res = ShellUtils_historyDown(str, &size);

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(141), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(142));

}



void test_HistoryDownPastTheEnd( void ) {



    char str[15] = { };

    uint16_t size;



    

   _Bool 

        res = ShellUtils_historyDown(str, &size);

    res = ShellUtils_historyDown(str, &size);

    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((res)), (

   ((void *)0)

   ), (UNITY_UINT)(152), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("")), (const char*)((str)), (

   ((void *)0)

   ), (UNITY_UINT)(153));

}
