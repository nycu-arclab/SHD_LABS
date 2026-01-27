#include "utils.h"

void exception_handler(void) {

    extern volatile int exception_triggered;

    unsigned int mepc, mcause, mstatus;
    
    // read some CSR values
    asm volatile ("csrr %0, mepc" : "=r"(mepc));
    asm volatile ("csrr %0, mcause" : "=r"(mcause));
    asm volatile ("csrr %0, mstatus" : "=r"(mstatus));
    
    unsigned int mpp = (mstatus >> 11) & 0x3;
    
    // print CSR values
    printf("[EXCEPTION!] mcause=%x mepc=%x mpp=%d", mcause, mepc, mpp);

    // print current PRIVILEGE MODE
    if (mpp == 0) {
        printf(" (U-mode)\n");
    } else if (mpp == 3) {
        printf(" (M-mode)\n");
    }

    // mark exception flag
    exception_triggered = 1;
    
    // update mepc 
    mepc += 4;
    asm volatile ("csrw mepc, %0" : : "r"(mepc));
}