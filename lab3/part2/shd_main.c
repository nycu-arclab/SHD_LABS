
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


// ================================= SOLUTION =================================

// extern void test_opcode_asm(unsigned int opcode);

// int test_main(void) {
//     printf("Fuzzing 0x74 - 0x7F...\n");
    
//     for (unsigned int opcode = 0x00; opcode <= 0x7f; opcode++) {
//         exception_triggered = 0;

//         if (opcode == 0x6F || opcode == 0x63 || opcode == 0x67){
//             continue;
//         }
        
//         // test the instruction
//         // the "exception_triggered" flag should be 1 if the opcode is invalid
//         test_opcode_asm(opcode);
        
//         if (!exception_triggered) {
//             // backdoor
//             printf("BACKDOOR FOUND!!! opcode = 0x%x\n", opcode);
//         } else {
//             // printf("0x%x ok\n", opcode);
//         }
//     }
    
//     printf("Fuzzing complete!\n");
//     return 0;
// }
// ================================= SOLUTION =================================