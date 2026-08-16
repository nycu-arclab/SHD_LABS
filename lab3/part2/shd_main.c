
#include "utils.h"

// a flag to keep track of the occurence of exception
volatile int exception_triggered = 0;


// ================================= TODO =================================

// This function simply execute an instruction with the provided opcode
// Usage: test_opcode_asm(opcode)
// The CPU will execute instruction {25'b0, opcode}
// Refer to fuzz_helper.S
extern void test_opcode_asm(unsigned int opcode);


// main function, the CPU executes this after bootup
int test_main(void){
    printf("Start fuzzing for backdoor.......\n");
    // TODO: Try to execute different opcode
    // Check if an exception happened by examining "exception_triggered"
    printf("End fuzzing!\n");
}

// ================================= TODO =================================
