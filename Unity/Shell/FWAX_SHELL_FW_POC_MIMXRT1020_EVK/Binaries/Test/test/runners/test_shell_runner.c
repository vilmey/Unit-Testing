/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_shellUtils.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_InitShellNullArgument(void );
extern void test_InitShellValidArgument(void );
extern void test_Shell_getChar_NewLine(void );
extern void test_Shell_getChar_h(void );
extern void test_Shell_getChar_Tab(void );
extern void test_Shell_getChar_Esc(void );
extern void test_Shell_getChar_Esc2(void );
extern void test_Shell_getChar_LedCmd(void );
extern void test_Shell_getChar_Backspace(void );
extern void test_Shell_getChar_ArrowUp(void );
extern void test_Shell_getChar_ArrowDown(void );


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_shellUtils_Init();
}
static void CMock_Verify(void)
{
  mock_shellUtils_Verify();
}
static void CMock_Destroy(void)
{
  mock_shellUtils_Destroy();
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_shell.c");
  run_test(test_InitShellNullArgument, "test_InitShellNullArgument", 28);
  run_test(test_InitShellValidArgument, "test_InitShellValidArgument", 32);
  run_test(test_Shell_getChar_NewLine, "test_Shell_getChar_NewLine", 36);
  run_test(test_Shell_getChar_h, "test_Shell_getChar_h", 41);
  run_test(test_Shell_getChar_Tab, "test_Shell_getChar_Tab", 46);
  run_test(test_Shell_getChar_Esc, "test_Shell_getChar_Esc", 53);
  run_test(test_Shell_getChar_Esc2, "test_Shell_getChar_Esc2", 57);
  run_test(test_Shell_getChar_LedCmd, "test_Shell_getChar_LedCmd", 63);
  run_test(test_Shell_getChar_Backspace, "test_Shell_getChar_Backspace", 77);
  run_test(test_Shell_getChar_ArrowUp, "test_Shell_getChar_ArrowUp", 82);
  run_test(test_Shell_getChar_ArrowDown, "test_Shell_getChar_ArrowDown", 90);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}