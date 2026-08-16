
#include "utils.h"

// a flag to keep track of the occurence of exception
volatile int exception_triggered = 0;


// ================================= TODO =================================

// Implement a function that computes multiplication without using the MUL instruction.


// main function, the CPU executes this after bootup
int test_main(void){
    printf("Start fuzzing for MUL bug.......\n");
    // TODO: Test different combinations of inputs
    // Compare hardware MUL result with ref_mul()
    // Print any discrepancies found
    printf("End fuzzing!\n");
}

// ================================= TODO =================================
