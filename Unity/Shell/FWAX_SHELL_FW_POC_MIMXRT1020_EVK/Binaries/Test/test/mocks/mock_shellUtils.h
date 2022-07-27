/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_SHELLUTILS_H
#define _MOCK_SHELLUTILS_H

#include "unity.h"
#include "shellUtils.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_shellUtils_Init(void);
void mock_shellUtils_Destroy(void);
void mock_shellUtils_Verify(void);




#define ShellUtils_compare_IgnoreAndReturn(cmock_retval) ShellUtils_compare_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void ShellUtils_compare_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, _Bool cmock_to_return);
#define ShellUtils_compare_StopIgnore() ShellUtils_compare_CMockStopIgnore()
void ShellUtils_compare_CMockStopIgnore(void);
#define ShellUtils_compare_ExpectAndReturn(str1, str2, cmock_retval) ShellUtils_compare_CMockExpectAndReturn(__LINE__, str1, str2, cmock_retval)
void ShellUtils_compare_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* str1, char* str2, _Bool cmock_to_return);
typedef _Bool (* CMOCK_ShellUtils_compare_CALLBACK)(char* str1, char* str2, int cmock_num_calls);
void ShellUtils_compare_AddCallback(CMOCK_ShellUtils_compare_CALLBACK Callback);
void ShellUtils_compare_Stub(CMOCK_ShellUtils_compare_CALLBACK Callback);
#define ShellUtils_compare_StubWithCallback ShellUtils_compare_Stub
#define ShellUtils_autocomplete_IgnoreAndReturn(cmock_retval) ShellUtils_autocomplete_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void ShellUtils_autocomplete_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, _Bool cmock_to_return);
#define ShellUtils_autocomplete_StopIgnore() ShellUtils_autocomplete_CMockStopIgnore()
void ShellUtils_autocomplete_CMockStopIgnore(void);
#define ShellUtils_autocomplete_ExpectAndReturn(str, size, cmock_retval) ShellUtils_autocomplete_CMockExpectAndReturn(__LINE__, str, size, cmock_retval)
void ShellUtils_autocomplete_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* str, uint16_t* size, _Bool cmock_to_return);
typedef _Bool (* CMOCK_ShellUtils_autocomplete_CALLBACK)(char* str, uint16_t* size, int cmock_num_calls);
void ShellUtils_autocomplete_AddCallback(CMOCK_ShellUtils_autocomplete_CALLBACK Callback);
void ShellUtils_autocomplete_Stub(CMOCK_ShellUtils_autocomplete_CALLBACK Callback);
#define ShellUtils_autocomplete_StubWithCallback ShellUtils_autocomplete_Stub
#define ShellUtils_addHistory_Ignore() ShellUtils_addHistory_CMockIgnore()
void ShellUtils_addHistory_CMockIgnore(void);
#define ShellUtils_addHistory_StopIgnore() ShellUtils_addHistory_CMockStopIgnore()
void ShellUtils_addHistory_CMockStopIgnore(void);
#define ShellUtils_addHistory_Expect(cmd) ShellUtils_addHistory_CMockExpect(__LINE__, cmd)
void ShellUtils_addHistory_CMockExpect(UNITY_LINE_TYPE cmock_line, char* cmd);
typedef void (* CMOCK_ShellUtils_addHistory_CALLBACK)(char* cmd, int cmock_num_calls);
void ShellUtils_addHistory_AddCallback(CMOCK_ShellUtils_addHistory_CALLBACK Callback);
void ShellUtils_addHistory_Stub(CMOCK_ShellUtils_addHistory_CALLBACK Callback);
#define ShellUtils_addHistory_StubWithCallback ShellUtils_addHistory_Stub
#define ShellUtils_historyUp_IgnoreAndReturn(cmock_retval) ShellUtils_historyUp_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void ShellUtils_historyUp_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, _Bool cmock_to_return);
#define ShellUtils_historyUp_StopIgnore() ShellUtils_historyUp_CMockStopIgnore()
void ShellUtils_historyUp_CMockStopIgnore(void);
#define ShellUtils_historyUp_ExpectAndReturn(str, size, cmock_retval) ShellUtils_historyUp_CMockExpectAndReturn(__LINE__, str, size, cmock_retval)
void ShellUtils_historyUp_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* str, uint16_t* size, _Bool cmock_to_return);
typedef _Bool (* CMOCK_ShellUtils_historyUp_CALLBACK)(char* str, uint16_t* size, int cmock_num_calls);
void ShellUtils_historyUp_AddCallback(CMOCK_ShellUtils_historyUp_CALLBACK Callback);
void ShellUtils_historyUp_Stub(CMOCK_ShellUtils_historyUp_CALLBACK Callback);
#define ShellUtils_historyUp_StubWithCallback ShellUtils_historyUp_Stub
#define ShellUtils_historyDown_IgnoreAndReturn(cmock_retval) ShellUtils_historyDown_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void ShellUtils_historyDown_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, _Bool cmock_to_return);
#define ShellUtils_historyDown_StopIgnore() ShellUtils_historyDown_CMockStopIgnore()
void ShellUtils_historyDown_CMockStopIgnore(void);
#define ShellUtils_historyDown_ExpectAndReturn(str, size, cmock_retval) ShellUtils_historyDown_CMockExpectAndReturn(__LINE__, str, size, cmock_retval)
void ShellUtils_historyDown_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* str, uint16_t* size, _Bool cmock_to_return);
typedef _Bool (* CMOCK_ShellUtils_historyDown_CALLBACK)(char* str, uint16_t* size, int cmock_num_calls);
void ShellUtils_historyDown_AddCallback(CMOCK_ShellUtils_historyDown_CALLBACK Callback);
void ShellUtils_historyDown_Stub(CMOCK_ShellUtils_historyDown_CALLBACK Callback);
#define ShellUtils_historyDown_StubWithCallback ShellUtils_historyDown_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif