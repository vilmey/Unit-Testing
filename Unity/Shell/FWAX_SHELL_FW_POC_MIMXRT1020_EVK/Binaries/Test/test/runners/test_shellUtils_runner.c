/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_CompareNullStrings(void );
extern void test_CompareTwoDifferentStrings(void );
extern void test_CompareTwoEqualStrings(void );
extern void test_CompareTwoPatiallyEqualStrings(void );
extern void test_AddHistoryNullString(void );
extern void test_AddHistoryRegularString(void );
extern void test_AddHistoryStringWithTrailingSpaces(void );
extern void test_AddHistoryRegularString2(void );
extern void test_HistoryUpOnce(void );
extern void test_HistoryUpTwice(void );
extern void test_HistoryUpUntilTheEnd(void );
extern void test_HistoryUpPastTheEnd(void );
extern void test_HistoryDownOnce(void );
extern void test_HistoryDownTwice(void );
extern void test_HistoryDownUntilTheEnd(void );
extern void test_HistoryDownPastTheEnd(void );


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
}
static void CMock_Verify(void)
{
}
static void CMock_Destroy(void)
{
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
  UnityBegin("test_shellUtils.c");
  run_test(test_CompareNullStrings, "test_CompareNullStrings", 24);
  run_test(test_CompareTwoDifferentStrings, "test_CompareTwoDifferentStrings", 30);
  run_test(test_CompareTwoEqualStrings, "test_CompareTwoEqualStrings", 37);
  run_test(test_CompareTwoPatiallyEqualStrings, "test_CompareTwoPatiallyEqualStrings", 44);
  run_test(test_AddHistoryNullString, "test_AddHistoryNullString", 52);
  run_test(test_AddHistoryRegularString, "test_AddHistoryRegularString", 57);
  run_test(test_AddHistoryStringWithTrailingSpaces, "test_AddHistoryStringWithTrailingSpaces", 62);
  run_test(test_AddHistoryRegularString2, "test_AddHistoryRegularString2", 67);
  run_test(test_HistoryUpOnce, "test_HistoryUpOnce", 73);
  run_test(test_HistoryUpTwice, "test_HistoryUpTwice", 83);
  run_test(test_HistoryUpUntilTheEnd, "test_HistoryUpUntilTheEnd", 93);
  run_test(test_HistoryUpPastTheEnd, "test_HistoryUpPastTheEnd", 103);
  run_test(test_HistoryDownOnce, "test_HistoryDownOnce", 115);
  run_test(test_HistoryDownTwice, "test_HistoryDownTwice", 125);
  run_test(test_HistoryDownUntilTheEnd, "test_HistoryDownUntilTheEnd", 135);
  run_test(test_HistoryDownPastTheEnd, "test_HistoryDownPastTheEnd", 145);

  return UnityEnd();
}
