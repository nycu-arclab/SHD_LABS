# compute.S - Assembly function for GDB practice
# 
# This function computes: 1 + 2 + 3 + ... + n
# Students can set breakpoints here to observe registers and stack

.globl compute

# ============================================
# compute: Calculate sum from 1 to n
# 
# Input:  a0 = n
# Output: a0 = 1 + 2 + ... + n
# 
# Registers used:
#   t0 = sum (accumulator)
#   t1 = i (counter)
#   a0 = n (input, preserved for comparison)
# ============================================
compute:
    # Save registers to stack
    addi sp, sp, -16
    sw ra, 12(sp)
    sw s0, 8(sp)

    # Initialize
    mv s0, a0               # s0 = n (save input)
    li t0, 0                # t0 = sum = 0
    li t1, 1                # t1 = i = 1

compute_loop:
    # Loop condition: if i > n, exit
    bgt t1, s0, compute_done

    # sum += i
    add t0, t0, t1

    # i++
    addi t1, t1, 1

    # Continue loop
    j compute_loop

compute_done:
    # Return value in a0
    mv a0, t0

    # Restore registers
    lw ra, 12(sp)
    lw s0, 8(sp)
    addi sp, sp, 16

    ret
