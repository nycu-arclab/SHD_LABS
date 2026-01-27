#include "utils.h"

void exception_handler(void) {

    extern volatile int exception_triggered;

     unsigned int mepc;
     asm volatile ("csrr %0, mepc" : "=r"(mepc));

    // mark exception flag
    exception_triggered = 1;
    
    // update mepc 
    mepc += 4;
    asm volatile ("csrw mepc, %0" : : "r"(mepc));
}