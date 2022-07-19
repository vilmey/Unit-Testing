#ifdef TEST

#include "unity.c"
#include "shell.h"

// Test callback
void ShellCallbackMockFunction(uint8_t *cmd, uint16_t argc, uint8_t **argv) {

}

void setUp(void){

}

void tearDown(void){

}

void test_InitShellNullArgument(void){
	TEST_ASSERT_EQUAL(1, shellInit(NULL));
}

void test_InitShellValidArgument(void){
	TEST_ASSERT_EQUAL(0, shellInit((shellCallbackPtr) ShellCallbackMockFunction));
}

void test_shellGetc_NewLine(void){
//	shellCheckMessage_Expect();
	shellGetc('\n');
}

void test_shellGetc_h(void){
//	shellCheckMessage_Expect();
	shellGetc('h');
}


void test_shellGetc_Tab(void){
//	shellCheckMessage_Expect();
	shellGetc(0x09);
}

void test_shellGetc_Esc(void){
//	shellCheckMessage_Expect();
	shellGetc(0x1B);
}

void test_shellGetc_Esc2(void){
//	shellCheckMessage_Expect();
	shellGetc(0x1B);
}

void test_shellGetc_LedCmd(void){
//	shellCheckMessage_Expect();

	int count = 0;
	char cmd[6] = "led ?";
	for(count = 0; count < sizeof(cmd); count++) {

		shellGetc(cmd[count]);
	}

	shellGetc('\n');
}

void test_shellGetc_Backspace(void){
//	shellCheckMessage_Expect();
	shellGetc(0x08);
}

void test_shellGetc_ArrowUp(void){
//	shellCheckMessage_Expect();
	shellGetc(0x1B);	//ESC
	shellGetc('[');		//Braces
	shellGetc('A');	//A
}

void test_shellGetc_ArrowDown(void){
//	shellCheckMessage_Expect();
	shellGetc(0x1B);	//ESC
	shellGetc('[');		//Braces
	shellGetc('B');	//A
}
#endif
