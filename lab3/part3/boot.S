.section .text.start
    .globl _start

_start:
    // set the MTVEC 
    // when exception occurs, CPU jumps to "exception_entry"
    la   t0, exception_entry
    csrw mtvec, t0
    
    la   sp, _stack_top
    
    // when the CPU does mret, it jumps to user_main
    la   t0, user_main
    csrw mepc, t0
    
    // set mstatus.MPP
    // when mret, he privilege becomes U-MODE
    li   t0, 0x1800
    csrc mstatus, t0
    
    mret