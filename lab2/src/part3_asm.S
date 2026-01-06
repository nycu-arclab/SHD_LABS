.global part3_start
.global win
.global gadget_1
.global gadget_2
.global gadget_3
.global gadget_4
.global gadget_5
.section .text

part3_start:
    addi sp, sp, -16
    sw fp, 0(sp)
    sw ra, 4(sp)
    addi fp, sp, 16

    la a0, welcome_msg
    call puts

    /*
     * Stack layout:
     * +----------------------+
     * | Saved Frame Pointer  | <- sp
     * +----------------------+
     * | Saved Return Address | sp + 4
     * +----------------------+
     * |       Padding        | sp + 8
     * +----------------------+
     * |       Padding        | sp + 12
     * +----------------------+
     */

    la a0, prompt
    call puts

    # Read input into stack
    mv a0, sp
    call gets

    la a0, newline
    call puts

    la a0, ra_msg
    call puts
    lw a0, 4(sp)
    call put_hex
    la a0, newline
    call puts

    lw fp, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 16
    ret


/*
 * ROP Gadgets
 * Note: You may not need all gadgets!
 */


gadget_1:
    lw a3, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 8
    ret

gadget_2:
    addi a2, a3, -0x100
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

gadget_3:
    li t0, 0x1234
    add a1, a2, t0
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

gadget_4:
    mv a0, a1
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

gadget_5:
    mv a0, a3
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

# win function - check if a0 == 0x5A5A5A5A
win:
    # Save a0 for later comparison
    mv t2, a0

    la a0, win_msg
    call puts

    la a0, a0_msg
    call puts
    mv a0, t2
    call put_hex
    la a0, newline
    call puts

    # Check if a0 == 0x5A5A5A5A
    li t0, 0x5A5A5A5A
    bne t2, t0, win_fail

    la a0, correct_msg
    call puts
    la a0, complete_msg
    call puts
    j .

win_fail:
    la a0, wrong_msg
    call puts
    j .

.section .rodata
welcome_msg:
.string "=== Part 3: Return-Oriented Programming ===\r\n"

prompt:
.string "Enter some bytes: "

ra_msg:
.string "Returning to: 0x"

win_msg:
.string "You successfully jumped to win! Now checking a0...\r\n"

a0_msg:
.string "a0 = 0x"

correct_msg:
.string "Correct!\r\n"

wrong_msg:
.string "Wrong! Expected a0: 0x5A5A5A5A\r\n"

complete_msg:
.string "\r\n=== Part 3 Complete! Press Ctrl+C to exit ===\r\n"

newline:
.string "\r\n"
