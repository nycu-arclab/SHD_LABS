.global part2_start
.global win1
.global win2
.section .text

part2_start:
    addi sp, sp, -16
    sw fp, 0(sp)
    sw ra, 4(sp)
    addi fp, sp, 16

    la a0, welcome_msg
    call puts

task1:
    la a0, task1_msg
    call puts

task1_retry:
    /*
     * Stack layout:
     * +----------------------+
     * |     buf[0..3]        | <- sp
     * +----------------------+
     * | Saved Frame Pointer  | sp + 4
     * +----------------------+
     * | Saved Return Address | sp + 8
     * +----------------------+
     */
    addi sp, sp, -16
    sw fp, 4(sp)
    sw ra, 8(sp)

    la a0, task1_prompt
    call puts

    # Read input into buf (starts at sp)
    mv a0, sp
    call gets

    la a0, newline
    call puts

    la a0, ra_msg
    call puts
    lw a0, 8(sp)
    call put_hex
    la a0, newline
    call puts

    lw fp, 4(sp)
    lw ra, 8(sp)
    addi sp, sp, 16
    ret

task2:
    la a0, task2_msg
    call puts

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

task2_input:
    # Initialize secret
    li t0, 0xDEADBEEF
    sw t0, 4(sp)

    la a0, task2_prompt
    call puts

    # Read input into buf (starts at sp)
    mv a0, sp
    call gets

    la a0, newline
    call puts

    la a0, ra_msg
    call puts
    lw a0, 12(sp)
    call put_hex
    la a0, newline
    call puts

    # Note: sp is NOT restored here so win2 can access secret at sp+4
    lw fp, 8(sp)
    lw ra, 12(sp)
    ret

leave_part2:
    lw fp, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 16
    ret

# Win function for task 1
win1:
    la a0, win1_msg
    call puts
    j task2

# Win function for task 2 (with condition check)
win2:
    # Check if secret == 0x1212
    lw t0, 4(sp)
    li t1, 0x1212
    bne t0, t1, win2_fail

    la a0, win2_msg
    call puts
    la a0, complete_msg
    call puts
    j .

win2_fail:
    la a0, win2_fail_msg
    call puts
    lw a0, 4(sp)
    call put_hex
    la a0, newline
    call puts
    j task2_input

.section .rodata
welcome_msg:
.string "=== Part 2: Return-Oriented Exploitation ===\r\n"

task1_msg:
.string "\r\n[Task 1] Overflow the buffer to jump to win1\r\n"

task1_prompt:
.string "Enter some bytes: "

task2_msg:
.string "\r\n[Task 2] Jump to win2 and pass the secret check\r\n"

task2_prompt:
.string "Enter some bytes: "

ra_msg:
.string "Returning to: 0x"

win1_msg:
.string "Task 1 complete! You reached win1!\r\n"

win2_msg:
.string "Task 2 complete! You reached win2 with correct secret!\r\n"

win2_fail_msg:
.string "win2 reached but secret is wrong: 0x"

complete_msg:
.string "\r\n=== Part 2 Complete! Press Ctrl+C to exit ===\r\n"

newline:
.string "\r\n"
