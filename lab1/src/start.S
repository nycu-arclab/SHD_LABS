# start.S - Program entry point

.section .text.init
.globl _start

_start:
    # Initialize stack pointer
    la sp, _stack_top

    # Call main function
    call main

    # If main returns, loop forever
_halt:
    j _halt
