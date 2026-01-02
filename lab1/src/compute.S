.globl compute

# ============================================
# compute: Calculate sum from 1 to n (recursive)
# 
# Input:  a0 = n
# Output: a0 = 1 + 2 + ... + n
# 
# Stack frame (8 bytes):
#   sp+4: ra (return address)
#   sp+0: saved n
# ============================================
compute:
    beqz a0, base_case

    # Allocate stack frame
    addi sp, sp, -8
    sw ra, 4(sp)
    sw a0, 0(sp)

    # Recursive call: compute(n-1)
    addi a0, a0, -1
    jal compute

    # After return: a0 = compute(n-1)
    lw t0, 0(sp)        # Restore n into t0
    add a0, a0, t0      # result = compute(n-1) + n

    # Restore and return
    lw ra, 4(sp)
    addi sp, sp, 8
    ret

base_case:
    li a0, 0            # Return 0
    ret
