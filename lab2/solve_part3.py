#!/usr/bin/env python3
from pwn import *

io = process(['./run.sh', 'part3'])

io.recvuntil(b"Enter some bytes: ")

# TODO: Fill in the address for gadgets and succeed function
GADGET_1 = 0x0
GADGET_2 = 0x0
GADGET_3 = 0x0
GADGET_4 = 0x0
GADGET_5 = 0x0
SUCCEED  = 0x0

# TODO: Complete the input_text that satisfy the requirement for succeed
input_text = b''

io.sendline(input_text)

io.interactive()
