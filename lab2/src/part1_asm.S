.global part1_start
.section .text

part1_start:
    addi sp, sp, -16
    sw fp, 0(sp)
    sw ra, 4(sp)
    addi fp, sp, 16

    la a0, welcome_msg
    call puts

task1:
    la a0, task1_msg
    call puts

    li a0, 0x1212
    li a1, 0xACDD

    # ==========================TODO: Your code here==========================

    @ ans
    @ li a2, 0xBEEF

    # ========================================================================

    # The check_sum function reads three inputs: a, b and c
    # It returns 1 if a + b equals c, returns 0 otherwise.
    call check_sum

    li t0, 1
    bne a0, t0, leave_part1

task2:
    la a0, task2_msg
    call puts

    # ==========================TODO: Your code here==========================

    @ ans
    @ addi sp, sp, -8
    @ li t0, 0x5543594E
    @ sw t0, 0(sp)
    @ sw zero, 4(sp)

    @ mv a0, sp

    # ========================================================================

    # The check_string function reads one input: str
    # It returns 1 if str is equal to "NYCU", returns 0 otherwise.
    call check_string

    # TODO: Restore sp
    @ addi sp, sp, 8

    li t0, 1
    bne a0, t0, leave_part1

task3:
    la a0, task3_msg
    call puts

overflow_retry:
    /*
     * Stack layout:
     * +----------------------+
     * |     buf[0..3]        | <- sp
     * +----------------------+
     * |     secret           | sp + 4
     * +----------------------+
     * | Saved Frame Pointer  | sp + 8
     * +----------------------+
     * | Saved Return Address | sp + 12
     * +----------------------+
     */
    addi sp, sp, -16
    sw fp, 8(sp)
    sw ra, 12(sp)

    # Initialize secret to 0xDEADBEEF
    li t0, 0xDEADBEEF
    sw t0, 4(sp)

    la a0, input_prompt
    call puts

    # Read input into buf (starts at sp)
    mv a0, sp
    call gets

    la a0, newline
    call puts

    # Check if secret was overwritten
    lw t0, 4(sp)
    li t1, 0xDEADBEEF
    bne t0, t1, overflow_success

    la a0, overflow_fail_msg
    call puts
    lw a0, 4(sp)
    call put_hex
    la a0, newline
    call puts

    lw fp, 8(sp)
    lw ra, 12(sp)
    addi sp, sp, 16
    j overflow_retry

overflow_success:
    la a0, overflow_success_msg
    call puts
    lw a0, 4(sp)
    call put_hex
    la a0, newline
    call puts

    lw fp, 8(sp)
    lw ra, 12(sp)
    addi sp, sp, 16

    la a0, complete_msg
    call puts

leave_part1:
    lw fp, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 16
    ret

.section .rodata
welcome_msg:
.string "=== Part 1: Calling Convention & Buffer Overflow ===\r\n"

task1_msg:
.string "\r\n[Task 1] Pass the correct argument\r\n"

task2_msg:
.string "\r\n[Task 2] Push string to stack\r\n"

task3_msg:
.string "\r\n[Task 3] Buffer Overflow\r\n"

input_prompt:
.string "Enter some bytes: "

overflow_fail_msg:
.string "You didn't overwrite the secret, try again. secret = 0x"

overflow_success_msg:
.string "Good! You changed the secret to 0x"

complete_msg:
.string "\r\n=== Part 1 Complete! Press Ctrl+C to exit ===\r\n"

newline:
.string "\r\n"
