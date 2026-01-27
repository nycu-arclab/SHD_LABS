.section .text
.globl test_opcode_asm

test_opcode_asm:
    # a0 = opcode (only lower 7 bits)
    andi a0, a0, 0x7F
    
    # replace "target_inst" with the given opcode
    la t0, target_inst
    sw a0, 0(t0)
    
    # flush instruction cache
    fence.i
    
    # execute "target_inst", which is overwritten after every function call
target_inst:
    .word 0x00000000
    ret